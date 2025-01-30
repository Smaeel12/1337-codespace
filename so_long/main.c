/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:08:24 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/29 19:03:01 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include 

#define WIDTH 800
#define HEIGHT 640

typedef struct s_char
{
    void *img;
    int width;
    int height;
    int offx;
    int offy;
    int keys[4];
} t_char;

typedef struct s_mlx
{
    void *ptr;
    void *win;
    t_char character;
} t_mlx;

int keypress(int keycode, t_mlx *mlx)
{
    if (keycode == 'a')
        mlx->character.keys[0] = 1;
    if (keycode == 'd')
        mlx->character.keys[1] = 1;
    if (keycode == 'w')
        mlx->character.keys[2] = 1;
    if (keycode == 's')
        mlx->character.keys[3] = 1;
    usleep(10000);
}

int keyrelease(int keycode, t_mlx *mlx)
{
    if (keycode == 'a')
        mlx->character.keys[0] = 0;
    if (keycode == 'd')
        mlx->character.keys[1] = 0;
    if (keycode == 'w')
        mlx->character.keys[2] = 0;
    if (keycode == 's')
        mlx->character.keys[3] = 0;
}

int render_char(t_mlx *mlx)
{
    if (mlx->character.keys[0] == 'a')
        mlx->character.offx -= 5;
    if (mlx->character.keys[1] == 'd')
        mlx->character.offx += 5;
    if (mlx->character.keys[2] == 'w')
        mlx->character.offy -= 5;
    if (mlx->character.keys[3] == 's')
        mlx->character.offy += 5;
    mlx_clear_window(mlx->ptr, mlx->win);
    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->character.img, mlx->character.offx, mlx->character.offy);
    return 0;
}

int main()
{
    t_mlx mlx;

    mlx.ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.ptr, WIDTH, HEIGHT, "GAME OF THRONES");
    mlx.character = (t_char) {NULL, 0, 0, 0, 0};
    mlx.character.img = mlx_xpm_file_to_image(mlx.ptr, "idle.xpm", &mlx.character.width, &mlx.character.height);
    
    
    mlx_hook(mlx.win, 2, 1L<<0, keypress, &mlx);
    mlx_hook(mlx.win, 2, 1L<<1, keyrelease, &mlx);
    mlx_loop_hook(mlx.ptr, render_char, &mlx);
    mlx_loop(mlx.ptr);
}