#include "fractol.h"

int	mandelbrot_set(t_fractal *mlx)
{
	int		i;
	double	aux;

	i = 0;
	while (complex_abs(mlx->z) < 4 && i < mlx->max_iter)
	{
		aux = pow(mlx->z->re, 2) - pow(mlx->z->im, 2) + mlx->c->re;
		mlx->z->im =  (2.0 * mlx->z->re * mlx->z->im) + mlx->c->im;
		mlx->z->re = aux;
		i++;
	}
	return (i);
}

int	burningship_set(t_fractal *mlx)
{
	int		i;
	double	aux;

	i = 0;
	while (complex_abs(mlx->z) < 4 && i < mlx->max_iter)
	{
		aux = pow(mlx->z->re, 2) - pow(mlx->z->im, 2) + mlx->c->re;
		mlx->z->im =  ft_abs(2.0 * mlx->z->re * mlx->z->im) + mlx->c->im;
		mlx->z->re = aux;
		i++;
	}
	return (i);
}
