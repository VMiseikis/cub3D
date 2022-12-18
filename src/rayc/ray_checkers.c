/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:53:50 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:10:50 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_cast_ray_till_hit(t_game *game, t_ray *ray, int i)
{
	while (i < game->ray_step_limit)
	{
		ft_ray_end_point_correction(game, ray);
		if (ray->grid_p.x >= 0 && ray->grid_p.x < game->map.col_c
			&& ray->grid_p.y >= 0 && ray->grid_p.y < game->map.row_c)
		{
			if (game->map.grid[ray->grid_p.y][ray->grid_p.x] == '1')
				i = game->ray_step_limit;
			else
			{
				ray->end.x += ray->offset.x;
				ray->end.y += ray->offset.y;
				ft_set_ray_offset(game, ray);
				i++;
			}
		}
		else
			i = game->ray_step_limit;
	}
}

void	ft_check_horizontal_lines(t_game *game, t_ray *ray)
{
	int	i;

	i = 0;
	ray->tan = -1 / tan(ray->ang);
	if (ray->ang > PI2)
		ray->end.y = game->pl.grid_p.y * game->map.t_sz;
	if (ray->ang < PI2)
		ray->end.y = game->pl.grid_p.y * game->map.t_sz + game->map.t_sz;
	ray->end.x = (game->pl.m_p.y - ray->end.y) * ray->tan + game->pl.m_p.x;
	if (ray->ang == 0 || ray->ang == PI2)
		i = game->ray_step_limit;
	ray->type = 'h';
	ft_cast_ray_till_hit(game, ray, i);
}

void	ft_check_vertical_lines(t_game *game, t_ray *ray)
{
	int	i;

	i = 0;
	ray->tan = -tan(ray->ang);
	if (ray->ang > PI1 && ray->ang < PI3)
		ray->end.x = game->pl.grid_p.x * game->map.t_sz;
	if (ray->ang < PI1 || ray->ang > PI3)
		ray->end.x = game->pl.grid_p.x * game->map.t_sz + game->map.t_sz;
	ray->end.y = (game->pl.m_p.x - ray->end.x) * ray->tan + game->pl.m_p.y;
	if (ray->ang == PI1 || ray->ang == PI3)
		i = game->ray_step_limit;
	ray->type = 'v';
	ft_cast_ray_till_hit(game, ray, i);
}
