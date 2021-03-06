/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demikael <pinheiromikael96@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:25:34 by demikael          #+#    #+#             */
/*   Updated: 2021/12/14 01:31:41 by demikael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libraries/minilibx/mlx.h"
# include "./libraries/libft/libft.h"

# define IMG_WIDTH 600
# define WIN_WIDTH 600

// # define WIN_WIDTH 800
# define WIN_HEIGHT 500
# define IMG_HEIGHT 500

// # define IMG_WIDTH 800

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_color
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_color;

typedef struct s_fractal
{
	char			*set;
	void			*init;
	void			*win;
	void			*img;
	int				*data;
	int				mouse_button;
	int				mouse_x;
	int				mouse_y;
	int				keyboard;
	double			offset_x;
	double			offset_y;
	int				max_iter;
	double			scale;
	unsigned int	color[255];
	int				r;
	int				g;
	int				b;
	t_color			*datas;
	t_complex		*z;
	t_complex		*c;
}	t_fractal;

double	ft_atod(const char *nptr);
int		mouse_event(int button, int x, int y, void *param);
int		key_event(int button, void *param);
void	set_fractol(t_fractal *mlx, char **argv, int argc);
double	complex_abs(t_complex *z);
void	set_default_fractal(t_fractal *mlx);
void	screen(t_fractal *mlx, t_color *color);
void	zoom(t_fractal *mlx, double z);
int		mandelbrot_set(t_fractal *mlx);
int		burningship_set(t_fractal *mlx);
void	generate_color(t_fractal *mlx);
void	set_color(int x, int y, t_fractal *mlx, int color);
void	fractal(t_fractal *mlx);
double	map_to_re(int x, t_fractal *mlx);
double	map_to_im(int y, t_fractal *mlx);
double	ft_abs(double n);
double	pow(double x, double n);
int		t_point_valid(char *number);
int		ft_only_digit(char *number);
int		ft_valid_len(int number);
void	ft_correct_exit(t_fractal *mlx);
int		ft_verify_param(char **argv);
void	init_j(int x, int y, t_fractal *mlx);
void	init_m(int x, int y, t_fractal *mlx);
void	init_b(int x, int y, t_fractal *mlx);

#endif
