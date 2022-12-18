/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:45:16 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/07/20 16:58:53 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/time.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

# define WIDTH	1024
# define HEIGHT	768

# define PI1 1.57079632679489
# define PI2 3.14159265358979
# define PI3 4.71238898038469
# define PI4 6.28318530717958	 

# define FOV 1.15191730631625
# define PRC 0.00000000001

typedef struct s_dda
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	steps;
}	t_dda;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	e;
	int	q;
	int	pause;
	int	left_arrow;
	int	right_arrow;
}	t_keys;

typedef struct s_img
{
	int		w;
	int		h;
	int		endian;
	int		b_per_px;
	int		l_len;
	void	*img;
	void	*addr;
	char	*path;
}	t_img;

typedef struct s_point_d
{
	double	x;
	double	y;
}	t_point_d;

typedef struct s_point_i
{
	int	x;
	int	y;
}	t_point_i;

typedef struct s_player
{
	char		dir;
	double		ang;
	double		delta_x;
	double		delta_y;
	t_point_i	grid_p;
	t_point_d	m_p;
	t_point_d	mm_p;
	t_point_d	mm_off;
}	t_player;

typedef struct s_textures
{
	t_img		no_w;
	t_img		so_w;
	t_img		ea_w;
	t_img		we_w;
	t_img		pl;
	t_img		door;
	t_img		enm;
	int			floor;
	int			ceiling;
}	t_textures;

typedef struct s_map
{
	int		fd;
	int		row_c;
	int		col_c;
	int		t_sz;
	int		h_t_sz;
	char	**grid;
}	t_map;

typedef struct s_ray
{
	char		type;
	double		ang;
	double		len;
	double		tan;
	t_point_i	grid_p;
	t_point_d	end;
	t_point_d	offset;
}	t_ray;

typedef struct s_minimap
{
	t_img		full;
	t_img		view;
	int			w;
	int			h;
	int			t_sz;
	t_point_d	p1;
	t_point_d	p2;
}	t_minimap;

typedef struct s_game
{
	int			fov;
	int			ray_step_limit;
	void		*mlx;
	void		*window;
	double		sf;
	double		w_h;
	double		w_h_off;
	double		dtpp;
	double		ray_max_dist;
	t_map		map;
	t_img		frame;
	t_ray		ray;
	t_dda		dda;
	t_keys		keys;
	t_player	pl;
	t_textures	txt;
	t_minimap	mmap;
	t_point_d	start;
	t_point_d	end;
	double		dist;
	int			maus_x;
	int			maus_y;
}	t_game;

//---Init
int		ft_load_sprites(t_game *game);
void	ft_init(t_game *game);
void	ft_more_init(t_game *game);
void	ft_define(t_game *game);
void	ft_init_mmap(t_game *game);
void	ft_init_mlx_images(t_game *game);

//---Minimap
void	ft_player_offset_x(t_game *game);
void	ft_player_offset_y(t_game *game);
void	ft_mmap_view_offset(t_game *game);
void	ft_full_mmap_offset(t_game *game, t_point_i *off);
void	ft_draw_mmap_view(t_game *game);
void	ft_generate_full_mmap_img(t_game *game);

//---Controls
int		ft_key_press(int keycode, t_game *game);
int		ft_key_release(int keycode, t_game *game);
void	ft_key_actions(t_game *game);
void	ft_key_w_action(t_game *game);
void	ft_key_s_action(t_game *game);
void	ft_key_a_action(t_game *game);
void	ft_key_d_action(t_game *game);
int		ft_mouse_move(int x, int y, t_game *game);

//---Uteles
int		ft_trim_str_front(char **str, char c);
int		ft_trim_str_back(char **str, char c);
int		ft_trim_2d_back(t_game *game, char *str);
char	*ft_get_pixel_info(t_img *img, int x, int y);
void	ft_free_2d_arr(char **arr);
void	ft_draw_line(t_game *game, t_img *img, int color);
void	ft_draw_rectangle(t_game *game, t_img img, int color1, int color2);
void	ft_set_pixel_color(t_img *img, int x, int y, int color);
void	ft_copy_pixel(t_game *game, t_img *img_1, t_img *img_2);
double	ft_reset_angle(double angle);
double	ft_get_radians_from_degree(double deg);
double	ft_get_hypotenuse(double x1, double x2, double y1, double y2);
long	ft_get_time(void);
int		ft_ignore_black_color(t_img *tile, int i, int j);
int		ft_min(int i, int j);
int		ft_max(int i, int j);
int		ft_random_number(int i, int j);

//---Miscellaneous
int		ft_print_err(char *str);
int		ft_exit(t_game *game);
void	ft_free_all(t_game *game);

//---Colisions
int		ft_rec_circle(t_point_d p, int yc, int xc, int r);
int		ft_rec_rec(t_game *game, t_point_d p, double i, double j);
int		ft_check_arround(t_game *game);

//---Checkers
int		ft_is_file_valid(char *path);
int		ft_is_extention_valid(char *str, char *ext);
int		ft_is_map_config_loaded(t_game *game);
int		ft_is_arr_only_nbr(char *str);
int		ft_has_only_spaces(char *str);
int		ft_check_rgb(char **str, int *nbr);
int		ft_check_texture_path_extension(char **line, char **path);
int		ft_is_map_surrounded_by_wall(t_game *game, int i, int j);

//---Helpers
void	ft_update_pl_coord(t_game *game, double x, double y);
void	ft_save_point(t_point_d *p, double x, double y);
void	ft_save_point_i(t_point_i *p, int x, int y);

//---Handle Map File
int		ft_get_line(int fd, char **line);
int		ft_get_map_grid(t_game *game, char **line);
int		ft_check_map(t_game *game);
int		ft_make_grid_square(t_game *game);
int		ft_get_map_config(t_game *game, char **line);
int		ft_handle_map_file(int argc, char **argv, t_game *game);
int		ft_parse_floor_ceiling_colors(t_game *game, char **line);
int		ft_store_wall_text_path(t_game *game, char **line);
int		ft_store_map_fc_colors(t_game *game, char type, char *src);

//---Ray Casting
void	ft_init_ray(t_game *game, t_ray *ray, double angle);
void	ft_check_horizontal_lines(t_game *game, t_ray *ray);
void	ft_check_vertical_lines(t_game *game, t_ray *ray);
void	ft_cast_rays(t_game *game);
void	ft_cast_one_ray(t_game *game, double angle);
void	ft_ray_end_point_correction(t_game *game, t_ray *ray);
void	ft_set_ray_offset(t_game *game, t_ray *ray);
void	ft_draw_pseudo_3d(t_game *game, int i);
#endif