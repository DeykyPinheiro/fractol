#include "fractol.h"

# define IMG_WIDTH 600
# define WIN_WIDTH 600

// # define WIN_WIDTH 800
# define WIN_HEIGHT 500
# define IMG_HEIGHT 500

// # define IMG_WIDTH 800
double	ft_abs(double n)
{
	if (n  < 0)
		return (-n);
	return (n);
}

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

double	pow(double x, double n)
{
	int		c;
	double	r;

	r = 1;
	c = 0;
	while (c < n)
	{
		r = r * x;
		c++;
	}
	return (r);
}

double	complex_abs(t_complex *z)
{
	return (pow(z->re, 2) + pow(z->im, 2));
}

typedef struct s_dimension
{
	double	MinRe;
	double	MaxRe;
	double	MinIm;
	double	MaxIm;
}	t_dimension;

typedef struct s_fractal
{
	void		*init;
	void		*win;
	void		*img;
	int			*data;
	int			mouse_button;
	int			mouse_x;
	int			mouse_y;
	int			keyboard;
	double		offset_x;
	double		offset_y;
	int			max_iter;
	double			scale;
	unsigned int	color[255];
	int			r;
	int			g;
	int			b;
	t_complex	*z;
	t_complex	*c;
	t_dimension	*limits;
}	t_fractal;

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

typedef struct s_color
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_color;

void	set_default_fractal(t_fractal *mlx)
{
	mlx->init = NULL;
	mlx->win = NULL;
	mlx->img = NULL;
	mlx->data = NULL;
	mlx->mouse_button = 1;
	mlx->mouse_x = IMG_WIDTH / 2;
	mlx->mouse_y = IMG_HEIGHT / 2;
	mlx->max_iter = 255;
	mlx->scale = ((IMG_HEIGHT / 2) + (IMG_WIDTH / 2)) / 4;
	mlx->offset_x = IMG_WIDTH / 2 / mlx->scale * -1;
	mlx->offset_y = IMG_HEIGHT / 2 / mlx->scale * -1;
	// mlx->z->re = 0;
	// mlx->z->im = 0;
	mlx->z = (t_complex *)malloc(sizeof(t_complex) * 1);
	mlx->c = (t_complex *)malloc(sizeof(t_complex) * 1);
	mlx->limits = (t_dimension *)malloc(sizeof(t_dimension) * 1);
	generate_color(mlx);
}

//apagar pq não to usando
// void	set_default_dimension(t_fractal *mlx)
// {
// 	mlx->limits->MinRe = -2.0;
// 	mlx->limits->MaxRe = 1.0;
// 	mlx->limits->MinIm = -1.2;
// 	mlx->limits->MaxIm = mlx->limits->MinIm + \
// 	(mlx->limits->MaxRe - mlx->limits->MinRe) \
// 	* IMG_HEIGHT / IMG_WIDTH;
// }

void	screen(t_fractal *mlx, t_color *color)
{
	mlx->init = mlx_init();
	mlx->win = mlx_new_window(mlx->init, WIN_WIDTH, WIN_HEIGHT, "Window");
	mlx->img = mlx_new_image(mlx->init, IMG_WIDTH, IMG_HEIGHT);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &color->bits_per_pixel, \
	&color->size_line, &color->endian);
}

// aponta para onde vai ficar a parte real na tela, converte em x na img
double	map_to_re(int x, t_fractal *mlx)
{
	return (x / mlx->scale + mlx->offset_x);
}

// aponta onde fica a parte imaginaria, converte em y na img
double	map_to_im(int y, t_fractal *mlx)
{
	return (y / mlx->scale + mlx->offset_y);
}

//mandelbrot
int	mandelbrot_set(t_fractal *mlx)
{
	int		i;
	double	aux;
	// printf("before z re: %f\n", mlx->z->re);
	// printf("before z im: %f\n", mlx->z->im);

	i = 0;
	// mlx->c->re  = -0.70176;
	// mlx->c->im = -0.3842;
	while (complex_abs(mlx->z) < 4 && i < mlx->max_iter)
	{
		aux = pow(mlx->z->re, 2) - pow(mlx->z->im, 2) + mlx->c->re;
		mlx->z->im = (2.0 * mlx->z->re * mlx->z->im) + mlx->c->im;
		mlx->z->re = aux;
		i++;
		// printf("i : %d\n", i);
	}
	// printf("after z re: %f\n", mlx->z->re);
	// printf("after z im: %f\n", mlx->z->im);
	// printf("===========================\n");

	// printf("i: %i\n", i);s
	// printf("c re: %f\n", mlx->c->re);
	// printf("c im: %f\n", mlx->c->im);
	return (i);
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
			// printf("x: %d\n", x);
			// mlx->c->re = x / mlx->scale + mlx->offset_x;
			mlx->z->re = map_to_re(x, mlx);
			mlx->z->im = map_to_im(y, mlx);
			mlx->c->re = -0.8;
			mlx->c->im = 0.156;
			// printf("c re: %f\n", mlx->c->re);
			// printf("c im: %f\n", mlx->c->im);
			color = mandelbrot_set(mlx);
			set_color(x, y, mlx, color);
		}

	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
}


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
int	key_event(int button, void *param)
{
	t_fractal *mlx = param;

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
		// printf("zoom in\n");
	}
	else if(button == 108)
	{
		zoom(mlx, 0.9);
		// printf("zoom out\n");
	}
	// up 119 65362
	else if (button == 119 || button == 65362)
	{
		mlx->offset_y += (ft_abs(mlx->offset_y / mlx->scale) * -1);
		fractal(mlx);
	}
	// down 115 65364
	else if (button == 115 || button == 65364)
	{
		mlx->offset_y -= (ft_abs(mlx->offset_y / mlx->scale) * -1);
		fractal(mlx);
	}
	// left 97 65361
	else if (button == 97 || button == 65361)
	{
		mlx->offset_x += (ft_abs(mlx->offset_x / mlx->scale) * -1);
		fractal(mlx);
	}
	// right 100 65363
	else if (button == 100 || button == 65363)
	{
		mlx->offset_x -= (ft_abs(mlx->offset_x / mlx->scale) * -1);
		fractal(mlx);
	}
	else if(button == 65307)
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
// mouse function
int mouse_event(int button, int x, int y, void *param)
{
	t_fractal *mlx = param;
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
		// printf("zoom in\n");
	}
	else if(button == 5)
	{
		zoom(mlx, 0.9);
		// printf("zoom out\n");

	}
	return (1);
}

int	main(int argc,char **argv)
{
	t_fractal		*mlx;
	t_color		*color;

	printf("argv[0]: %s\n", argv[0]);
	printf("argv[1]: %s\n", argv[1]);
	printf("argv[2]: %s\n", argv[argc ]);

	mlx = (t_fractal *)malloc(sizeof(t_fractal) * 1);
	color = (t_color *)malloc(sizeof(t_color) * 1);

	set_default_fractal(mlx);
	// printf("setei o padrao\n");
	// set_default_dimension(mlx);
	screen(mlx, color);
	fractal(mlx);
	printf("scale		: %f\n", mlx->scale);
	printf("offset x	: %f\n", mlx->offset_x);
	printf("offset y	: %f\n", mlx->offset_y);
	mlx_key_hook(mlx->win, &key_event, mlx);
	mlx_mouse_hook(mlx->win, mouse_event, mlx);
	mlx_loop(mlx->init);
}


