/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 21:55:54 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/16 22:23:55 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_init_ray(t_game *game, t_ray *ray, double angle)
{
	ray->offset.x = 0;
	ray->offset.y = 0;
	ray->len = game->ray_max_dist;
	ray->ang = ft_reset_angle(angle);
	ray->end.x = game->pl.m_p.x;
	ray->end.y = game->pl.m_p.y;
}
