/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:08:08 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/06/04 22:06:28 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

long	ft_get_time(void)
{
	struct timeval	time_stamp;

	gettimeofday(&time_stamp, NULL);
	return (time_stamp.tv_sec * 1000 + time_stamp.tv_usec / 1000);
}
