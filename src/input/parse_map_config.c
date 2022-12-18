/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:48:25 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/10 22:12:27 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_parse_floor_ceiling_colors(t_game *game, char **line)
{
	char	*temp;

	if ((line[0][0] == 'F' && game->txt.floor != -1)
		|| (line[0][0] == 'C' && game->txt.ceiling != -1))
		return (ft_print_err
			("Duplicate map configuration entries found in map file"));
	temp = ft_substr(*line, 2, ft_strlen(*line));
	if (!ft_trim_str_front(&temp, ' ')
		|| !ft_store_map_fc_colors(game, line[0][0], temp))
	{
		free(temp);
		return (FALSE);
	}
	free(temp);
	return (TRUE);
}

int	ft_get_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_store_trgb(t_game *game, char type, int *rgb)
{
	if (type == 'F')
		game->txt.floor = ft_get_trgb(0, rgb[0], rgb[1], rgb[2]);
	else
		game->txt.ceiling = ft_get_trgb(0, rgb[0], rgb[1], rgb[2]);
}

int	ft_store_map_fc_colors(t_game *game, char type, char *src)
{
	int		i;
	int		nbr;
	int		rgb[3];
	char	**temp;

	temp = ft_split(src, ',');
	if (temp == NULL || ft_strlen_2d(temp) != 3)
	{
		ft_free_2d_arr(temp);
		return (ft_print_err("Incorrect map color rgb parameter"));
	}
	i = -1;
	while (++i < 3)
	{
		if (!ft_check_rgb(&temp[i], &nbr))
		{
			ft_free_2d_arr(temp);
			return (FALSE);
		}
		rgb[i] = nbr;
	}
	ft_store_trgb(game, type, rgb);
	ft_free_2d_arr(temp);
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
	if (line[0][0] == 'N' && game->txt.no_w.path == NULL)
		game->txt.no_w.path = path;
	else if (line[0][0] == 'S' && game->txt.so_w.path == NULL)
		game->txt.so_w.path = path;
	else if (line[0][0] == 'E' && game->txt.ea_w.path == NULL)
		game->txt.ea_w.path = path;
	else if (line[0][0] == 'W' && game->txt.we_w.path == NULL)
		game->txt.we_w.path = path;
	else
	{
		free(path);
		return (ft_print_err
			("Duplicate map configuration entries found in map file"));
	}
	return (TRUE);
}
