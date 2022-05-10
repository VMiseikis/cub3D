/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:02:00 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/09 21:02:17 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_get_line(int fd, char **line)
{
	char	buffer;
	int		size;

	size = 0;
	*line = NULL;
	buffer = '\0';
	if (fd < 0 || read(fd, &buffer, 0) < 0)
		return (FALSE);
	size = read(fd, &buffer, 1);
	if (!buffer)
		return (FALSE);
	if (buffer != '\n' && size == 1)
		*line = ft_str_join_c(*line, buffer);
	while (buffer != '\n' && size == 1)
	{
		size = read(fd, &buffer, 1);
		if (!buffer)
			return (FALSE);
		if (buffer != '\n' && size == 1)
			*line = ft_str_join_c(*line, buffer);
	}
	return (TRUE);
}
