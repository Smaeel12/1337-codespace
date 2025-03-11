/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 00:47:56 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/10 21:30:23 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <fcntl.h>
#include <stdio.h>

/* MACROS */
#define SIZE 32
#define TITLE_GAME "Game Of Thrones"
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

/* ERROR MESSAGES */
#define ERROR_MSG "\033[31;1mError\n\033[0m"
#define NO_FILE_ERR "\033[31;1mError\n\033[0mInclude a map file .ber\n"

/* ENUMS */
typedef enum s_error
{
	EXT_ERR,
	COPEN_FILE,
	EMPTY_FILE,
	NOT_RECT_MAP,
	INV_CHAR,
	INV_EDGES,
	INV_STATS,
	INV_REACH,
	MLX_INIT,
	MLX_WIN,
	LOAD_ASSETS,
} t_error;

/* STRUCTERES */
typedef struct s_stats
{
	t_list *clc_poss;
	t_list *enm_poss;
	t_list *exit_pos;
	t_list *player_pos;
	t_error err;
} t_stats;

typedef struct s_point
{
	size_t x;
	size_t y;
} t_point;

typedef struct s_map
{
	char **grid;
	t_point size;
	t_stats stats;
	t_error err;
} t_map;

typedef struct s_img
{
	void *ptr;
	char *addr;
	int size;
	int bpp;
	int sline;
	int endian;
} t_img;

typedef struct s_frames
{
	void **frames;
	int tframes;
	int cframe;
} t_frames;

typedef struct s_assets
{
	t_frames wall;
	t_frames exit;
	t_frames clc;
	t_frames space;
	t_frames enemy;
	t_frames player_idle[4];
	t_frames player_walk[4];
} t_assets;

typedef struct s_mlx
{
	void *ptr;
	void *win;
	t_map map;
	t_assets assets;
	t_error err;
} t_mlx;

/* PROTOTYPES */
t_mlx init_game(char *filename);
int init_assets(t_mlx *mlx);
t_map load_map(int fd);
int render_game(t_mlx *mlx);

int map_errors(t_error error);
int mlx_errors(int error);

int clear_grid(char **grid);
int clear_map(t_map *map);
int clear_mlx(t_mlx *mlx);
int exit_program(t_mlx *mlx);

/* DEBUG */
void print_map(t_map *map);
void print_stats(t_stats *stats);
#define DEBUG(map, stats, error) \
	print_map(map);              \
	print_stats(stats);          \
	printf("error:: %i\n", error);
