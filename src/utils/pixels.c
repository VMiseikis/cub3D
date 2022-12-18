/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:20:10 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:41:37 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	*ft_get_pixel_info(t_img *img, int x, int y)
{
	return (img->addr + (y * img->l_len + x * (img->b_per_px / 8)));
}

void	ft_set_pixel_color(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->l_len + x * (img->b_per_px / 8));
	*(unsigned int *)dest = color;
}

void	ft_copy_pixel(t_game *game, t_img *img_1, t_img *img_2)
{
	char	*dest;
	char	*input;

	dest = img_2->addr + ((int)game->start.y * img_2->l_len
			+ ((int)game->start.x * (img_2->b_per_px / 8)));
	input = img_1->addr + ((int)game->end.y * img_1->l_len
			+ ((int)game->end.x * (img_1->b_per_px / 8)));
	*(unsigned int *)dest = *(unsigned int *)input;
}

int	ft_ignore_black_color(t_img *tile, int i, int j)
{
	char	*pixel;

	pixel = tile->addr + (j * tile->l_len
			+ i * (tile->b_per_px / 8));
	if (*(unsigned int *)pixel != 0x000001)
		return (1);
	return (0);
}
