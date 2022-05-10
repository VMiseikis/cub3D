/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:07:50 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/10 18:01:36 by vmiseiki         ###   ########.fr       */
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
