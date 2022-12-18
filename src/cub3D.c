/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:30:20 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:52:34 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_frames(t_game *game)
{
	ft_key_actions(game);
	game->pl.ang = ft_reset_angle(game->pl.ang);
	ft_cast_rays(game);
	ft_player_offset_x(game);
	ft_player_offset_y(game);
	ft_mmap_view_offset(game);
	ft_draw_mmap_view(game);
	mlx_put_image_to_window(game->mlx, game->window, game->frame.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, game->mmap.view.img, 0, 0);
	return (TRUE);
}

void	ft_render(t_game *game)
{
	ft_define(game);
	game->mlx = mlx_init();
	mlx_mouse_hide();
	if (!ft_load_sprites(game))
		ft_exit(game);
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	ft_init_mmap(game);
	ft_init_mlx_images(game);
	ft_generate_full_mmap_img(game);
	mlx_loop_hook (game->mlx, &ft_frames, game);
	mlx_hook(game->window, 2, 1L << 0, ft_key_press, game);
	mlx_hook(game->window, 3, 1L << 1, ft_key_release, game);
	mlx_hook(game->window, 6, 1L << 6, ft_mouse_move, game);
	mlx_hook(game->window, 17, 1L << 17, ft_exit, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_init(&game);
	ft_more_init(&game);
	if (ft_handle_map_file(argc, argv, &game))
		ft_render(&game);
	ft_free_all(&game);
	return (0);
}
