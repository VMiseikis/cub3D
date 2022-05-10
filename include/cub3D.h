/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:45:16 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/10 23:24:48 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0
# define FAIL -1

typedef struct s_point
{
	int	x;
	int	y;	
}	t_point;

typedef struct s_player
{
	char	dir;
	t_point	p;
}	t_player;

typedef struct s_wall
{
	char	*path;
}	t_wall;

typedef struct s_color
{
	int	rgb[3];
}	t_color;

typedef struct s_map
{
	int			fd;
	char		**grid;
	int			row_c;
	int			col_c;
	t_wall		no;
	t_wall		so;
	t_wall		ea;
	t_wall		we;
	t_color		floor;
	t_color		ceiling;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	t_map		map;
	t_player	pl;
}	t_game;

//	Uteles
int	ft_trim_str_front(char **str, char c);
int	ft_trim_str_back(char **str, char c);
int	ft_trim_2d_back(t_game *game, char *str);

void	ft_free_2d_arr(char **arr);

int	ft_print_error(char *str);

//Checkers
int	ft_is_file_valid(char *path);
int	ft_is_extention_valid(char *str, char *ext);
int	ft_is_map_config_loaded(t_game *game);
int	ft_is_arr_only_nbr(char *str);
int	ft_has_only_spaces(char *str);

int	ft_check_rgb(char **str, int *nbr);
int	ft_check_texture_path_extension(char **line, char **path);
int	ft_is_map_surrounded_by_wall(t_game *game, int i, int j);
//helpers
void	ft_skip_empty_lines_from_file(t_game *game, char **line);



//read file
int	ft_get_line(int fd, char **line);
int	ft_get_map_grid(t_game *game, char **line);
int	ft_check_map(t_game *game);
int	ft_make_grid_square(t_game *game);
int	ft_get_map_config(t_game *game, char **line);

//int	ft_get_map_colors_textures(t_game *game, char **line);


int	ft_parse_floor_ceiling_colors(t_game *game, char **line);
int	ft_store_wall_text_path(t_game *game, char **line);
int	ft_store_map_fc_colors(t_game *game, char type, char *src);
#endif