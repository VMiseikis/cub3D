/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:42:11 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/14 21:43:16 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_min(int i, int j)
{
	if (i <= j)
		return (i);
	return (j);
}

int	ft_max(int i, int j)
{
	if (i >= j)
		return (i);
	return (j);
}
