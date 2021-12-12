/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demikael <pinheiromikael96@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:41:31 by demikael          #+#    #+#             */
/*   Updated: 2021/12/11 23:02:39 by demikael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				init_j(x, y, mlx);
			else if (mlx->set[0] == 'm')
				init_m(x, y, mlx);
			else if (mlx->set[0] == 'b')
				init_b(x, y, mlx);
			if (mlx->set[0] == 'b')
				color = burningship_set(mlx);
			else
				color = mandelbrot_set(mlx);
			set_color(x, y, mlx, color);
		}
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
}

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
}
