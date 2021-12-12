/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demikael <pinheiromikael96@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:47:56 by demikael          #+#    #+#             */
/*   Updated: 2021/12/11 20:47:56 by demikael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_correct_exit(t_fractal *mlx)
{
	mlx_destroy_image(mlx->init, mlx->img);
	mlx_destroy_window(mlx->init, mlx->win);
	mlx_destroy_display(mlx->init);
	free(mlx->init);
	free(mlx->z);
	free(mlx->c);
	free(mlx->datas);
	free(mlx);
	exit(EXIT_SUCCESS);
}
