#include "mrt.h"

int	destroy_mlx(t_window *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->img.img)
		mlx_destroy_image(mlx->ptr, mlx->img.img);
	if (mlx->ptr)
		free(mlx->ptr);
	return (0);
}

bool	mrt_init(t_window *mlx)
{
	printf("Initialising...\n");
	mlx->ptr = NULL;
	mlx->win = NULL;
	mlx->img.img = NULL;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (print_error("mlx_init() failed"), false);
	mlx->win = mlx_new_window(mlx->ptr, W_WIDTH, W_HEIGHT, "MiniRT");
	if (!mlx->win)
		return (print_error("mlx_new_window() failed"), destroy_mlx(mlx));
	mlx->img.img = mlx_new_image(mlx->ptr, W_WIDTH, W_HEIGHT);
	if (!mlx->img.img)
		return (print_error("mlx_new_image() failed"), destroy_mlx(mlx));
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
						&mlx->img.line_length, &mlx->img.endian);
	return (true);
}
