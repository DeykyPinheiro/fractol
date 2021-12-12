/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demikael <pinheiromikael96@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:44:01 by demikael          #+#    #+#             */
/*   Updated: 2021/12/11 22:23:02 by demikael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_fractol(t_fractal *mlx, char **argv)
{
	if (argv[1][0] == 'j' || argv[1][0] == 'J')
	{
		mlx->set = "j";
		mlx->c->re = ft_atod(argv[2]);
		mlx->c->im = ft_atod(argv[3]);
	}
	else if (argv[1][0] == 'm' || argv[1][0] == 'M')
		mlx->set = "m";
	else if (argv[1][0] == 'b' || argv[1][0] == 'B')
		mlx->set = "b";
}

int	main(int argc, char **argv)
{
	t_fractal	*mlx;

	(void)argc;
	mlx = (t_fractal *)malloc(sizeof(t_fractal) * 1);
	set_default_fractal(mlx);
	screen(mlx, mlx->datas);
	if (ft_verify_param(argv))
	{
		set_fractol(mlx, argv);
		fractal(mlx);
		mlx_key_hook(mlx->win, &key_event, mlx);
		mlx_mouse_hook(mlx->win, &mouse_event, mlx);
		mlx_loop(mlx->init);
	}
	else
		ft_correct_exit(mlx);
}
