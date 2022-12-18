/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_rectangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:44:19 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:51:29 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_draw_rectangle(t_game *game, t_img img, int color1, int color2)
{
	int	i;
	int	j;

	i = game->start.x;
	while (i < game->end.x)
	{
		j = game->start.y;
		while (j < game->end.y)
		{
			if (i == game->start.x
				|| j == game->start.y
				|| i == (game->end.x - 1)
				|| j == (game->end.y - 1))
				ft_set_pixel_color(&img, i, j, color1);
			else
				ft_set_pixel_color(&img, i, j, color2);
			j++;
		}
		i++;
	}
}
