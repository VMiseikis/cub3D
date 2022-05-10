/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:15:13 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/09 21:45:39 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_make_grid_square(t_game *game)
{
	int		i;
	int		len;
	char	*tail;

	i = 0;
	while (game->map.grid[i] != NULL)
	{
		len = ft_strlen(game->map.grid[i]);
		if (len < game->map.col_c)
		{
			tail = (char *) malloc ((game->map.col_c - len + 1) * sizeof(char));
			if (!tail)
				return (ft_print_error("Error occurred while reading the map"));
			tail[game->map.col_c - len] = '\0';
			while (len < game->map.col_c)
			{
				tail[game->map.col_c - len - 1] = ' ';
				len++;
			}
			game->map.grid[i] = ft_strjoin(game->map.grid[i], tail);
			free(tail);
		}
		i++;
	}
	return (TRUE);
}

int	ft_check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.row_c)
	{
		j = 0;
		while (j < game->map.col_c)
		{
			if (!ft_strchr(" 10NSEW", game->map.grid[i][j]))
				return (ft_print_error("Not valid symbols in the map found"));
			if (ft_strchr("0NSEW", game->map.grid[i][j]) && (i == 0 || j == 0
				|| i == game->map.row_c - 1 || j == game->map.col_c - 1))
				return (ft_print_error("Map is not surrounded by walls"));
			if (ft_strchr("0NSEW", game->map.grid[i][j])
				&& (game->map.grid[i + 1][j] == ' '
				|| game->map.grid[i - 1][j] == ' '
				|| game->map.grid[i][j + 1] == ' '
				|| game->map.grid[i][j - 1] == ' '))
				return (ft_print_error("Map is not surrounded by walls"));
			j++;
		}
		i++;
	}
	return (TRUE);
}
