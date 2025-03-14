/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:26 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 14:08:23 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../libft/libft.h"
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

typedef enum s_error
{
	OK,
	INV_EXT,
	COPEN_FILE,
	EMPTY_FILE,
	NOT_RECT_MAP,
	INV_CHAR,
	INV_EDGES,
	INV_STATS,
	INV_REACH,
	MLX_FAILED,
	LOAD_ASSETS,
	MLX_WIN,
	FAILED,
	SUCCESS,
}						t_error;

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_stats
{
	t_list				*clc_poss;
	t_list				*enemy_poss;
	t_point				player_pos;
	t_point				exit_pos;
	t_error				err;
}						t_stats;

typedef struct s_map
{
	char				**grid;
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
	t_frames			death;
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
int						search_path(char **grid, t_point start, t_point size,
							t_point *stats);
int						scan_map(t_stats *stats, char **grid, t_point size,
							t_point id);
int						load_map(t_mlx *mlx, int fd);

int						split_sprite_to_frames(void *mlx_ptr, t_frames *stc,
							char *filename);

int						render_map(t_mlx *mlx);
int						put_image(t_mlx *mlx, void *img, int x, int y);

int						map_errors(t_error error);
int						mlx_errors(t_error error);
int						exit_program(t_mlx *mlx);
int						free2(char **arr);

int						move_player(t_mlx *mlx, int x, int y);

int						animate_player(t_mlx *mlx);
int						animate_enemy(t_mlx *mlx);
int						animate_clc(t_mlx *mlx);
int						reset_player_animation(t_mlx *mlx);

int						map_errors(t_error error);
int						mlx_errors(t_error error);
int						stats_errors(t_error error);
#endif
