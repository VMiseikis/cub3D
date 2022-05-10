/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:48:25 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/10 18:34:06 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
	if (!ft_trim_str_front(&temp, ' ') || !ft_store_map_fc_colors(game, line[0][0], temp))
	{
		free(temp);
		return (FALSE);
	}
	free(temp);
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
	i = -1;
	while (++i < 3)
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
	}
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
