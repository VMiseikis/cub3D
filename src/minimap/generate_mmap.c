/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_mmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:00:08 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:50:52 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_draw_player_in_mmap(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->txt.pl.w)
	{
		j = 0;
		while (j < game->txt.pl.h)
		{
			ft_save_point(&game->start,
				game->pl.mm_p.x + game->pl.mm_off.x - 4 + j,
				game->pl.mm_p.y + game->pl.mm_off.y - 4 + i);
			ft_save_point(&game->end, i, j);
			if (ft_ignore_black_color(&game->txt.pl, i, j))
				ft_copy_pixel(game, &game->txt.pl, &game->mmap.view);
			j++;
		}
		i++;
	}
}

void	ft_draw_mmap_view(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->mmap.w)
	{
		j = 0;
		while (j < game->mmap.h)
		{
			ft_save_point(&game->start, i, j);
			ft_save_point(&game->end, i + game->mmap.p1.x, j + game->mmap.p1.y);
			ft_copy_pixel(game, &game->mmap.full, &game->mmap.view);
			j++;
		}
		i++;
	}
	ft_draw_player_in_mmap(game);
}

void	ft_full_mmap_offset(t_game *game, t_point_i *off)
{
	off->x = 0;
	if (game->map.col_c * game->mmap.t_sz < game->mmap.w)
		off->x = (game->mmap.w - (game->map.col_c * game->mmap.t_sz)) / 2;
	off->y = 0;
	if (game->map.row_c * game->mmap.t_sz < game->mmap.h)
		off->y = (game->mmap.h - (game->map.row_c * game->mmap.t_sz)) / 2;
}

void	ft_generate_full_mmap_img(t_game *game)
{
	int			i;
	int			j;
	t_point_i	off;

	i = 0;
	ft_full_mmap_offset(game, &off);
	while (i < game->map.row_c)
	{
		j = 0;
		while (j < game->map.col_c)
		{
			ft_save_point(&game->start,
				j * game->mmap.t_sz + off.x, i * game->mmap.t_sz + off.y);
			ft_save_point(&game->end,
				j * game->mmap.t_sz + game->mmap.t_sz + off.x,
				i * game->mmap.t_sz + game->mmap.t_sz + off.y);
			if (game->map.grid[i][j] == '1')
				ft_draw_rectangle(game, game->mmap.full, 0x0000FF, 0x0000FF);
			else if (game->map.grid[i][j] == '0')
				ft_draw_rectangle(game, game->mmap.full, 0x36454F, 0x000000);
			j++;
		}
		i++;
	}
}
