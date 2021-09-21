#include <stdio.h>
#include <stdlib.h>
#include "./minilibx-linux/mlx.h"

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

# define IMG_WIDTH 1000
# define IMG_HEIGHT 1000

typedef struct    s_img
{
    void        *img_ptr;
    int            *data;
    int            size_l;
    int            bpp;
    int            endian;
}                t_img;

typedef struct    s_mlx
{
    void        *mlx_ptr;
    void        *win;
}                t_mlx;

int    main(void)
{
    t_mlx    *mlx;
    t_img    img;
    double x_new;
    double c_re;
    double c_im;
    double x;
    double y;
    int iteration;
    int        row;
    int        col;
    int        max;

    max = 50;

    mlx = malloc(sizeof(void *) * 1);
    mlx->mlx_ptr = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example");
    img.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
    img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

    row = 0;
    col = 0;
    c_re = 0;
    c_im = 0;
    iteration = 0;
    max = 200;
    x = 0;
    y = 0;

    row = 0;
    while (row < IMG_HEIGHT)
    {
        col = 0;
        while (col < IMG_WIDTH)
        {
            c_re = (row - IMG_WIDTH / 2.0) * 4.0 / IMG_WIDTH;
            c_im = (col - IMG_HEIGHT / 2.0) * 4.0 / IMG_WIDTH;
            x = 0;
            y = 0;
            iteration = 0;

            while (x * x + y * y <= 4 && iteration < max)
            {
                x_new = x * x - y * y + c_re;
                y = 2 * x * y + c_im;
                x = x_new;
                iteration++;
            }

            if (iteration < max)
                img.data[col * IMG_WIDTH + row] = 0xfffff+iteration * 3.5;
            else
                img.data[col * IMG_WIDTH + row] = 0x00000;
            col++;
        }
        row++;
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.img_ptr, 0, -150);
    mlx_loop(mlx->mlx_ptr);
    return (0);
}
