/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:18:04 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/16 16:05:59 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (game->keys.pause == 0)
	{
		mlx_mouse_move(game->window, game->maus_x, game->maus_y);
		if (x < game->maus_x)
		{
			game->pl.ang = game->pl.ang - 0.03;
			game->pl.delta_x = cos(game->pl.ang);
			game->pl.delta_y = sin(game->pl.ang);
		}
		if (x > game->maus_x)
		{
			game->pl.ang = game->pl.ang + 0.03;
			game->pl.delta_x = cos(game->pl.ang);
			game->pl.delta_y = sin(game->pl.ang);
		}
	}
	return (0);
}
