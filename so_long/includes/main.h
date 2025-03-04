/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:26 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/26 09:46:31 by iboubkri         ###   ########.fr       */
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
#include <stdio.h>
#include <math.h>


# define MIN_MAP_HEIGHT 3
# define SIZE 32
# define ESCAPE 65307
# define MICROSEC 1000000

typedef struct s_stats
{
	int		next;
	int		nclc;
}			t_stats;

typedef struct s_point
{
	int	x;
	int	y;
}			t_point;

typedef struct s_frames
{
	void **frames;
	int tframes;
} t_frames;

typedef struct s_assets
{
	t_frames wall;
	t_frames exit;
	t_frames player;
	t_frames clc;
	t_frames space;
}			t_assets;

typedef struct s_map
{
	t_list	*map;
	t_point	msize;
	t_point	pp;
}			t_map;

typedef struct s_img
{
	void *ptr;
	char *addr;
	int size;
	int bpp;
	int sline;
	int endian;
} t_img;

typedef enum s_error
{
	MAP_OK = 0,
	EMPTY_FILE = 1,
	NOT_RECT_MAP = 2,
	INVALID_EXT = 3,
	FILE_NOT_FOUND = 4,
	MAP_INVALID = 5,
	MLX_INS = 6,
	ASSETS_ERR = 7,
}			t_error;


typedef struct s_player_animation
{
	t_frames walk[4];
	t_frames idle[4];
} t_player_animation;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_assets	assets;
	t_stats	stats;
	t_map	map;
	t_error	err;
	t_player_animation player;
}			t_mlx;



#endif