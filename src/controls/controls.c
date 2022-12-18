/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:28:25 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:58:00 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_show_hide_mouse(int keycode, t_game *game)
{
	if (keycode == 50)
	{
		if (game->keys.pause == 0)
		{
			game->keys.pause = 1;
			mlx_mouse_show();
		}
		else
		{
			game->keys.pause = 0;
			mlx_mouse_hide();
		}
	}
}

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == 53)
		ft_exit(game);
	if (keycode == 13)
		game->keys.w = 1;
	if (keycode == 0)
		game->keys.a = 1;
	if (keycode == 1)
		game->keys.s = 1;
	if (keycode == 2)
		game->keys.d = 1;
	if (keycode == 123)
		game->keys.left_arrow = 1;
	if (keycode == 124)
		game->keys.right_arrow = 1;
	ft_show_hide_mouse(keycode, game);
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == 13)
		game->keys.w = 0;
	if (keycode == 0)
		game->keys.a = 0;
	if (keycode == 1)
		game->keys.s = 0;
	if (keycode == 2)
		game->keys.d = 0;
	if (keycode == 123)
		game->keys.left_arrow = 0;
	if (keycode == 124)
		game->keys.right_arrow = 0;
	return (0);
}

void	ft_key_rotation(t_game *game)
{
	if (game->keys.left_arrow == 1)
	{
		game->pl.ang = game->pl.ang - 0.05;
		game->pl.delta_x = cos(game->pl.ang);
		game->pl.delta_y = sin(game->pl.ang);
	}
	if (game->keys.right_arrow == 1)
	{
		game->pl.ang = game->pl.ang + 0.05;
		game->pl.delta_x = cos(game->pl.ang);
		game->pl.delta_y = sin(game->pl.ang);
	}
}

void	ft_key_actions(t_game *game)
{
	ft_key_w_action(game);
	ft_key_s_action(game);
	ft_key_a_action(game);
	ft_key_d_action(game);
	ft_key_rotation(game);
}
