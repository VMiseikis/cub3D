/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colisions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:32:36 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:43:02 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_rec_circle(t_point_d p, int yc, int xc, int r)
{
	int	xn;
	int	yn;
	int	dx;
	int	dy;

	xn = ft_max(p.x, ft_min(xc, p.x + 64));
	yn = ft_max(p.y, ft_min(yc, p.y + 64));
	dx = xn - xc;
	dy = yn - yc;
	if ((dx * dx + dy * dy) <= r * r)
		return (0);
	return (1);
}

int	ft_rec_rec(t_game *game, t_point_d p, double i, double j)
{
	if (p.x < (i + game->map.t_sz) && p.x + game->dist * 2 - 1 > i
		&& p.y < (j + game->map.t_sz) && p.y + game->dist * 2 - 1 > j)
		return (TRUE);
	return (FALSE);
}

int	ft_check_tile(t_game *game, char *str, int x, int y)
{
	if (ft_strchr(str, game->map.grid[y][x])
		&& ft_rec_rec(game, game->end,
			x * game->map.t_sz, y * game->map.t_sz))
		return (TRUE);
	return (FALSE);
}

int	ft_check_arround(t_game *game)
{
	t_point_i	p;

	p.x = game->start.x / game->map.t_sz;
	p.y = game->start.y / game->map.t_sz;
	if (ft_check_tile(game, "1D", p.x, p.y - 1)
		|| ft_check_tile(game, "1D", p.x - 1, p.y - 1)
		|| ft_check_tile(game, "1D", p.x + 1, p.y - 1)
		|| ft_check_tile(game, "1D", p.x, p.y + 1)
		|| ft_check_tile(game, "1D", p.x - 1, p.y + 1)
		|| ft_check_tile(game, "1D", p.x + 1, p.y + 1)
		|| ft_check_tile(game, "1D", p.x - 1, p.y)
		|| ft_check_tile(game, "1D", p.x + 1, p.y))
		return (TRUE);
	return (FALSE);
}
