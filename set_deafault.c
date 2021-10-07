#include "fractol.h"

void	set_default_fractal(t_fractal *mlx)
{
	mlx->init = NULL;
	mlx->win = NULL;
	mlx->img = NULL;
	mlx->data = NULL;
	mlx->mouse_button = 1;
	mlx->mouse_x = IMG_WIDTH / 2;
	mlx->mouse_y = IMG_HEIGHT / 2;
	mlx->max_iter = 255;
	mlx->scale = ((IMG_HEIGHT / 2) + (IMG_WIDTH / 2)) / 4;
	mlx->offset_x = IMG_WIDTH / 2 / mlx->scale * -1;
	mlx->offset_y = IMG_HEIGHT / 2 / mlx->scale * -1;
	// mlx->z->re = 0;
	// mlx->z->im = 0;
	mlx->z = (t_complex *)malloc(sizeof(t_complex) * 1);
	mlx->c = (t_complex *)malloc(sizeof(t_complex) * 1);
	generate_color(mlx);
}

void	screen(t_fractal *mlx, t_color *color)
{
	mlx->init = mlx_init();
	mlx->win = mlx_new_window(mlx->init, WIN_WIDTH, WIN_HEIGHT, "Window");
	mlx->img = mlx_new_image(mlx->init, IMG_WIDTH, IMG_HEIGHT);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &color->bits_per_pixel, \
	&color->size_line, &color->endian);
}
