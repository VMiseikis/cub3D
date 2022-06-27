/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:15:13 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/06/27 16:13:09 by vmiseiki         ###   ########.fr       */
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

float	ft_player_look_direction(char c)
{
	if (c == 'N')
		return(PI / 2);
	if (c == 'E')
		return(0);
	if (c == 'S')
		return(3 * PI / 2);
	return(PI);
}

int	ft_get_player(t_game *game, int i, int j)
{
	if (ft_strchr("NSEW", game->map.grid[i][j]))
	{
		if (game->pl.dir != '\0')
			return (ft_print_error("Multiple players"));
		game->pl.dir = game->map.grid[i][j];
		game->pl.angle = ft_player_look_direction(game->map.grid[i][j]);
		game->pl.p.x = j;
		game->pl.p.y = i;
		// game->pl.mm_p.x = j * game->mmap.t_sz + (game->mmap.t_sz / 2);
		// game->pl.mm_p.y = i * game->mmap.t_sz + (game->mmap.t_sz / 2);
		game->pl.mm_p.x = j * game->mmap.t_sz;
		game->pl.mm_p.y = i * game->mmap.t_sz;
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
			if (!ft_get_player(game, i, j)
				|| !ft_is_map_surrounded_by_wall(game, i, j))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}
