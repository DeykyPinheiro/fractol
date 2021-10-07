#include "fractol.h"

void	fractal(t_fractal *mlx)
{
	int		x;
	int		y;
	int		color;

	y = -1;
	while (++y < IMG_HEIGHT)
	{
		x = -1;
		while (++x < IMG_WIDTH)
		{
			if (mlx->set[0] == 'j')
			{
				mlx->z->im = map_to_im(y, mlx);
				mlx->z->re = map_to_re(x, mlx);
				mlx->c->re = -0.80;
				mlx->c->im = 0.156;
			}
			else if (mlx->set[0] == 'm')
			{
				mlx->c->im = map_to_im(y, mlx);
				mlx->c->re = map_to_re(x, mlx);
				mlx->z->re = 0;
				mlx->z->im = 0;
			}
			else if (mlx->set[0] == 'b')
			{
				mlx->c->im = map_to_im(y, mlx);
				mlx->c->re = map_to_re(x, mlx);
				mlx->z->re = 0;
				mlx->z->im = 0;
			}
			color = mandelbrot_set(mlx);
			set_color(x, y, mlx, color);
		}
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
}

double	map_to_re(int x, t_fractal *mlx)
{
	return (x / mlx->scale + mlx->offset_x);
}

double	map_to_im(int y, t_fractal *mlx)
{
	return (y / mlx->scale + mlx->offset_y);
}
