#include "mrt.h"

int	close_handler(t_mrt *mrt)
{
	printf("Close handler...\n");
	if (mrt->img.img)
		mlx_destroy_image(mrt->mlx, mrt->img.img);
	if (mrt->mlx_win)
	{
		mlx_clear_window(mrt->mlx, mrt->mlx_win);
		mlx_destroy_window(mrt->mlx, mrt->mlx_win);
	}
	if (mrt->mlx)
	{
		printf("Freeing mlx...\n");
		free(mrt->mlx);
		mrt->mlx = NULL;
	}
	free_mrt(mrt);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keysym, t_mrt *mrt)
{
	printf("Key hook...\n");
	if (keysym == ESC_KEY)
		close_handler(mrt);
	return (0);
}


void	hook_init(t_mrt *mrt)
{
	printf("Hook init...\n");
	mlx_key_hook(mrt->mlx_win, key_hook, mrt);
	mlx_hook(mrt->mlx_win, 17, 1L<<17, close_handler, mrt);
}
