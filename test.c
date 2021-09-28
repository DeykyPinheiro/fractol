#include "fractol.h"

//numeros complexos
typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;



typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
	char	*data;
	int		size_x;
	int		size_y;
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
	mlx->size_x = 400;
	mlx->size_y = 300;
}

void screen(t_mlx *mlx, t_color *color)
{
	mlx->init = mlx_init();
	mlx->win = mlx_new_window(mlx->init, mlx->size_x, mlx->size_y, "Window");
	mlx->img = mlx_new_image(mlx->init, mlx->size_x, mlx->size_y);
	mlx->data = mlx_get_data_addr(mlx->init, &color->bits_per_pixel, \
	&color->size_line, &color->endian);
	mlx_loop(mlx->init);
}

int	main(void)
{
	t_mlx	*mlx;
	t_color	*color;
	t_complex *c;

	c = (t_complex *)malloc(sizeof(t_complex) * 1);
	mlx = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	color = (t_color *)malloc(sizeof(t_color) * 1);


	set_default_mlx(mlx);
	screen(mlx, color);
}
