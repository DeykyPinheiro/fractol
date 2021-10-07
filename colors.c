#include "fractol.h"

void	generate_color(t_fractal *mlx)
{
	int		iter;
	float	factor;
	float	diff;

	iter = 0;
	factor = 0;
	while (iter < mlx->max_iter)
	{
		factor = (float)iter / mlx->max_iter;
		if (iter < mlx->max_iter / 2)
			mlx->color[iter] = 255 * iter / mlx->max_iter;
		else
		{
			diff = 1. - factor;
			mlx->r = 9 * diff * (factor * factor * factor) * 255;
			mlx->g = 15 * (diff * diff) * (factor * factor) * 255;
			mlx->b = 8.5 * (diff * diff * diff) * factor * 255;
			mlx->color[iter] = (mlx->r & 0xff) \
			<< 16 |(mlx->g & 0xff) << 8 | (mlx->b & 0xff);
		}
		iter++;
	}
}


void	set_color(int x, int y, t_fractal *mlx, int color)
{
		mlx->data[y * IMG_WIDTH + x] = mlx->color[color];
	// if (color < mlx->max_iter)
	// {
	// 	// // printf("===========================\n");
	// 	// printf("color: %d\n", color);
	// 	// printf("fora\n");
	// 	// printf("===========================\n");
	// 	mlx->data[y * IMG_WIDTH + x] = 0x687178;
	// }
	// else
	// {
	// 	// printf("color: %d\n", color);
	// 	// printf("dentro\n");
	// 	// printf("===========================\n");
	// 	mlx->data[y * IMG_WIDTH + x] = 0x33D4FF;
	// }
}
