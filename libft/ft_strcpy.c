/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:46:00 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/09 18:23:45 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	**ft_2dstrcpy(char **src, char **dest)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen_2d(src);
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
