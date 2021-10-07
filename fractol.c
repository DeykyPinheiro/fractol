#include "fractol.h"


void	set_fractol(t_fractal *mlx, char **argv)
{
	printf("chamei a funcao\n");
	// printf("aqui tem o: %d\n", argv[1][0] == 'j');
	if (argv[1][0]== 'j' || argv[1][0]== 'J')
	{
		mlx->set = "j";
		printf("entrei no julia\n");
	}
	else if (argv[1][0] == 'm' || argv[1][0] == 'M')
	{
		mlx->set = "m";
		printf("entrei no mandelbrot\n");
	}
	else if (argv[1][0] == 'b' || argv[1][0] == 'B')
	{
		mlx->set = "b";
		printf("entrei no burn\n");

	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	t_fractal		*mlx;
	t_color		*color;

	mlx = (t_fractal *)malloc(sizeof(t_fractal) * 1);
	set_default_fractal(mlx);
	set_fractol(mlx, argv);


	printf("argc: %i\n",argc);
	printf("argv[0]: %s\n", argv[0]);
	printf("argv[1]: %s\n", argv[1]);
	printf("argv[2]: %s\n", argv[2]);
	printf("argv[3]: %s\n", argv[3]);
	printf("argv[4]: %s\n", argv[4]);
	printf("set selection: %s\n", mlx->set);
	printf("\n");




	color = (t_color *)malloc(sizeof(t_color) * 1);
	screen(mlx, color);
	fractal(mlx);
	printf("scale		: %f\n", mlx->scale);
	printf("offset x	: %f\n", mlx->offset_x);
	printf("offset y	: %f\n", mlx->offset_y);
	mlx_key_hook(mlx->win, &key_event, mlx);
	mlx_mouse_hook(mlx->win, mouse_event, mlx);
	mlx_loop(mlx->init);
}
