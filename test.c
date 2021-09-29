#include "fractol.h"


# define WIN_WIDTH 400
# define WIN_HEIGHT 300

# define IMG_WIDTH 400
# define IMG_HEIGHT 300

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

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
	int		*data;
	int		mouse_button;
	int		offset_x;
	int		offset_y;
}	t_mlx;

typedef struct s_color
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_color;

void	set_default_mlx(t_mlx *mlx)
{
	mlx->init = NULL;
	mlx->win = NULL;
	mlx->img = NULL;
	mlx->data = NULL;
}

void	set_default_dimension(t_dimension *limits)
{
	limits->MinRe = -2.0;
	limits->MaxRe = 1.0;
	limits->MinIm = - 1.2;
	limits->MaxIm = limits->MinIm + (limits->MaxRe - limits->MinRe) \
	* IMG_HEIGHT / IMG_WIDTH;
}

void	screen(t_mlx *mlx, t_color *color)
{
	mlx->init = mlx_init();
	mlx->win = mlx_new_window(mlx->init, WIN_WIDTH, WIN_HEIGHT, "Window");
	mlx->img = mlx_new_image(mlx->init, IMG_WIDTH, IMG_HEIGHT);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &color->bits_per_pixel, \
	&color->size_line, &color->endian);
}

// aponta para onde vai ficar a parte real na tela, converte em x na img
double	map_to_re(int x, t_dimension *limits)
{
	double	range;

	range = limits->MaxRe - limits->MinRe;
	return (x * (range / IMG_WIDTH) + limits->MinRe);
}

// aponta onde fica a parte imaginaria, converte em y na img
double	map_to_im(int y, t_dimension *limits)
{
	double	range;

	range = limits->MaxIm - limits->MinIm;
	return (y * (range / IMG_HEIGHT) + limits->MinIm);
}

//mandelbrot
int	mandelbrot_set(t_complex *c, t_complex *z, int max_iter)
{
	int		i;
	double	aux;

	i = 0;
	z->re = 0;
	z->im = 0;
	while (complex_abs(z) < 4 && i < max_iter)
	{
		aux = pow(z->re, 2) - pow(z->im, 2) + c->re;
		z->im = (2.0 * z->re * z->im) + c->im;
		z->re = aux;
		i++;
	}
	return (i);
}

void	set_color(int x, int y, t_mlx *mlx, int color, int max_iter)
{
	if (color < max_iter)
	{
		// // printf("===========================\n");
		// printf("color: %d\n", color);
		// printf("fora\n");
		// printf("===========================\n");
		mlx->data[y * IMG_WIDTH + x] = 0xFFFFFF;
	}
	else
	{
		// printf("color: %d\n", color);
		// printf("dentro\n");
		// printf("===========================\n");
		mlx->data[y * IMG_WIDTH + x] = 0x33D4FF;
	}
}

void	fractal(t_complex *c, t_complex *z, int max_iter, t_dimension *limits, \
t_mlx *mlx)
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
			c->re = map_to_re(x, limits);
			c->im = map_to_im(y, limits);
			color = mandelbrot_set(c, z, 50);
			set_color(x, y, mlx, color, max_iter);
		}
	}
}

// mouse function
int mouse_event(int button, int x, int y, void *param)
{
	t_mlx *mlx = param;
	mlx->mouse_button = button;
	mlx->offset_x = x;
	mlx->offset_y= y;
	printf("=======================================\n");
	printf("button		: %d\n", mlx->mouse_button);
	printf("x		: %d\n", mlx->offset_x);
	printf("y		: %d\n", mlx->offset_y);
	return (1);
}

int	main(void)
{
	t_complex	*c;
	t_complex	*z;
	t_mlx		*mlx;
	t_color		*color;
	t_dimension	*limits;

	limits = (t_dimension *)malloc(sizeof(t_dimension) * 1);
	mlx = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	color = (t_color *)malloc(sizeof(t_color) * 1);
	z = (t_complex *)malloc(sizeof(t_complex) * 1);
	c = (t_complex *)malloc(sizeof(t_complex) * 1);
	set_default_mlx(mlx);
	set_default_dimension(limits);
	screen(mlx, color);
	fractal(c, z, 50, limits, mlx);
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
	mlx_mouse_hook(mlx->win, mouse_event, mlx);

	mlx_loop(mlx->init);
}
