/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:30:20 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/08 23:01:43 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_print_error(char *str)
{
	printf("Error: %s\n", str);
	//printf("Program was terminated!\n");
	return (FALSE);
}

void	ft_free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_check_extention(char *str, char *ext)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(str);
	temp = ft_substr(str, len - 4, len);
	if (ft_strcmp(temp, ext) != 0)
	{
		free(temp);
		return (FALSE);
	}
	free(temp);
	return (TRUE);
}

int	ft_is_file_valid(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (FALSE);
	return (TRUE);
}

int	ft_is_map_config_loaded(t_game *game)
{
	if (game->map.no.path == NULL || game->map.so.path == NULL
		|| game->map.ea.path == NULL || game->map.we.path == NULL
		|| game->map.floor.rgb[0] == -1 || game->map.ceiling.rgb[0] == -1)
		return (FALSE);
	return (TRUE);
}

int	ft_is_arr_only_nbr(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_get_line(int fd, char **line)
{
	char	buffer;
	int		size;

	size = 0;
	*line = NULL;
	buffer = '\0';
	if (fd < 0 || read(fd, &buffer, 0) < 0)
		return (FALSE);
	size = read(fd, &buffer, 1);
	if (!buffer)
		return (FALSE);
	if (buffer != '\n' && size == 1)
		*line = ft_str_join_c(*line, buffer);
	while (buffer != '\n' && size == 1)
	{
		size = read(fd, &buffer, 1);
		if (!buffer)
			return (FALSE);
		if (buffer != '\n' && size == 1)
			*line = ft_str_join_c(*line, buffer);
	}
	return (TRUE);
}

int	ft_check_rgb(char **str, int *nbr)
{
	if (!ft_trim_front(str, ' ') || !ft_trim_back(str, ' '))
		return (FALSE);
	if (!ft_is_arr_only_nbr(*str))
		return (ft_print_error("Incorrect map color rgb parameter"));
	*nbr = ft_atoi(*str);
	if (*nbr < 0 || *nbr > 255)
		return (ft_print_error("Incorrect map color rgb parameter"));
	return (TRUE);
}

int	ft_store_map_fc_colors(t_game *game, char type, char *src)
{
	int		i;
	int		nbr;
	char	**temp;

	temp = ft_split(src, ',');
	if (temp == NULL || ft_strlen_2d(temp) != 3)
	{
		ft_free_2d_arr(temp);
		return (ft_print_error("Incorrect map color rgb parameter"));
	}
	i = 0;
	while (i < 3)
	{
		if (!ft_check_rgb(&temp[i], &nbr))
		{
			ft_free_2d_arr(temp);
			return (FALSE);
		}
		if (type == 'F')
			game->map.floor.rgb[i] = nbr;
		else
			game->map.ceiling.rgb[i] = nbr;
		i++;
	}
	ft_free_2d_arr(temp);
	return (TRUE);
}

int	ft_parse_floor_ceiling_colors(t_game *game, char **line)
{
	char	*temp;

	if (line[0][0] == 'F')
	{
		if (game->map.floor.rgb[0] != -1)
			return (ft_print_error("Duplicate map configuration entries found in map file"));
	}
	else if (line[0][0] == 'C')
	{
		if (game->map.ceiling.rgb[0] != -1)
			return (ft_print_error("Duplicate map configuration entries found in map file"));
	}
	temp = ft_substr(*line, 2, ft_strlen(*line));
	if (!ft_trim_front(&temp, ' ') || !ft_store_map_fc_colors(game, line[0][0], temp))
	{
		free(temp);
		return (FALSE);
	}
	free(temp);
	return (TRUE);
}

int	ft_check_texture_path_extension(char **line, char **path)
{
	*path = ft_substr(*line, 3, ft_strlen(*line));
	if (!ft_trim_front(path, ' ') || !ft_trim_back(path, ' ') || !ft_check_extention(*path, ".xpm"))
		return (ft_print_error("Unsupported map texture extension"));
	if (!ft_is_file_valid(*path))
		return (ft_print_error("No such map texture file"));
	return (TRUE);
}

int	ft_store_wall_text_path(t_game *game, char **line)
{
	char	*path;

	path = NULL;
	if (!ft_check_texture_path_extension(line, &path))
	{
		free(path);
		return (FALSE);
	}
	if (line[0][0] == 'N' && game->map.no.path == NULL)
		game->map.no.path = path;
	else if (line[0][0] == 'S' && game->map.so.path == NULL)
		game->map.so.path = path;
	else if (line[0][0] == 'E' && game->map.ea.path == NULL)
		game->map.ea.path = path;
	else if (line[0][0] == 'W' && game->map.we.path == NULL)
		game->map.we.path = path;
	else
	{
		free(path);
		return (ft_print_error("Duplicate map configuration entries found in map file"));
	}
	return (TRUE);
}

int	ft_get_map_colors_textures(t_game *game, char **line)
{
	char	*sub;

	sub = ft_substr(*line, 0, 3);
	if ((line[0][0] == 'F' || line[0][0] == 'C') && line[0][1] == ' '
		&& ft_strlen(*line) > 6)
	{
		if (!ft_parse_floor_ceiling_colors(game, line))
		{
			free(sub);
			return (FALSE);
		}
	}
	else if ((ft_strcmp(sub, "NO ") == 0 || ft_strcmp(sub, "SO ") == 0
			|| ft_strcmp(sub, "EA ") == 0 || ft_strcmp(sub, "WE ") == 0)
		&& ft_strlen(*line) > 9)
	{
		if (!ft_store_wall_text_path(game, line))
		{
			free(sub);
			return (FALSE);
		}
	}
	else
	{
		free (sub);
		return (ft_print_error("Unsupported, missing or corrupted entries found in map file"));
	}
	free (sub);
	free(*line);
	return (TRUE);
}

int	ft_check_map_file_till_map(t_game *game, char **line)
{
	char	*temp;

	temp = NULL;
	while (TRUE)
	{
		if(*line == NULL && !ft_get_line(game->map.fd, line))
			return (FALSE);
		if (*line != NULL)
		{
			temp = ft_strdup(*line);
			if (ft_trim_front(&temp, ' ') && temp != NULL && temp[0] == '1')
			{
				free(temp);
				return (TRUE);
			}
			if (!ft_get_map_colors_textures(game, &temp))
			{
				free(temp);
				return (FALSE);
			}
		}
	}
	return (TRUE);
}


int	ft_get_map_config(t_game *game, char **line)
{
	while (ft_get_line(game->map.fd, line) && !ft_is_map_config_loaded(game))
	{
		if (*line != NULL && ft_trim_front(line, ' '))
		{	
			if (!ft_get_map_colors_textures(game, line))
			{
				free(*line);
				return (FALSE);
			}
		}
	}
	if (!ft_is_map_config_loaded(game))
		return (ft_print_error("Missing or incorect map configuration parameters"));	
	if (!ft_check_map_file_till_map(game, line))
	{
		free(*line);
		return (FALSE);
	}
	return (TRUE);
}


//----------Get map------------

void	ft_copy_2d_arr(char **src, char **dest)
{
	int		i;

	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = NULL;
}

void ft_print(char **str)
{
	int	i;
	
	i = 0;
	while(str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int	ft_get_map_grid(t_game *game, char **line)
{
	int		len;
	int		flag;
	char	*temp;
	char	**dd_temp;

	flag = 0;
	game->map.grid = (char **) malloc (2 * sizeof(char *));
	if (!game->map.grid)
		return (FALSE);
		
	if (*line != NULL)
	{
		game->map.col_count = ft_strlen(*line);
		game->map.grid[game->map.row_count] = *line;
		game->map.row_count++;
		game->map.grid[game->map.row_count] = NULL;
	}
	while (ft_get_line(game->map.fd, line))
	{
		temp = ft_strdup(*line);
		ft_trim_front(&temp, ' ');
		if (temp == NULL || ft_strlen(temp) == 0)
		{
			free(temp);
			free(*line);
			flag = 1;
		}
		else if (ft_strlen(temp) != 0 && flag == 1)
		{
			free(temp);
			free(*line);
			return (ft_print_error("Empty lines in map"));
		}
		else
		{
			len = ft_strlen(*line);
			if (len > game->map.col_count)
				game->map.col_count = len;
			free(temp);
			dd_temp = malloc((ft_strlen_2d(game->map.grid) + 1) * sizeof(char *));
			if (!dd_temp)
				return (ft_print_error("Error occurred while reading the map"));
			ft_copy_2d_arr(game->map.grid, dd_temp);
			free(game->map.grid);
			game->map.grid = malloc((game->map.row_count + 2) * sizeof(char *));
			if (!game->map.grid)
				return (ft_print_error("Error occurred while reading the map"));
			ft_copy_2d_arr(dd_temp, game->map.grid);
			free(dd_temp);
			game->map.grid[game->map.row_count] = *line;
			game->map.row_count++;
			game->map.grid[game->map.row_count] = NULL;
		}
	}
	return (TRUE);
}

int	ft_make_grid_square(t_game *game)
{
	int		i;
	int		len;
	char	*tail;

	i = 0;
	while (game->map.grid[i] != NULL)
	{
		len = ft_strlen(game->map.grid[i]);
		if (len < game->map.col_count)
		{
			tail = (char *) malloc ((game->map.col_count - len + 1) * sizeof(char));
			if (!tail)
				return (ft_print_error("Error occurred while reading the map"));
			tail[game->map.col_count - len] = '\0';
			while (len < game->map.col_count)
			{
			 	tail[game->map.col_count - len - 1] = ' ';
				len++;
			}
			game->map.grid[i] = ft_strjoin(game->map.grid[i], tail);
			free(tail);
		}
		i++;
	}
	return (TRUE);
}


int	ft_search_for_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_map_check_line()
{
	return (TRUE);
}


int	ft_is_map_surounded_with_walls(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;	
	while (i < game->map.row_count)
	{
		j = 0;
		flag = 0;
		while (j < game->map.col_count)
		{
			if (!ft_search_for_char(" 10NSEW", game->map.grid[i][j]))
				return (ft_print_error("Not valid symbols in the map found"));
			if (game->map.grid[i][j] == '1')
				flag = 1;
			if (ft_search_for_char("0NSEW", game->map.grid[i][j]) && ( flag == 0 || i == 0 || i == game->map.row_count - 1 || j == 0 || j == game->map.col_count - 1 || game->map.grid[i][j + 1] == ' '))
			//if (ft_search_for_char("0NSEW", game->map.grid[i][j])
			{
				//if (i > 0 && i < game->map.row_count - 1 && j > 0 && j < game>map.col_count)
				ft_print_error("Map is not surrounded by walls");
				return (FALSE);
			}
			if (game->map.grid[i][j] == ' ')
				flag = 0;
			printf("%c", game->map.grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (TRUE);
}

int	ft_get_map_file_content(t_game *game)
{
	char	*line;

	if (!ft_get_map_config(game, &line))
		return (FALSE);
	if (!ft_get_map_grid(game, &line))
		return (FALSE);
	ft_make_grid_square(game);

	ft_is_map_surounded_with_walls(game);
	return (TRUE);
}

int	ft_map_file(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		return (ft_print_error("Invalid number of input arguments"));
	if (ft_strlen(argv[1]) < 5)
		return (ft_print_error("Invalid map file name"));
	if (!ft_check_extention(argv[1], ".cub"))
		return (ft_print_error("Unsupported map file extension"));
	game->map.fd = open (argv[1], O_RDONLY);
	if (game->map.fd == -1)
		return (ft_print_error("No such map file"));
	if (!ft_get_map_file_content(game))
		return (FALSE);
	return (TRUE);
}

void	ft_init(t_game *game)
{
	game->map.fd = -1;
	game->map.floor.rgb[0] = -1;
	game->map.ceiling.rgb[0] = -1;
	game->map.row_count = 0;
	game->map.col_count = 0;
	game->map.no.path = NULL;
	game->map.so.path = NULL;
	game->map.ea.path = NULL;
	game->map.we.path = NULL;
}



void foo(int argc, char **argv)
{
	t_game	game;

	ft_init(&game);
	ft_map_file(argc, argv, &game);
	printf("Map FD: %d\n", game.map.fd);
	printf("RGB: %d %d %d\n", game.map.floor.rgb[0], game.map.floor.rgb[1], game.map.floor.rgb[2]);
	printf("RGB: %d %d %d\n", game.map.ceiling.rgb[0], game.map.ceiling.rgb[1], game.map.ceiling.rgb[2]);
	printf("Texture PATH no: %s\n", game.map.no.path);
	printf("Texture PATH so: %s\n", game.map.so.path);
	printf("Texture PATH ea: %s\n", game.map.ea.path);
	printf("Texture PATH we: %s\n", game.map.we.path);
	printf("Map Row Count: %d\n", game.map.row_count);
	printf("Map Col Count: %d\n", game.map.col_count);
	
	// int i;
	// if(game.map.grid != NULL)
	// {
	// 	i = 0;
	// 	while (game.map.grid[i] != NULL)
	// 	{
	// 		printf(">>%s<<\n", game.map.grid[i]);
	// 		i++;
	// 	}
	// }
	//ft_free_2d_arr(game.map.grid);
	free(game.map.no.path);
	free(game.map.so.path);
	free(game.map.we.path);
	free(game.map.ea.path);
}

int	main(int argc, char **argv)
{

	foo(argc, argv);

	// system("leaks cub3D");fscanf(stdin, "c");
	return (0);
}


