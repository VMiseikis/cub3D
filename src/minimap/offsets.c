/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offsets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:46:37 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/13 14:45:48 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_player_offset_x(t_game *game)
{
	if (game->pl.mm_p.x > (game->mmap.w / 2)
		&& game->mmap.w < game->map.col_c * game->mmap.t_sz)
	{
		if (((game->map.col_c * game->mmap.t_sz) - game->pl.mm_p.x)
			< game->mmap.w / 2)
			game->pl.mm_off.x
				= game->mmap.w - (game->map.col_c * game->mmap.t_sz);
		else
			game->pl.mm_off.x = (game->mmap.w / 2) - game->pl.mm_p.x + 1;
	}
	else if (game->mmap.w > game->map.col_c * game->mmap.t_sz)
		game->pl.mm_off.x
			= (game->mmap.w - (game->map.col_c * game->mmap.t_sz)) / 2;
}

void	ft_player_offset_y(t_game *game)
{
	if (game->pl.mm_p.y > (game->mmap.h / 2)
		&& game->mmap.h < (game->map.row_c * game->mmap.t_sz))
	{
		if (((game->map.row_c * game->mmap.t_sz) - game->pl.mm_p.y)
			< game->mmap.h / 2)
			game->pl.mm_off.y
				= game->mmap.h - (game->map.row_c * game->mmap.t_sz);
		else
			game->pl.mm_off.y = (game->mmap.h / 2) - game->pl.mm_p.y + 1;
	}
	else if (game->mmap.h > (game->map.row_c * game->mmap.t_sz))
		game->pl.mm_off.y
			= (game->mmap.h - (game->map.row_c * game->mmap.t_sz)) / 2;
}

void	ft_mmap_view_offset(t_game *game)
{
	game->mmap.p1.x = 0;
	game->mmap.p1.y = 0;
	if (game->pl.mm_off.x > 0)
		game->mmap.p2.x = game->mmap.w;
	else
	{
		game->mmap.p1.x = game->pl.mm_off.x * -1;
		game->mmap.p2.x = game->mmap.p1.x + game->mmap.w;
	}
	if (game->pl.mm_off.y > 0)
		game->mmap.p2.y = game->mmap.h;
	else
	{
		game->mmap.p1.y = game->pl.mm_off.y * -1;
		game->mmap.p2.y = game->mmap.p1.y + game->mmap.h;
	}
}
