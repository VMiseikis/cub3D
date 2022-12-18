/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:35:05 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/14 20:47:41 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_save_point(t_point_d *p, double x, double y)
{
	p->x = x;
	p->y = y;
}

void	ft_save_point_i(t_point_i *p, int x, int y)
{
	p->x = x;
	p->y = y;
}

void	ft_update_pl_coord(t_game *game, double x, double y)
{
	game->pl.mm_p.x = x / (game->map.t_sz / game->mmap.t_sz);
	game->pl.mm_p.y = y / (game->map.t_sz / game->mmap.t_sz);
	game->pl.grid_p.x = (int)(x / game->map.t_sz);
	game->pl.grid_p.y = (int)(y / game->map.t_sz);
}
