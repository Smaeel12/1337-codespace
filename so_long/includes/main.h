/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:26 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/13 10:19:32 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../libft/get_next_line/get_next_line.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>

# define MIN_MAP_HEIGHT 3
# define SIZE 32
# define ESCAPE 65307

typedef struct s_stats
{
	int		next;
	int		nclc;
}			t_stats;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_tiles
{
	void	*wall;
	void	*exit;
	void	*player;
	void	*clc;
	void	*space;
	int		tsize;
}			t_tiles;

typedef enum s_error
{
	MAP_OK = 0,
	EMPTY_FILE = 1,
	NOT_RECT_MAP = 2,
	INVALID_EXT = 3,
	FILE_NOT_FOUND = 4,
	MAP_INVALID = 5,
	MLX_INS = 6,
	TILES_ERR = 7,
}			t_error;

typedef struct s_map
{
	t_list	*map;
	t_point	msize;
	t_point	pp;
}			t_map;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_tiles	tiles;
	t_stats	stats;
	t_map	map;
	t_error	err;
}			t_mlx;

int			dfs_search(t_mlx *mlx, t_point start, char s);
int			check_map(t_mlx *mlx, char *filename);
int			run_game(t_mlx *mlx);
void		kill_program(t_mlx *mlx);
void		render_map(t_mlx *mlx);
int			move_player(t_mlx *mlx, int x, int y);
void		put_image(t_mlx *mlx, void *img, int x, int y);
void		print_error(t_error error);

#endif