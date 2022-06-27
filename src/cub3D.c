/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:30:20 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/06/27 22:21:57 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_print_error(char *str)
{
	printf("Error: %s\n", str);
	//printf("Program was terminated!\n");
	return (FALSE);
}

int	ft_get_map_file_content(t_game *game)
{
	char	*line;

	if (!ft_get_map_config(game, &line))
		return (FALSE);
	if (!ft_get_map_grid(game, &line))
		return (FALSE);
	if (!ft_trim_2d_back(game, "") || !ft_make_grid_square(game) || !ft_check_map(game))
		return (FALSE);
	return (TRUE);
}

void ft_free_all(t_game *game)
{
	if(game->map.grid != NULL)
		ft_free_2d_arr(game->map.grid);
	if (game->map.no.path != NULL)
		free(game->map.no.path);
	if (game->map.so.path != NULL)
		free(game->map.so.path);
	if (game->map.we.path != NULL)
		free(game->map.we.path);
	if (game->map.ea.path != NULL)
		free(game->map.ea.path);
}

int	ft_handle_map_file(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		return (ft_print_error("Invalid number of input arguments"));
	if (ft_strlen(argv[1]) < 5)
		return (ft_print_error("Invalid map file name"));
	if (!ft_is_extention_valid(argv[1], ".cub"))
		return (ft_print_error("Unsupported map file extension"));
	game->map.fd = open (argv[1], O_RDONLY);
	if (game->map.fd == -1)
		return (ft_print_error("No such map file"));
	if (!ft_get_map_file_content(game))
		return (FALSE);
	return (TRUE);
}



void	ft_init(t_game *game)
{
	game->width = 1260;
	game->height = 960;
	game->map.fd = -1;
	game->map.floor.rgb[0] = -1;
	game->map.ceiling.rgb[0] = -1;
	game->map.row_c = 0;
	game->map.col_c = 0;
	game->map.grid = NULL;
	game->map.no.path = NULL;
	game->map.so.path = NULL;
	game->map.ea.path = NULL;
	game->map.we.path = NULL;
	game->pl.dir = '\0';
	
	game->t_size = 64;
	

	game->start.x = 0;
	game->start.y = 0;
	game->end.x = 0;
	game->end.y = 0;

	game->mmap.width = 500;
	game->mmap.height = 400;
	// game->mmap.size.x = 200;
	// game->mmap.size.y = 150;
	game->mmap.t_sz = 16;
	game->pl.mm_off.x = 0;
	game->pl.mm_off.y = 0;
	game->mmap.p1.x = 0;
	game->mmap.p1.y = 0;
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.s = 0;
	game->keys.w = 0;
	game->keys.q = 0;
	game->keys.e = 0;




	
}

int ft_exit(t_game *game)
{
	game->pl.mm_off.y = 0;
	exit(1);
}

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == 53)
		ft_exit(game);
	if (keycode == 13)
	{
		game->keys.w = 1;
	}
	if (keycode == 0)
	{
		game->keys.a = 1;
	}
	if (keycode == 1)
	{
		game->keys.s = 1;
	}
	if (keycode == 2)
	{
		game->keys.d = 1;
	}
	
	if (keycode == 12)
	{
		game->keys.q = 1;
	}
	if (keycode == 14)
	{
		game->keys.e = 1;
	}
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == 13)
	{
		game->keys.w = 0;
	}
	if (keycode == 0)
	{
		game->keys.a = 0;
	}
	if (keycode == 1)
	{
		game->keys.s = 0;
	}
	if (keycode == 2)
	{
		game->keys.d = 0;
	}
	

	if (keycode == 12)
	{
		game->keys.q = 0;
	}
	if (keycode == 14)
	{
		game->keys.e = 0;
	}
	return (0);
}

void ft_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->l_len + x * (img->b_per_px / 8));
	*(unsigned int*)dest = color;
}

void ft_draw_rectangle(t_game *game, t_img img, int color)
{
	int i;
	int j;

	i = game->start.x;
	while (i < game->end.x)
	{
		
		j = game->start.y;
		while (j < game->end.y)
		{
			if (i == game->start.x || j == game->start.y || i == (game->end.x - 1) || j == (game->end.y - 1))
				ft_pixel_to_img(&img, i, j, color);
			j++;
		}
		i++;
	
	}
}
// int	ft_ignore_black_color(t_img *tile, int i, int j)
// {
// 	char	*pixel;

// 	pixel = tile->addr + (j * tile->l_len
// 			+ i * (tile->b_per_px / 8));
// 	if (*(unsigned int *)pixel != 0x000001)
// 		return (1);
// 	return (0);
// }

void ft_save_point(t_point *p, int x, int y)
{
	p->x = x;
	p->y = y;
}

void ft_draw_mmap_border(t_game *game)
{
	ft_save_point(&game->start, 0, 0);
	ft_save_point(&game->end, game->mmap.width, game->mmap.height);
	ft_draw_rectangle(game, game->mmap.view, 0x00FF00);
}

void ft_generate_map_img(t_game *game)
{
	int i;
	int j;
	int mod_x;
	int mod_y;

	mod_x = 0;
	if (game->map.col_c * game->mmap.t_sz < game->mmap.width)
		mod_x = (game->mmap.width - (game->map.col_c * game->mmap.t_sz)) / 2;
	mod_y = 0;
	if (game->map.row_c * game->mmap.t_sz < game->mmap.height)
		mod_y = (game->mmap.height - (game->map.row_c * game->mmap.t_sz)) / 2;
	i = 0;
	while (i < game->map.row_c)
	{
		j = 0;
		while (j < game->map.col_c)
		{
			if (game->map.grid[i][j] != '1' && game->map.grid[i][j] != ' ')
			{
				ft_save_point(&game->start, j * game->mmap.t_sz + mod_x, i * game->mmap.t_sz + mod_y);
				ft_save_point(&game->end, j * game->mmap.t_sz + game->mmap.t_sz + mod_x, i * game->mmap.t_sz + game->mmap.t_sz + mod_y);
				ft_draw_rectangle(game, game->mmap.map, 0x36454F);
			}
			if (game->map.grid[i][j] == '1')
			{
				ft_save_point(&game->start, j * game->mmap.t_sz + mod_x, i * game->mmap.t_sz + mod_y);
				ft_save_point(&game->end, j * game->mmap.t_sz + game->mmap.t_sz + mod_x, i * game->mmap.t_sz + game->mmap.t_sz + mod_y);
				ft_draw_rectangle(game, game->mmap.map, 0x0000FF);
			}
			j++;
		}
		i++;
			
	}
}


void ft_player_offset(t_game *game)
{
	if (game->pl.mm_p.x > (game->mmap.width / 2) && game->mmap.width < game->map.col_c * game->mmap.t_sz)
	{
		if (((game->map.col_c * game->mmap.t_sz) - game->pl.mm_p.x) < game->mmap.width / 2)
			game->pl.mm_off.x = game->mmap.width - (game->map.col_c * game->mmap.t_sz);
		else
			game->pl.mm_off.x = (game->mmap.width / 2) - game->pl.mm_p.x + 1;
	}
	else if (game->mmap.width > game->map.col_c * game->mmap.t_sz)
		game->pl.mm_off.x = (game->mmap.width - (game->map.col_c * game->mmap.t_sz)) / 2;
	if (game->pl.mm_p.y > (game->mmap.height / 2) && game->mmap.height < (game->map.row_c * game->mmap.t_sz))
	{
		if(((game->map.row_c * game->mmap.t_sz) - game->pl.mm_p.y) < game->mmap.height / 2)
			game->pl.mm_off.y = game->mmap.height - (game->map.row_c * game->mmap.t_sz);
		else
			game->pl.mm_off.y = (game->mmap.height / 2) - game->pl.mm_p.y + 1;
	}
	else if (game->mmap.height > (game->map.row_c * game->mmap.t_sz))
		game->pl.mm_off.y = (game->mmap.height - (game->map.row_c * game->mmap.t_sz)) / 2;

	//printf("Player: X: %f, Y: %f, Off_X: %f, Off_Y: %f\n", game->pl.mm_p.x, game->pl.mm_p.y, game->pl.mm_off.x, game->pl.mm_off.y);
}

void ft_mmap_offset(t_game *game)
{
	game->mmap.p1.x = 0;
	game->mmap.p1.y = 0;
	if (game->pl.mm_off.x > 0)
		game->mmap.p2.x = game->mmap.width;
	else
	{
		game->mmap.p1.x = game->pl.mm_off.x * -1;
		game->mmap.p2.x = game->mmap.p1.x + game->mmap.width;
	}
	if (game->pl.mm_off.y > 0)
		game->mmap.p2.y = game->mmap.height;
	else
	{
		game->mmap.p1.y = game->pl.mm_off.y * -1;
		game->mmap.p2.y = game->mmap.p1.y  + game->mmap.height;
	}
	//printf("X: %d, X2: %d, Y: %d, Y2: %d\n", game->mmap.p1.x, game->mmap.p2.x, game->mmap.p1.y, game->mmap.p2.y);

}

//DDA Algorithm (Digital Differential Analysis)
void ft_dda(t_game *game)
{	
    game->dda.dx = (game->end.x - game->start.x);
    game->dda.dy = (game->end.y - game->start.y);  
		
    if(fabsf(game->dda.dx) >= fabsf(game->dda.dy))  
        game->dda.steps = fabsf(game->dda.dx);  
    else  
    	game->dda.steps = fabsf(game->dda.dy);  
	//printf("STEPS %f DDAx %f DDAy %f DDAdx %f DDAdy %f\n", game->dda.steps, game->dda.x, game->dda.y, game->dda.dx, game->dda.dy);

    game->dda.dx = game->dda.dx / game->dda.steps;  
    game->dda.dy = game->dda.dy / game->dda.steps;  

    game->dda.x = game->start.x;  
    game->dda.y = game->start.y;

	//printf("STEPS %f DDAx %f DDAy %f DDAdx %f DDAdy %f\n", game->dda.steps, game->dda.x, game->dda.y, game->dda.dx, game->dda.dy);

} 

void ft_draw_line(t_game *game)
{
	int i;
	i = 0; 
    // while(i < game->dda.steps)  
	while(i < 5)  
    {  
		ft_pixel_to_img(&game->mmap.view, game->pl.mm_p.x + game->pl.mm_off.x + game->dda.x * 16, game->pl.mm_p.y + game->pl.mm_off.y + game->dda.y * 16, 0xFF0000); 
		game->dda.x += game->dda.dx;  
		game->dda.y += game->dda.dy;

        i++;  
    } 
}


void ft_draw_ray(t_game *game)
{
	int i;

	i = 0;

	
float dif_x;
float dif_y;


	dif_x = (int)game->pl.mm_p.x % 16;
	dif_y = (int)game->pl.mm_p.y % 16;
// 	game->start.x = game->start.x - dif_x;
// 	game->start.y = game->start.y - dif_y;

	//printf("%f %f %f %f \n", game->pl.mm_p.x, game->pl.mm_p.y, dif_x, dif_y);

	
	while (i < 5)
	{
		game->dda.dx = game->end.x - game->start.x;
    	game->dda.dy = game->end.y - game->start.y;  

		if(fabsf(game->dda.dx) >= fabsf(game->dda.dy))
			game->dda.steps = fabsf(game->dda.dx);
		else  
			game->dda.steps = fabsf(game->dda.dy);  
		
		game->dda.dx = game->dda.dx / game->dda.steps;  
		game->dda.dy = game->dda.dy / game->dda.steps;  
		
			game->dda.x = game->start.x;  
			game->dda.y = game->start.y;




		// if (i == 0)
		// {
		// 	ft_pixel_to_img(&game->mmap.view, game->pl.mm_p.x + game->pl.mm_off.x + game->dda.x * 16, game->pl.mm_p.y + game->pl.mm_off.y + game->dda.y * 16, 0xFF0000);

		// 		game->start.x += (game->dda.dx * (16 - dif_x)) / 16;  
		// 		game->start.y += (game->dda.dy * (16 - dif_y)) / 16;


		// 	// game->start.x += game->dda.dx * (16 - dif_x) / 16;  
		// 	// game->start.y += game->dda.dy * (16 - dif_y) / 16;
		// }
		// else
		// {
			ft_pixel_to_img(&game->mmap.view, game->pl.mm_p.x + game->pl.mm_off.x + game->dda.x * 16, game->pl.mm_p.y + game->pl.mm_off.y + game->dda.y * 16, 0xFF0000);
			game->start.x += game->dda.dx;  
			game->start.y += game->dda.dy;
		// }
		
				
		i++;
	}
}


void ft_draw_pl_dir(t_game *game)
{
	ft_dda(game);
	ft_draw_line(game);
}

void ft_pixels_to_mmap_view(t_game *game, int x, int y)
{
	char	*dest;
	char	*input;

	dest = game->mmap.view.addr + (y * game->mmap.view.l_len + (x * (game->mmap.view.b_per_px / 8)));
	input = game->mmap.map.addr + ((y + (int)game->mmap.p1.y) * game->mmap.map.l_len + ((x + (int)game->mmap.p1.x) * (game->mmap.map.b_per_px / 8)));
	*(unsigned int *)dest = *(unsigned int *)input;
}


void ft_draw_mmap_view_details(t_game *game)
{
	int i;
	int j;

	i = 0;
	while(i < game->mmap.width)
	{
		j = 0;
		while (j < game->mmap.height)
		{
			ft_pixels_to_mmap_view(game, i, j);
			j++;
		}
		i++;
	}
	ft_pixel_to_img(&game->mmap.view, game->pl.mm_p.x + game->pl.mm_off.x, game->pl.mm_p.y + game->pl.mm_off.y, 0xFF0000);

	ft_save_point(&game->start, 0, 0);
	ft_save_point(&game->end, game->pl.delta_x *100, game->pl.delta_y *100); //depth of view
	//ft_draw_pl_dir(game);
	
	ft_draw_ray(game);

	
	ft_pixel_to_img(&game->mmap.view, game->pl.mm_p.x + game->pl.mm_off.x, game->pl.mm_p.y + game->pl.mm_off.y+1, 0xFF0000);
	ft_pixel_to_img(&game->mmap.view, game->pl.mm_p.x + game->pl.mm_off.x, game->pl.mm_p.y + game->pl.mm_off.y-1, 0xFF0000);
	ft_pixel_to_img(&game->mmap.view, game->pl.mm_p.x + game->pl.mm_off.x+1, game->pl.mm_p.y + game->pl.mm_off.y, 0xFF0000);
	ft_pixel_to_img(&game->mmap.view, game->pl.mm_p.x + game->pl.mm_off.x-1, game->pl.mm_p.y + game->pl.mm_off.y, 0xFF0000);
}



int ft_frames(t_game *game)
{
	if (game->keys.w == 1)
	{
		//game->pl.p.y = game->pl.p.y - 4;
		//game->pl.mm_p.y = game->pl.mm_p.y - 1;
		game->pl.mm_p.y = game->pl.mm_p.y + game->pl.delta_y;
		game->pl.mm_p.x = game->pl.mm_p.x + game->pl.delta_x;
	}
	if (game->keys.a == 1)
	{
		//game->pl.p.x = game->pl.p.x - 4;
		//game->pl.mm_p.x = game->pl.mm_p.x - 1;
		game->pl.mm_p.y = game->pl.mm_p.y - game->pl.delta_x;
		game->pl.mm_p.x = game->pl.mm_p.x + game->pl.delta_y;
	}
	if (game->keys.s == 1)
	{
		//game->pl.p.y = game->pl.p.y + 4;
		//game->pl.mm_p.y = game->pl.mm_p.y + 1;
		game->pl.mm_p.y = game->pl.mm_p.y - game->pl.delta_y;
		game->pl.mm_p.x = game->pl.mm_p.x - game->pl.delta_x;
	}
	if (game->keys.d == 1)
	{
		//game->pl.p.x = game->pl.p.x + 4;
		//game->pl.mm_p.x = game->pl.mm_p.x + 1;
		game->pl.mm_p.y = game->pl.mm_p.y + game->pl.delta_x;
		game->pl.mm_p.x = game->pl.mm_p.x - game->pl.delta_y;
	}

	if (game->keys.q == 1)
	{
		game->pl.angle = game->pl.angle + 0.05;
		if (game->pl.angle > (2 * PI))
			game->pl.angle = 0;
		game->pl.delta_x = cos(game->pl.angle);
		game->pl.delta_y = -sin(game->pl.angle);
	}
	if (game->keys.e == 1)
	{
		game->pl.angle = game->pl.angle - 0.05;
		if (game->pl.angle < 0)
			game->pl.angle = 2 * PI;
		game->pl.delta_x = cos(game->pl.angle);
		game->pl.delta_y = -sin(game->pl.angle);
	}

	ft_player_offset(game);
	ft_mmap_offset(game);
	ft_draw_mmap_view_details(game);
	ft_draw_mmap_border(game);

	mlx_put_image_to_window(game->mlx, game->window, game->mmap.view.img, 0, 0);
	return (1);
}



void	ft_render(t_game *game)
{
	int i;
	int j;
	game->pl.delta_x = cos(game->pl.angle);
	game->pl.delta_y = -sin(game->pl.angle);
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, game->width, game->height, "Cub3D");

	i = game->map.col_c * game->mmap.t_sz;
	if (i < game->mmap.width)
		i = game->mmap.width;
	j = game->map.row_c * game->mmap.t_sz;
	if (j < game->mmap.height)
		j = game->mmap.height;
	
	game->mmap.map.img = mlx_new_image(game->mlx, i, j);
	game->mmap.map.addr = mlx_get_data_addr(game->mmap.map.img, &game->mmap.map.b_per_px, &game->mmap.map.l_len, &game->mmap.map.endian);
	ft_generate_map_img(game);

	game->mmap.view.img = mlx_new_image(game->mlx, game->mmap.width, game->mmap.height);
	game->mmap.view.addr = mlx_get_data_addr(game->mmap.view.img, &game->mmap.view.b_per_px, &game->mmap.view.l_len, &game->mmap.view.endian);

	
	mlx_loop_hook (game->mlx, &ft_frames, game);

	mlx_hook(game->window, 2, 1L << 0, ft_key_press, game);
	mlx_hook(game->window, 3, 1L << 1, ft_key_release, game);
	mlx_loop(game->mlx);

}

int	main(int argc, char **argv)
{
	t_game	game;
	
	ft_init(&game);
	ft_handle_map_file(argc, argv, &game);
	ft_render(&game);

	return (0);
}



