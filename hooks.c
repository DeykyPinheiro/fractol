#include "fractol.h"

// mouse function
int	mouse_event(int button, int x, int y, void *param)
{
	t_fractal	*mlx;

	mlx = param;
	mlx->mouse_button = button;
	mlx->mouse_x = (double)x;
	mlx->mouse_y = (double)y;
	printf("=======================================\n");
	printf("mouse button	: %d\n", mlx->mouse_button);
	printf("x		: %d\n", mlx->mouse_x);
	printf("y		: %d\n", mlx->mouse_y);
	printf("scale		: %f\n", mlx->scale);
	printf("offset x	: %f\n", mlx->offset_x);
	printf("offset y	: %f\n", mlx->offset_y);
	if (button == 4)
	{
		zoom(mlx, 1.1);
	}
	else if (button == 5)
	{
		zoom(mlx, 0.9);
	}
	return (1);
}

int	key_event(int button, void *param)
{
	t_fractal	*mlx;

	mlx = param;
	mlx->keyboard = button;
	if (button == 105)
	{
		mlx->mouse_x = IMG_WIDTH / 2;
		mlx->mouse_y = IMG_HEIGHT / 2;
		mlx->scale = ((IMG_HEIGHT / 2) + (IMG_WIDTH / 2)) / 4;
		mlx->offset_x = IMG_WIDTH / 2 / mlx->scale * -1;
		mlx->offset_y = IMG_HEIGHT / 2 / mlx->scale * -1;
		fractal(mlx);
	}
	else if (button == 107)
	{
		zoom(mlx, 1.1);
	}
	else if (button == 108)
	{
		zoom(mlx, 0.9);
	}
	else if (button == 119 || button == 65362)
	{
		mlx->offset_y += (ft_abs(mlx->offset_y / mlx->scale) * -1);
		fractal(mlx);
	}
	else if (button == 115 || button == 65364)
	{
		mlx->offset_y -= (ft_abs(mlx->offset_y / mlx->scale) * -1);
		fractal(mlx);
	}
	else if (button == 97 || button == 65361)
	{
		mlx->offset_x += (ft_abs(mlx->offset_x / mlx->scale) * -1);
		fractal(mlx);
	}
	else if (button == 100 || button == 65363)
	{
		mlx->offset_x -= (ft_abs(mlx->offset_x / mlx->scale) * -1);
		fractal(mlx);
	}
	else if (button == 65307)
	{
		exit(1);
	}
	printf("=======================================\n");
	printf("keyborad key	: %d\n", button);
	printf("x		: %d\n", mlx->mouse_x);
	printf("y		: %d\n", mlx->mouse_y);
	printf("scale		: %f\n", mlx->scale);
	printf("offset x	: %f\n", mlx->offset_x);
	printf("offset y	: %f\n", mlx->offset_y);
	return (1);
}
