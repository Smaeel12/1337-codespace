/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:26 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/02 21:29:39 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../libft/get_next_line/get_next_line.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MIN_MAP_HEIGHT 3
# define SIZE 32
# define ESCAPE 65307
# define RIGHT 'd'
# define LEFT 'a'
# define UP 'w'
# define DOWN 's'
# define MICROSEC 1000000
# define P_NUM_FRAMES 4
# define ACCELERATION 8

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_stats
{
	t_point				pc;
	t_point				*clc_poss;
	t_point				*enemy_poss;
	t_point				exit_pos;
	int					next;
	int					nclc;
	int					eaten;
	int					nenemy;
}						t_stats;

typedef enum s_error
{
	MAP_OK = 0,
	INV_EXT = 1,
	COPEN_FILE = 2,
	EMPTY_FILE = 3,
	NOT_RECT_MAP = 4,
	INV_CHAR = 5,
	INV_EDGES = 6,
	DOUBLE_PLAYER = 7,
	INV_STATS = 8,
	INV_REACH = 9,
	MLX_FAILED = 10,
	LOAD_ASSETS = 11,
	MLX_WIN = 12,
	EXT_OK = 13,
}						t_error;

typedef struct s_map
{
	char				**arr;
	t_stats				stats;
	t_point				size;
	t_error				err;
}						t_map;

typedef struct s_frames
{
	void				**frames;
	int					tframes;
	int					cframe;
}						t_frames;

typedef struct s_assets
{
	t_frames			wall;
	t_frames			exit;
	t_frames			clc;
	t_frames			space;
	t_frames			enemy;
}						t_assets;

typedef struct s_player_animation
{
	t_frames			*cur_frame;
	t_frames			walk[P_NUM_FRAMES];
	t_frames			idle[P_NUM_FRAMES];
	t_point				direction;
	t_point				offset;
}						t_player_animation;

typedef struct s_mlx
{
	void				*ptr;
	void				*win;
	t_map				map;
	t_assets			assets;
	t_player_animation	pc_anim;
	t_error				err;
	int					num_mov;
}						t_mlx;

typedef struct s_img
{
	void				*ptr;
	char				*addr;
	int					size;
	int					bpp;
	int					sline;
	int					endian;
}						t_img;

int						init_assets(t_mlx *mlx);
int						search_path(t_map *map, t_point start, char edge);
t_error					scan_map(t_map *map, t_point start);
int						load_map(t_mlx *mlx, int fd);

int						render_map(t_mlx *mlx);
int						put_image(t_mlx *mlx, void *img, int x, int y);

int						map_errors(t_error error);
int						exit_program(t_mlx *mlx);
int						free_array(char **arr);

int						move_player(t_mlx *mlx, int x, int y);

#endif