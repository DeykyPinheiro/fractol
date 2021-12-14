/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demikael <pinheiromikael96@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:44:01 by demikael          #+#    #+#             */
/*   Updated: 2021/12/14 01:34:00 by demikael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	warning(void)
{
	printf("PARAMETER ERROR\ntype 'M', 'J' or 'B' for mandelbroth \
Julia or Burniship spec.\nYou can enter parameters for \
Julia. Real/Imag such as:\n./fractol j -0.8 0.156\n");
}

static void	verify(int argc, char **argv, t_fractal *mlx)
{
	if (argv[1][1])
	{
		warning();
		ft_correct_exit(mlx);
	}
	else if (argc == 2)
	{
		if ((!(argv[1][0] == 'm' || argv[1][0] == 'M')) \
		&& (!(argv[1][0] == 'b' || argv[1][0] == 'B')))
		{
			warning();
			ft_correct_exit(mlx);
		}
	}
	else if (argc == 4)
	{
		if (!(argv[1][0] == 'j' || argv[1][0] == 'J'))
		{
			warning();
			ft_correct_exit(mlx);
		}
	}
}

void	set_fractol(t_fractal *mlx, char **argv, int argc)
{
	if ((argv[1][0] == 'j' || argv[1][0] == 'J') && argc == 4)
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

static void	rotine(t_fractal *mlx)
{
	fractal(mlx);
	mlx_key_hook(mlx->win, &key_event, mlx);
	mlx_mouse_hook(mlx->win, &mouse_event, mlx);
	mlx_loop(mlx->init);
}

int	main(int argc, char **argv)
{
	t_fractal	*mlx;

	mlx = (t_fractal *)malloc(sizeof(t_fractal) * 1);
	set_default_fractal(mlx);
	set_fractol(mlx, argv, argc);
	screen(mlx, mlx->datas);
	verify(argc, argv, mlx);
	if (mlx->set[0] == 'j' && ft_verify_param(argv))
		rotine(mlx);
	else if (mlx->set[0] == 'b' || mlx->set[0] == 'm')
		rotine(mlx);
	else
	{
		warning();
		ft_correct_exit(mlx);
	}
}
