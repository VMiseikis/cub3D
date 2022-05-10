/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:33:41 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/10 18:12:57 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_trim_str_front(char **str, char c)
{
	int		i;
	char	*temp;

	if (!(*str))
		return (FALSE);
	i = 0;
	while ((*str)[i] != '\0' && (*str)[i] == c)
		i++;
	temp = *str;
	*str = ft_substr(temp, i, ft_strlen(*str));
	free(temp);
	if (!(*str))
		return (FALSE);
	return (TRUE);
}

int	ft_trim_str_back(char **str, char c)
{
	int		i;
	char	*temp;

	if (!(*str))
		return (FALSE);
	i = ft_strlen(*str) - 1;
	while (i > 0 && (*str)[i] == c)
		i--;
	temp = *str;
	*str = ft_substr(temp, 0, i + 1);
	free(temp);
	if (!(*str))
		return (FALSE);
	return (TRUE);
}

int	ft_count_lines_for_back_trim(t_game	*game, char *str)
{
	int	i;

	i = game->map.row_c - 1;
	while (ft_strcmp(game->map.grid[i], str) == 0)
	{
		free(game->map.grid[i]);
		i--;
	}
	i++;
	return (i);
}

int	ft_trim_2d_back(t_game *game, char *str)
{
	int		i;
	char	**temp;

	game->map.row_c = ft_count_lines_for_back_trim(game, str);
	temp = malloc((game->map.row_c + 1) * sizeof(char *));
	if (!temp)
		return (FALSE);
	i = 0;
	while (i < game->map.row_c)
	{
		temp[i] = game->map.grid[i];
		i++;
	}
	temp[i] = NULL;
	free(game->map.grid);
	game->map.grid = malloc((game->map.row_c + 1) * sizeof(char *));
	if (!game->map.grid)
		return (FALSE);
	ft_2dstrcpy(temp, game->map.grid);
	free(temp);
	return (TRUE);
}
