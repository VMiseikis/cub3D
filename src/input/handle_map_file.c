/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:16:37 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 17:24:07 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_check_if_empty_line(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.grid[i])
	{
		if (ft_strlen(game->map.grid[i]) == 0)
			return (ft_print_err("Empty line in the map"));
		i++;
	}
	return (TRUE);
}

int	ft_get_map_file_content(t_game *game)
{
	char	*line;

	if (!ft_get_map_config(game, &line))
		return (FALSE);
	if (!ft_get_map_grid(game, &line))
		return (FALSE);
	if (!ft_trim_2d_back(game, "")
		|| !ft_check_if_empty_line(game)
		|| !ft_make_grid_square(game)
		|| !ft_check_map(game))
		return (FALSE);
	return (TRUE);
}

int	ft_handle_map_file(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		return (ft_print_err("Invalid number of input arguments"));
	if (ft_strlen(argv[1]) < 5)
		return (ft_print_err("Invalid map file name"));
	if (!ft_is_extention_valid(argv[1], ".cub"))
		return (ft_print_err("Unsupported map file extension"));
	game->map.fd = open (argv[1], O_RDONLY);
	if (game->map.fd == -1)
		return (ft_print_err("No such map file"));
	if (!ft_get_map_file_content(game))
		return (FALSE);
	return (TRUE);
}
