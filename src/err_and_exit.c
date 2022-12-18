/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_and_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:22:08 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:08:49 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_print_err(char *str)
{
	printf("Error: %s\n", str);
	printf("Program was terminated!\n");
	return (FALSE);
}

void	ft_free_all(t_game *game)
{
	if (game->map.grid != NULL)
		ft_free_2d_arr(game->map.grid);
	if (game->txt.no_w.path != NULL)
		free(game->txt.no_w.path);
	if (game->txt.so_w.path != NULL)
		free(game->txt.so_w.path);
	if (game->txt.ea_w.path != NULL)
		free(game->txt.ea_w.path);
	if (game->txt.we_w.path != NULL)
		free(game->txt.we_w.path);
	if (game->txt.pl.img != NULL)
		free(game->txt.pl.img);
	if (game->mmap.full.img)
		mlx_destroy_image(game->mlx, game->mmap.full.img);
	if (game->mmap.view.img)
		mlx_destroy_image(game->mlx, game->mmap.view.img);
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
}

int	ft_exit(t_game *game)
{
	ft_free_all(game);
	exit(0);
}
