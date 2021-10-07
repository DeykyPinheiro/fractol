#include "fractol.h"

void	zoom(t_fractal *mlx, double z)
{
	double	mouse_before_x;
	double	mouse_before_y;
	double	mouse_after_x;
	double	mouse_after_y;

	mouse_before_x = (double)mlx->mouse_x / mlx->scale + mlx->offset_x;
	mouse_before_y = (double)mlx->mouse_y / mlx->scale + mlx->offset_y;
	mlx->scale *= z;
	mouse_after_x = (double)mlx->mouse_x / mlx->scale + mlx->offset_x;
	mouse_after_y = (double)mlx->mouse_y / mlx->scale + mlx->offset_y;
	mlx->offset_x += mouse_before_x - mouse_after_x;
	mlx->offset_y += mouse_before_y - mouse_after_y;
	fractal(mlx);
}
