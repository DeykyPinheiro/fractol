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

typedef struct s_fractal
{
	void		*init;
	void		*win;
	void		*img;
	int			*data;
	int			mouse_button;
	int			offset_x;
	int			offset_y;
	int			max_iter;
	t_complex	*z;
	t_complex	*c;
	t_dimension	*limits;
}	t_fractal;

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
	mlx->img =NULL;
	mlx->data = NULL;
	mlx->mouse_button = 1;
	mlx->offset_x = 0;
	mlx->offset_y = 0;
	mlx->max_iter = 50;
	mlx->z = (t_complex *)malloc(sizeof(t_complex) * 1);
	mlx->c = (t_complex *)malloc(sizeof(t_complex) * 1);
	mlx->limits = (t_dimension *)malloc(sizeof(t_dimension) * 1);
}

void	set_default_dimension(t_fractal *mlx)
{
	mlx->limits->MinRe = -2.0;
	mlx->limits->MaxRe = 1.0;
	mlx->limits->MinIm = -1.2;
	mlx->limits->MaxIm = mlx->limits->MinIm + \
	(mlx->limits->MaxRe - mlx->limits->MinRe) \
	* IMG_HEIGHT / IMG_WIDTH;
}

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
	double	range;
	range = mlx->limits->MaxRe - mlx->limits->MinRe;
	return (x * (range / IMG_WIDTH) + mlx->limits->MinRe);
}

// aponta onde fica a parte imaginaria, converte em y na img
double	map_to_im(int y, t_fractal *mlx)
{
	double	range;
	// printf("entrei no map_to_im\n");
	range = mlx->limits->MaxIm - mlx->limits->MinIm;
	return (y * (range / IMG_HEIGHT) + mlx->limits->MinIm);
}

//mandelbrot
int	mandelbrot_set(t_fractal *mlx)
{
	int		i;
	double	aux;

	i = 0;
	mlx->z->re = 0;
	mlx->z->im = 0;
	while (complex_abs(mlx->z) < 4 && i < mlx->max_iter)
	{
		aux = pow(mlx->z->re, 2) - pow(mlx->z->im, 2) + mlx->c->re;
		mlx->z->im = (2.0 * mlx->z->re * mlx->z->im) + mlx->c->im;
		mlx->z->re = aux;
		i++;
	}

	// printf("i: %i\n", i);
	return (i);
}

void	set_color(int x, int y, t_fractal *mlx, int color)
{
	if (color < mlx->max_iter)
	{
		// // printf("===========================\n");
		// printf("color: %d\n", color);
		// printf("fora\n");
		// printf("===========================\n");
		mlx->data[y * IMG_WIDTH + x] = 0x687178;
	}
	else
	{
		// printf("color: %d\n", color);
		// printf("dentro\n");
		// printf("===========================\n");
		mlx->data[y * IMG_WIDTH + x] = 0x33D4FF;
	}
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
			mlx->c->re = map_to_re(x, mlx);
			mlx->c->im = map_to_im(y, mlx);
			color = mandelbrot_set(mlx);
			set_color(x, y, mlx, color);
		}
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
}


void	zoom(t_fractal *mlx, double z)
{
	double	aux;
	// centraliza o ponto selecionado pelo mouse
	mlx->c->re = mlx->limits->MinRe + (mlx->limits->MaxRe - mlx->limits->MinRe) * mlx->offset_x / IMG_WIDTH;

	mlx->c->im = mlx->limits->MinIm + (mlx->limits->MaxIm - mlx->limits->MinIm) * mlx->offset_y / IMG_HEIGHT;

	//zoom
	aux = mlx->c->re - (mlx->limits->MaxRe - mlx->limits->MinRe) / z;


	mlx->limits->MaxRe = mlx->c->re + (mlx->limits->MaxRe - mlx->limits->MinRe) / z;

	mlx->limits->MinRe = aux;

	aux = mlx->c->im - (mlx->limits->MaxIm - mlx->limits->MinIm) / 2 / z;
	mlx->limits->MaxIm = mlx->c->im + (mlx->limits->MaxIm - mlx->limits->MinIm) / 2 / z;
	mlx->limits->MinIm = aux;
	printf("max re		: %f\n", mlx->limits->MaxRe);
	printf("min re		: %f\n", mlx->limits->MinRe);
	printf("max im		: %f\n", mlx->limits->MaxIm);
	printf("min im		: %f\n", mlx->limits->MinIm);
	printf("c re		: %f\n", mlx->c->re);
	printf("c im		: %f\n", mlx->c->im);
	printf("offset_x	: %d\n", mlx->offset_x);
	printf("offset_y	: %d\n", mlx->offset_y);
	fractal(mlx);
}

// mouse function
int mouse_event(int button, int x, int y, void *param)
{
	t_fractal *mlx = param;
	mlx->mouse_button = button;
	mlx->offset_x = x;
	mlx->offset_y = y;
	printf("=======================================\n");
	printf("button		: %d\n", mlx->mouse_button);
	printf("x		: %d\n", mlx->offset_x);
	printf("y		: %d\n", mlx->offset_y);

	if (button == 4)
	{
		zoom(mlx, 1.1);
		printf("zoom in\n");
	}
	else if(button == 5)
	{
		zoom(mlx, 0.9);
		printf("zoom out\n");

	}
	return (1);
}

int	main(void)
{
	t_fractal		*mlx;
	t_color		*color;

	mlx = (t_fractal *)malloc(sizeof(t_fractal) * 1);
	color = (t_color *)malloc(sizeof(t_color) * 1);

	set_default_fractal(mlx);
	set_default_dimension(mlx);
	screen(mlx, color);
	fractal(mlx);
	mlx_mouse_hook(mlx->win, mouse_event, mlx);
	mlx_loop(mlx->init);
}
