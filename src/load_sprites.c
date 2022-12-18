/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:14:34 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:51:56 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_get_sprite_address(t_game *game)
{
	game->txt.no_w.addr = mlx_get_data_addr(game->txt.no_w.img,
			&game->txt.no_w.b_per_px, &game->txt.no_w.l_len,
			&game->txt.no_w.endian);
	game->txt.so_w.addr = mlx_get_data_addr(game->txt.so_w.img,
			&game->txt.so_w.b_per_px, &game->txt.so_w.l_len,
			&game->txt.so_w.endian);
	game->txt.ea_w.addr = mlx_get_data_addr(game->txt.ea_w.img,
			&game->txt.ea_w.b_per_px, &game->txt.ea_w.l_len,
			&game->txt.ea_w.endian);
	game->txt.we_w.addr = mlx_get_data_addr(game->txt.we_w.img,
			&game->txt.we_w.b_per_px, &game->txt.we_w.l_len,
			&game->txt.we_w.endian);
	game->txt.pl.addr = mlx_get_data_addr(game->txt.pl.img,
			&game->txt.pl.b_per_px, &game->txt.pl.l_len,
			&game->txt.pl.endian);
}

void	ft_load_sprite_img(t_game *game)
{
	game->txt.no_w.img = mlx_xpm_file_to_image(game->mlx,
			game->txt.no_w.path, &game->txt.no_w.w, &game->txt.no_w.h);
	game->txt.so_w.img = mlx_xpm_file_to_image(game->mlx,
			game->txt.so_w.path, &game->txt.so_w.w, &game->txt.so_w.h);
	game->txt.ea_w.img = mlx_xpm_file_to_image(game->mlx,
			game->txt.ea_w.path, &game->txt.ea_w.w, &game->txt.ea_w.h);
	game->txt.we_w.img = mlx_xpm_file_to_image(game->mlx,
			game->txt.we_w.path, &game->txt.we_w.w, &game->txt.we_w.h);
	game->txt.pl.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/circle8.xpm", &game->txt.pl.w, &game->txt.pl.h);
}

int	ft_load_sprites(t_game *game)
{
	ft_load_sprite_img(game);
	if (!game->txt.no_w.img || !game->txt.so_w.img
		|| !game->txt.ea_w.img || !game->txt.we_w.img
		|| !game->txt.pl.img)
		return (ft_print_err("Error occurred while loading sprites!"));
	ft_get_sprite_address(game);
	return (TRUE);
}
