#include "mrt.h"

int	close_handler(t_mrt *mrt)
{
	printf("Close handler...\n");

	if (mrt->mlx_win)
	{
		mlx_clear_window(mrt->mlx, mrt->mlx_win);
		mlx_destroy_window(mrt->mlx, mrt->mlx_win);
	}
	if (mrt->mlx)
	{
		printf("Freeing mlx...\n");
		free(mrt->mlx);
	}
	exit(EXIT_SUCCESS);
}

int	key_hook(int keysym, t_mrt *mrt)
{
	printf("Key hook...\n");
	if (keysym == ESC_KEY)
		close_handler(mrt);
	return (0);
}