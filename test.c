#include "fractol.h"

//struct para inicializar a mlx
typedef struct mlx_var
{
	void	*init;
	void	*window;
	void	*image;
	int		size_x;
	int		size_y;
}	mlx_var;

//funcao setando valores padroes
void	set_default_mlx(mlx_var *mlx)
{
	mlx->init = NULL;
	mlx->window = NULL;
	mlx->image = NULL;
	mlx->size_x = 600;
	mlx->size_y = 400;
}

//funcao para imprimir tela
void	screen(mlx_var *mlx)
{
	mlx->init = mlx_init();
	mlx->window = mlx_new_window(mlx->init, mlx->size_x, mlx->size_y, "Window");
	mlx->image = mlx_new_image(mlx->init, mlx->size_x, mlx->size_y);
	mlx_loop(mlx->init);
}

// // funcao que desenha fractol
// void	fractol(mlx_var *mlx)
// {
// }
// -[] criar funcao para computar a proporcao do pixel
// -[] capturar a mouse event click
// -[] aplicar zoom

// main chamando todas as funcoes
// obrigatorio separar espaco para a variavel
int	main(void)
{
	mlx_var	*mlx;

	mlx = (mlx_var *)malloc(sizeof(mlx_var) * 1);
	set_default_mlx(mlx);
	screen(mlx);
}
