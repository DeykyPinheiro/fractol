/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demikael <pinheiromikael96@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:13:56 by demikael          #+#    #+#             */
/*   Updated: 2021/12/11 20:38:55 by demikael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map_to_re(int x, t_fractal *mlx)
{
	return (x / mlx->scale + mlx->offset_x);
}

double	map_to_im(int y, t_fractal *mlx)
{
	return (y / mlx->scale + mlx->offset_y);
}

void	init_j(int x, int y, t_fractal *mlx)
{
	mlx->z->im = map_to_im(y, mlx);
	mlx->z->re = map_to_re(x, mlx);
}

void	init_m(int x, int y, t_fractal *mlx)
{
	mlx->c->im = map_to_im(y, mlx);
	mlx->c->re = map_to_re(x, mlx);
	mlx->z->re = 0;
	mlx->z->im = 0;
}

void	init_b(int x, int y, t_fractal *mlx)
{
	mlx->c->im = map_to_im(y, mlx);
	mlx->c->re = map_to_re(x, mlx);
	mlx->z->re = 0;
	mlx->z->im = 0;
}
