/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:08:22 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/10 18:31:45 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_read_till_map_found_in_file(t_game *game, char **line)
{
	char	*sub;
	char	*temp;

	ft_skip_empty_lines_from_file(game, line);
	if (*line)
	{
		temp = ft_strdup(*line);
		ft_trim_str_front(&temp, ' ');
		sub = ft_substr(temp, 0, 3);
		if (ft_strcmp(sub, "NO ") == 0 || ft_strcmp(sub, "SO ") == 0
			|| ft_strcmp(sub, "EA ") == 0 || ft_strcmp(sub, "WE ") == 0
			|| (temp[1] == ' ' && (temp[0] == 'F' || temp[0] == 'C')))
		{
			free (sub);
			free(temp);
			return (ft_print_error("Duplicate map configuration entries found in map file"));
		}
		free (sub);
		free(temp);
		return (TRUE);
	}
	return (FALSE);
}

int	ft_get_map_colors_textures(t_game *game, char **line)
{
	char	*sub;

	if (!ft_strchr("NSEWFC", *line[0]))
		return (ft_print_error("Unsupported, missing or corrupted entries found in map file"));
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
	free(sub);
	return (TRUE);
}

int	ft_get_map_config(t_game *game, char **line)
{
	while (ft_get_line(game->map.fd, line) && !ft_is_map_config_loaded(game))
	{
		if (*line != NULL && ft_trim_str_front(line, ' '))
		{	
			if (!ft_get_map_colors_textures(game, line))
			{
				free(*line);
				return (FALSE);
			}
			free (*line);
		}
	}
	if (!ft_is_map_config_loaded(game))
		return (ft_print_error("Missing or incorect map configuration parameters"));
	if (!ft_read_till_map_found_in_file(game, line))
	{
		free(*line);
		return (FALSE);
	}
	return (TRUE);
}
