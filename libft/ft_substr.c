/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:43:03 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/03 21:10:31 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!str)
		return (NULL);
	if (ft_strlen(str) < start)
		len = 0;
	dest = (char *) malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i + start < len)
	{
		dest[i] = str[i + start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
