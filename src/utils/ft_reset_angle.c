/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_angle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:24:53 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/10 22:25:48 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

double	ft_reset_angle(double angle)
{
	if (angle < 0)
		return (angle + PI4);
	if (angle > PI4)
		return (angle - PI4);
	return (angle);
}
