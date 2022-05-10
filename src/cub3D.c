/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:30:20 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/10 19:51:00 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_print_error(char *str)
{
	printf("Error: %s\n", str);
	//printf("Program was terminated!\n");
	return (FALSE);
}

int	ft_get_map_file_content(t_game *game)
{
	char	*line;

	if (!ft_get_map_config(game, &line))
		return (FALSE);
	if (!ft_get_map_grid(game, &line))
		return (FALSE);
	if (!ft_trim_2d_back(game, "") || !ft_make_grid_square(game) || !ft_check_map(game))
		return (FALSE);
	return (TRUE);
}

int	ft_handle_map_file(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		return (ft_print_error("Invalid number of input arguments"));
	if (ft_strlen(argv[1]) < 5)
		return (ft_print_error("Invalid map file name"));
	if (!ft_is_extention_valid(argv[1], ".cub"))
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
	game->map.row_c = 0;
	game->map.col_c = 0;
	game->map.no.path = NULL;
	game->map.so.path = NULL;
	game->map.ea.path = NULL;
	game->map.we.path = NULL;
}

void foo(int argc, char **argv)
{
	t_game	game;

	ft_init(&game);
	ft_handle_map_file(argc, argv, &game);
	// printf("Map FD: %d\n", game.map.fd);
	printf("RGB: %d %d %d\n", game.map.floor.rgb[0], game.map.floor.rgb[1], game.map.floor.rgb[2]);
	printf("RGB: %d %d %d\n", game.map.ceiling.rgb[0], game.map.ceiling.rgb[1], game.map.ceiling.rgb[2]);
	printf("Texture PATH no: %s\n", game.map.no.path);
	printf("Texture PATH so: %s\n", game.map.so.path);
	printf("Texture PATH ea: %s\n", game.map.ea.path);
	printf("Texture PATH we: %s\n", game.map.we.path);
	printf("Map Row Count: %d\n", game.map.row_c);
	printf("Map Col Count: %d\n", game.map.col_c);
	
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
	// ft_free_2d_arr(game.map.grid);
	// free(game.map.no.path);
	// free(game.map.so.path);
	// free(game.map.we.path);
	// free(game.map.ea.path);
}

int	main(int argc, char **argv)
{


	foo(argc, argv);

	system("leaks cub3D");fscanf(stdin, "c");
	return (0);
}



