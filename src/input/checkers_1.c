/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:09:16 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/10 18:41:27 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_is_file_valid(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (FALSE);
	return (TRUE);
}

int	ft_is_extention_valid(char *str, char *ext)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(str);
	temp = ft_substr(str, len - 4, len);
	if (ft_strcmp(temp, ext) != 0)
	{
		free(temp);
		return (FALSE);
	}
	free(temp);
	return (TRUE);
}

int	ft_is_map_config_loaded(t_game *game)
{
	if (game->map.no.path == NULL || game->map.so.path == NULL
		|| game->map.ea.path == NULL || game->map.we.path == NULL
		|| game->map.floor.rgb[0] == -1 || game->map.ceiling.rgb[0] == -1)
		return (FALSE);
	return (TRUE);
}

int	ft_is_arr_only_nbr(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_has_only_spaces(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			count++;
		i++;
	}
	if (count != i)
		return (FALSE);
	return (TRUE);
}