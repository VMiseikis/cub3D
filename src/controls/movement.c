/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:53:55 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:46:11 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_key_w_action(t_game *game)
{
	if (game->keys.w == 1)
	{
		ft_save_point(&game->start,
			game->pl.m_p.x + game->pl.delta_x, game->pl.m_p.y);
		ft_save_point(&game->end,
			game->start.x - game->dist, game->start.y - game->dist);
		if (game->map.grid
			[game->pl.grid_p.y][(int)(game->start.x / game->map.t_sz)] != '1'
			&& !ft_check_arround(game))
			game->pl.m_p.x = game->start.x;
		ft_save_point(&game->start,
			game->pl.m_p.x, game->pl.m_p.y + game->pl.delta_y);
		ft_save_point(&game->end,
			game->start.x - game->dist, game->start.y - game->dist);
		if (game->map.grid[(int)(game->start.y / game->map.t_sz)]
			[(int)(game->start.x / game->map.t_sz)] != '1'
			&& !ft_check_arround(game))
			game->pl.m_p.y = game->start.y;
		ft_update_pl_coord(game, game->pl.m_p.x, game->pl.m_p.y);
	}
}

void	ft_key_s_action(t_game *game)
{
	if (game->keys.s == 1)
	{
		ft_save_point(&game->start,
			game->pl.m_p.x - game->pl.delta_x, game->pl.m_p.y);
		ft_save_point(&game->end,
			game->start.x - game->dist, game->start.y - game->dist);
		if (game->map.grid
			[game->pl.grid_p.y][(int)(game->start.x / game->map.t_sz)] != '1'
			&& !ft_check_arround(game))
			game->pl.m_p.x = game->start.x;
		ft_save_point(&game->start,
			game->pl.m_p.x, game->pl.m_p.y - game->pl.delta_y);
		ft_save_point(&game->end,
			game->start.x - game->dist, game->start.y - game->dist);
		if (game->map.grid[(int)(game->start.y / game->map.t_sz)]
			[(int)(game->start.x / game->map.t_sz)] != '1'
			&& !ft_check_arround(game))
			game->pl.m_p.y = game->start.y;
		ft_update_pl_coord(game, game->pl.m_p.x, game->pl.m_p.y);
	}
}

void	ft_key_a_action(t_game *game)
{
	if (game->keys.a == 1)
	{
		ft_save_point(&game->start,
			game->pl.m_p.x + game->pl.delta_y, game->pl.m_p.y);
		ft_save_point(&game->end,
			game->start.x - game->dist, game->start.y - game->dist);
		if (game->map.grid
			[game->pl.grid_p.y][(int)(game->start.x / game->map.t_sz)] != '1'
			&& !ft_check_arround(game))
			game->pl.m_p.x = game->start.x;
		ft_save_point(&game->start,
			game->pl.m_p.x, game->pl.m_p.y - game->pl.delta_x);
		ft_save_point(&game->end,
			game->start.x - game->dist, game->start.y - game->dist);
		if (game->map.grid[(int)(game->start.y / game->map.t_sz)]
			[(int)(game->start.x / game->map.t_sz)] != '1'
			&& !ft_check_arround(game))
			game->pl.m_p.y = game->start.y;
		ft_update_pl_coord(game, game->pl.m_p.x, game->pl.m_p.y);
	}
}

void	ft_key_d_action(t_game *game)
{
	if (game->keys.d == 1)
	{
		ft_save_point(&game->start,
			game->pl.m_p.x - game->pl.delta_y, game->pl.m_p.y);
		ft_save_point(&game->end,
			game->start.x - game->dist, game->start.y - game->dist);
		if (game->map.grid
			[game->pl.grid_p.y][(int)(game->start.x / game->map.t_sz)] != '1'
			&& !ft_check_arround(game))
			game->pl.m_p.x = game->start.x;
		ft_save_point(&game->start,
			game->pl.m_p.x, game->pl.m_p.y + game->pl.delta_x);
		ft_save_point(&game->end,
			game->start.x - game->dist, game->start.y - game->dist);
		if (game->map.grid[(int)(game->start.y / game->map.t_sz)]
			[(int)(game->start.x / game->map.t_sz)] != '1'
			&& !ft_check_arround(game))
			game->pl.m_p.y = game->start.y;
		ft_update_pl_coord(game, game->pl.m_p.x, game->pl.m_p.y);
	}
}
