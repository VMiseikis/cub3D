/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:17:33 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:54:14 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_init(t_game *game)
{
	game->map.fd = -1;
	game->map.row_c = 0;
	game->map.col_c = 0;
	game->map.grid = NULL;
	game->map.t_sz = 64;
	game->txt.no_w.path = NULL;
	game->txt.so_w.path = NULL;
	game->txt.ea_w.path = NULL;
	game->txt.we_w.path = NULL;
	game->txt.pl.img = NULL;
	game->mmap.full.img = NULL;
	game->mmap.view.img = NULL;
	game->frame.img = NULL;
	game->window = NULL;
	game->txt.floor = -1;
	game->txt.ceiling = -1;
	game->pl.dir = '\0';
	game->ray_step_limit = 448;
	game->start.x = 0;
	game->start.y = 0;
}

void	ft_more_init(t_game *game)
{
	game->end.x = 0;
	game->end.y = 0;
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.s = 0;
	game->keys.w = 0;
	game->keys.q = 0;
	game->keys.e = 0;
	game->keys.left_arrow = 0;
	game->keys.right_arrow = 0;
	game->keys.pause = 0;
	game->dist = 16;
	game->maus_x = WIDTH / 2;
	game->maus_y = HEIGHT / 2;
	game->ray.grid_p.x = 0;
	game->ray.grid_p.y = 0;
	game->mmap.t_sz = 16;
	game->mmap.w = 256;
	game->mmap.h = 192;
}

void	ft_define(t_game *game)
{
	game->dtpp = (WIDTH / 2) / tan(FOV / 2);
	game->pl.delta_x = cos(game->pl.ang);
	game->pl.delta_y = sin(game->pl.ang);
	game->map.h_t_sz = game->map.t_sz / 2;
	game->ray_max_dist = ft_get_hypotenuse
		(game->map.col_c * 64, 0, game->map.row_c * 64, 0);
}

void	ft_init_mlx_images(t_game *game)
{
	game->frame.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->frame.addr = mlx_get_data_addr
		(game->frame.img, &game->frame.b_per_px, &game->frame.l_len,
			&game->frame.endian);
	game->mmap.full.img
		= mlx_new_image(game->mlx, game->mmap.p1.x, game->mmap.p1.y);
	game->mmap.full.addr = mlx_get_data_addr
		(game->mmap.full.img, &game->mmap.full.b_per_px,
			&game->mmap.full.l_len, &game->mmap.full.endian);
	game->mmap.view.img = mlx_new_image(game->mlx, game->mmap.w, game->mmap.h);
	game->mmap.view.addr = mlx_get_data_addr
		(game->mmap.view.img, &game->mmap.view.b_per_px,
			&game->mmap.view.l_len, &game->mmap.view.endian);
}

void	ft_init_mmap(t_game *game)
{
	game->mmap.p1.x = game->map.col_c * game->mmap.t_sz;
	if (game->mmap.p1.x < game->mmap.w)
		game->mmap.p1.x = game->mmap.w;
	game->mmap.p1.y = game->map.row_c * game->mmap.t_sz;
	if (game->mmap.p1.y < game->mmap.h)
		game->mmap.p1.y = game->mmap.h;
}
