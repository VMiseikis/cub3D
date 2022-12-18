/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:08:22 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/10 22:13:47 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_skip_empty_lines_from_file(t_game *game, char **line)
{
	if (*line == NULL || ft_has_only_spaces(*line))
	{
		while (ft_get_line(game->map.fd, line)
			&& (*line == NULL || ft_has_only_spaces(*line)))
		{	
			if (*line)
				free(*line);
			continue ;
		}
	}
}

int	ft_read_till_map_found_in_file(t_game *game, char **line)
{
	char	*temp;

	ft_skip_empty_lines_from_file(game, line);
	if (*line)
	{
		temp = ft_strdup(*line);
		ft_trim_str_front(&temp, ' ');
		if (ft_strncmp(temp, "NO", 2) == 0
			|| ft_strncmp(temp, "SO", 2) == 0
			|| ft_strncmp(temp, "EA", 2) == 0
			|| ft_strncmp(temp, "WE", 2) == 0
			|| temp[0] == 'F' || temp[0] == 'C')
		{
			free(temp);
			return (ft_print_err
				("Duplicate map configuration entries found in map file"));
		}
		free(temp);
		return (TRUE);
	}
	return (FALSE);
}

int	ft_get_map_colors_textures(t_game *game, char **line)
{
	if ((ft_strncmp(*line, "F ", 2) == 0
			|| ft_strncmp(*line, "C ", 2) == 0)
		&& ft_strlen(*line) > 6)
	{
		if (!ft_parse_floor_ceiling_colors(game, line))
			return (FALSE);
	}
	else if ((ft_strncmp(*line, "NO ", 3) == 0
			|| ft_strncmp(*line, "SO ", 3) == 0
			|| ft_strncmp(*line, "EA ", 3) == 0
			|| ft_strncmp(*line, "WE ", 3) == 0)
		&& ft_strlen(*line) > 9)
	{
		if (!ft_store_wall_text_path(game, line))
			return (FALSE);
	}
	return (TRUE);
}

int	ft_get_map_config(t_game *game, char **line)
{
	while (ft_get_line(game->map.fd, line) && !ft_is_map_config_loaded(game))
	{
		if (*line != NULL && ft_trim_str_front(line, ' '))
		{	
			if (!ft_strchr("NSEWFC", *line[0]))
				return (ft_print_err
					("Unsupported, missing or corrupted entries found in map"));
			if (!ft_get_map_colors_textures(game, line))
			{
				free(*line);
				return (FALSE);
			}
			free (*line);
		}
	}
	if (!ft_is_map_config_loaded(game))
		return (ft_print_err
			("Missing or incorect map configuration parameters"));
	if (!ft_read_till_map_found_in_file(game, line))
	{
		free(*line);
		return (FALSE);
	}
	return (TRUE);
}
