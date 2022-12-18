/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:42:36 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/14 20:09:04 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_dda(t_game *game)
{
	game->dda.dx = (game->end.x - game->start.x);
	game->dda.dy = (game->end.y - game->start.y);
	if (fabs(game->dda.dx) >= fabs(game->dda.dy))
		game->dda.steps = fabs(game->dda.dx);
	else
		game->dda.steps = fabs(game->dda.dy);
	game->dda.dx = game->dda.dx / game->dda.steps;
	game->dda.dy = game->dda.dy / game->dda.steps;
	game->dda.x = game->start.x;
	game->dda.y = game->start.y;
}

void	ft_draw_line(t_game *game, t_img *img, int color)
{
	int	i;

	i = 0;
	ft_dda(game);
	while (i < game->dda.steps)
	{
		ft_set_pixel_color(img, game->dda.x, game->dda.y, color);
		game->dda.x += game->dda.dx;
		game->dda.y += game->dda.dy;
		i++;
	}
}
