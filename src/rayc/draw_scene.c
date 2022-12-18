/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:59:12 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/17 21:12:58 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_get_x(t_game *game)
{
	if (game->ray.type == 'h' && game->ray.ang > PI2)
		return ((int)(game->ray.end.x) % game->map.t_sz);
	if (game->ray.type == 'h' && game->ray.ang <= PI2)
		return (game->map.t_sz - (int)(game->ray.end.x) % game->map.t_sz - 1);
	if (game->ray.type == 'v' && game->ray.ang > PI1 && game->ray.ang < PI3)
		return (game->map.t_sz - (int)(game->ray.end.y) % game->map.t_sz - 1);
	if (game->ray.type == 'v' && (game->ray.ang <= PI1 || game->ray.ang >= PI3))
		return ((int)(game->ray.end.y) % game->map.t_sz);
	return (0);
}

t_img	*ft_get_txt(t_game *game)
{
	if (game->map.grid[game->ray.grid_p.y][game->ray.grid_p.x] == 'D')
		return (&game->txt.door);
	if (game->ray.type == 'h' && game->ray.ang > PI2)
		return (&game->txt.no_w);
	if (game->ray.type == 'h' && game->ray.ang <= PI2)
		return (&game->txt.so_w);
	if (game->ray.type == 'v' && game->ray.ang > PI1 && game->ray.ang < PI3)
		return (&game->txt.we_w);
	if (game->ray.type == 'v' && (game->ray.ang <= PI1 || game->ray.ang >= PI3))
		return (&game->txt.ea_w);
	return (NULL);
}

void	ft_draw_wall_texture(t_game *game, int i)
{
	int		j;	
	t_img	*txt;

	j = 0;
	txt = ft_get_txt(game);
	if (txt != NULL)
	{
		while (j < game->w_h)
		{
			*(unsigned int *)
			(ft_get_pixel_info(&game->frame, i, j + game->start.y))
			= (*(unsigned int *)
			(ft_get_pixel_info(txt, ft_get_x(game),
			(j - game->w_h_off + PRC) * game->sf)));
			j++;
		}
	}
}

void	ft_draw_pseudo_3d(t_game *game, int i)
{	
	double	half_g_h;
	double	half_w_h;

	game->w_h_off = 0;
	game->w_h = ((HEIGHT * game->map.t_sz) / (game->ray.len)) + PRC;
	game->sf = game->map.t_sz / game->w_h;
	if (game->w_h >= HEIGHT)
	{
		game->w_h_off = ((HEIGHT - game->w_h) / 2);
		game->w_h = HEIGHT;
	}
	half_g_h = (HEIGHT / 2);
	half_w_h = (game->w_h / 2);
	ft_save_point(&game->start, i, (half_g_h - half_w_h));
	ft_save_point(&game->end, i, (half_g_h + half_w_h));
	ft_draw_wall_texture(game, i);
	if (half_g_h - half_w_h != 0)
	{
		ft_save_point(&game->start, i, 0);
		ft_save_point(&game->end, i, half_g_h - half_w_h);
		ft_draw_line(game, &game->frame, game->txt.ceiling);
		ft_save_point(&game->start, i, half_g_h + half_w_h - 1);
		ft_save_point(&game->end, i, HEIGHT);
		ft_draw_line(game, &game->frame, game->txt.floor);
	}
}
