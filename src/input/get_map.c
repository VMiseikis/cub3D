/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:07:17 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/10 22:08:02 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_read_map_from_file(t_game *game, char **line, char **dd_temp, int len)
{
	if (!*line || ft_has_only_spaces(*line))
	{
		free(*line);
		*line = ft_strdup("");
	}
	else
		len = ft_strlen(*line);
	if (len > game->map.col_c)
		game->map.col_c = len;
	dd_temp = malloc((game->map.row_c + 1) * sizeof(char *));
	if (!dd_temp)
		return (ft_print_err("Error occurred while reading the map"));
	ft_2dstrcpy(game->map.grid, dd_temp);
	free(game->map.grid);
	game->map.grid = malloc((game->map.row_c + 2) * sizeof(char *));
	if (!game->map.grid)
		return (ft_print_err("Error occurred while reading the map"));
	ft_2dstrcpy(dd_temp, game->map.grid);
	free(dd_temp);
	game->map.grid[game->map.row_c] = *line;
	game->map.row_c++;
	game->map.grid[game->map.row_c] = NULL;
	return (TRUE);
}

int	ft_get_map_grid(t_game *game, char **line)
{
	int		len;
	char	**dd_temp;

	len = 0;
	dd_temp = NULL;
	game->map.grid = (char **) malloc (2 * sizeof(char *));
	if (!game->map.grid)
		return (FALSE);
	if (*line != NULL)
	{
		game->map.col_c = ft_strlen(*line);
		game->map.grid[game->map.row_c] = *line;
		game->map.row_c++;
		game->map.grid[game->map.row_c] = NULL;
	}
	while (ft_get_line(game->map.fd, line))
	{	
		if (!ft_read_map_from_file(game, line, dd_temp, len))
			return (FALSE);
	}
	return (TRUE);
}
