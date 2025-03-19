/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:26 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/19 00:56:10 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>

# define MIN_MAP_HEIGHT 3
# define SIZE 32
# define ESCAPE 65307

# define KEY_RIGHT 'd'
# define KEY_LEFT 'a'
# define KEY_UP 'w'
# define KEY_DOWN 's'

# define DOWN 0
# define RIGHT 1
# define UP 2
# define LEFT 3

# define MICROSEC 1000000
# define P_NUM_FRAMES 4
# define ACCELERATION 8

# ifndef BONUS_MODE
#  define BONUS_MODE 0
# endif

typedef enum s_error
{
	OK,
	INV_EXT,
	COPEN_FILE,
	EMPTY_FILE,
	NOT_RECT_MAP,
	INV_CHAR,
	INV_EDGES,
	COINS_ERR,
	EXIT_ERR,
	PLAYER_ERR,
	PATH_ERR,
	MLX_FAILED,
	LOAD_ASSETS,
	MLX_WIN,
	BIG_MAP,
	INV_STATS,
	EXIT_SIG,
}				t_error;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_cords
{
	t_list		*clc;
	t_list		*enemy;
	t_list		*player;
	t_list		*exit;
	t_error		error;
}				t_cords;

typedef struct s_map
{
	char		**grid;
	t_cords		cords;
	t_point		size;
	t_error		err;
}				t_map;

typedef struct s_frames
{
	void		**frames;
	int			tframes;
}				t_frames;

typedef struct s_assets
{
	t_frames	wall;
	t_frames	exit;
	t_frames	clc;
	t_frames	space;
	t_frames	death_scene;
	t_frames	enemy_walk[4];
	t_frames	player_walk[4];
	t_frames	player_idle[4];
}				t_assets;

typedef struct s_movement
{
	t_frames	*cur_frame;
	t_point		direction;
	t_point		offset;
	int			side;
}				t_movement;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_map		map;
	t_assets	assets;
	int			nmoves;
	t_movement	player;
	int			fps;
	t_error		err;
}				t_mlx;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			size;
	int			bpp;
	int			sline;
	int			endian;
}				t_img;

int				init_assets(t_mlx *mlx);
int				search_path(char **grid, t_point start, t_point size,
					t_point *stats);
int				scan_map(t_cords *stats, char **grid, t_point size);
int				load_map(t_mlx *mlx, int fd);

int				split_sprite_to_frames(void *mlx_ptr, t_frames *stc,
					char *filename);
int				put_string_to_window(t_mlx *mlx);

int				render_map(t_mlx *mlx);
int				render_frames(t_mlx *mlx);
int				put_image(t_mlx *mlx, t_img *img, t_point *point);

int				map_errors(t_error error);
int				mlx_errors(t_error error);
int				exit_program(t_mlx *mlx);
int				free2(char **arr);

int				keypress(int keycode, t_mlx *mlx);
int				move_player(t_mlx *mlx, t_point move);

int				map_errors(t_error error);
int				mlx_errors(t_error error);
int				stats_errors(t_error error);
#endif
