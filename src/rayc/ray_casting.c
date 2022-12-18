/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:51:10 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/16 21:53:27 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_set_ray_offset(t_game *game, t_ray *ray)
{
	if (ray->type == 'h' && ray->offset.y == 0)
	{
		if (ray->ang < PI2)
			ray->offset.y = game->map.t_sz;
		if (ray->ang > PI2)
			ray->offset.y = -game->map.t_sz;
		ray->offset.x = -ray->offset.y * ray->tan;
		return ;
	}
	if (ray->type == 'v' && ray->offset.x == 0)
	{
		if (ray->ang > PI1 && ray->ang < PI3)
			ray->offset.x = -game->map.t_sz;
		if (ray->ang < PI1 || ray->ang > PI3)
			ray->offset.x = game->map.t_sz;
		ray->offset.y = -ray->offset.x * ray->tan;
		return ;
	}
}

void	ft_ray_end_point_correction(t_game *game, t_ray *ray)
{
	if (ray->type == 'h' && ray->ang > PI2)
		ray->grid_p.y = (int)(ray->end.y - 1) / game->map.t_sz;
	else
		ray->grid_p.y = (int)ray->end.y / game->map.t_sz;
	if (ray->type == 'v' && ray->ang > PI1 && ray->ang < PI3)
		ray->grid_p.x = (int)(ray->end.x - 1) / game->map.t_sz;
	else
		ray->grid_p.x = (int)ray->end.x / game->map.t_sz;
}

void	ft_choose_ray_to_cast(t_game *game, t_ray ray_h, t_ray ray_v)
{
	if (ray_h.len == 0)
		ray_h.len = game->ray_max_dist;
	if (ray_v.len == 0)
		ray_v.len = game->ray_max_dist;
	if (ray_h.len < ray_v.len)
		game->ray = ray_h;
	else
		game->ray = ray_v;
}

void	ft_cast_one_ray(t_game *game, double angle)
{
	t_ray	ray_h;
	t_ray	ray_v;

	ft_init_ray(game, &ray_h, angle);
	ft_init_ray(game, &ray_v, angle);
	ft_check_horizontal_lines(game, &ray_h);
	ft_check_vertical_lines(game, &ray_v);
	ray_h.len = ft_get_hypotenuse
		(ray_h.end.x, game->pl.m_p.x, ray_h.end.y, game->pl.m_p.y);
	ray_v.len = ft_get_hypotenuse
		(ray_v.end.x, game->pl.m_p.x, ray_v.end.y, game->pl.m_p.y);
	ft_choose_ray_to_cast(game, ray_h, ray_v);
}

void	ft_cast_rays(t_game *game)
{
	int		i;
	double	step_angle;

	i = 0;
	while (i < WIDTH)
	{
		step_angle = atan((i - (WIDTH / 2)) / game->dtpp);
		ft_cast_one_ray(game, game->pl.ang + step_angle);
		game->ray.len = game->ray.len * cos
			(ft_reset_angle(game->ray.ang - game->pl.ang));
		ft_draw_pseudo_3d(game, i);
		i++;
	}
}
