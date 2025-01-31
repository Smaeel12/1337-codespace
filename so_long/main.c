/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:43:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/30 15:20:29 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 832
#define HEIGHT 608
#define ESCAPE 65307


typedef struct s_img
{
    void *ptr;
    char *addr;
    int bpp;
    int sline;
    int endian;
} t_img;

typedef struct s_char
{
    t_img img;
    int width;
    int height;
    int offx;
    int offy;
} t_char;

typedef struct s_wall
{
    t_img img;
    int width;
    int height;
} t_wall;

typedef struct s_mlx
{
    void *ptr;
    void *win;
    t_char character;
    t_wall walls;
} t_mlx;

int my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = img->addr + (y * img->sline + (x * (img->bpp / 8)));
        *(unsigned int *) dst = color;
    }
}

int close_window(t_mlx *mlx)
{
    mlx_destroy_image(mlx->ptr, mlx->character.img.ptr);
    mlx_destroy_window(mlx->ptr, mlx->win);
    exit(1);
}


int move_char(int keycode, t_char *character)
{
    if (keycode == 'w')
        character->offy -= 32;
    if (keycode == 's')
        character->offy += 32;
    if (keycode == 'a')
        character->offx -= 32;
    if (keycode == 'd')
        character->offx += 32;
    // printf("%i\n", keycode);
}

int keypress(int keycode, t_mlx *mlx)
{
    if (keycode == ESCAPE)
        close_window(mlx);
    else
        move_char(keycode, &mlx->character);
}

int render_map(t_mlx *mlx)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; (y < 32 || y > HEIGHT - 32) && x < WIDTH; x++)  // Draw across full width
        {
            my_mlx_pixel_put(&mlx->walls.img, x, y, 0xFF0000);
        }
    }
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; (x < 32 || x > WIDTH - 32) && y < HEIGHT; y++)  // Draw across full width
        {
            my_mlx_pixel_put(&mlx->walls.img, x, y, 0xFF0000);
        }
    }
    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->walls.img.ptr, 0, 0);
    return 0;
}

int render_char(t_mlx *mlx)
{
    mlx_clear_window(mlx->ptr, mlx->win);
    render_map(mlx);
    for (int y = 0; y < mlx->character.height; y++)
    {
        for (int x = 0; x < mlx->character.width; x++)
            my_mlx_pixel_put(&mlx->character.img, x, y, 0xFFFFFF);
    }
    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->character.img.ptr, mlx->character.offx, mlx->character.offy);
}


#include <stdio.h>
int main()
{
    t_mlx mlx;

    mlx.ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.ptr, WIDTH, HEIGHT, "GAME OF THRONES");    
    mlx.character = (t_char) {{NULL}, 32, 32, 32, 32};
    mlx.walls = (t_wall) {{NULL}, 32, 32};
    
    mlx.character.img.ptr = mlx_new_image(mlx.ptr, mlx.character.width, mlx.character.height);
    mlx.character.img.addr = mlx_get_data_addr(mlx.character.img.ptr, &mlx.character.img.bpp, &mlx.character.img.sline, &mlx.character.img.endian);
    
    mlx.walls.img.ptr = mlx_new_image(mlx.ptr, WIDTH, HEIGHT);
    mlx.walls.img.addr = mlx_get_data_addr(mlx.walls.img.ptr, &mlx.walls.img.bpp, &mlx.walls.img.sline, &mlx.walls.img.endian);
    
    
    mlx_hook(mlx.win, 2, 1L<<0, keypress, &mlx);
    mlx_hook(mlx.win, 17, 0, close_window, &mlx);

    mlx_loop_hook(mlx.ptr, render_char, &mlx);
    mlx_loop(mlx.ptr);
}