#include "mrt.h"

void	free_obj(t_mrt *mrt)
{
	printf("Freeing objects...\n");
	if (mrt->spheres)
	{
		free(mrt->spheres);
		mrt->spheres = NULL;
	}
	if (mrt->planes)
	{
		free(mrt->planes);
		mrt->planes = NULL;
	}
	if (mrt->cylinders)
	{
		free(mrt->cylinders);
		mrt->cylinders = NULL;
	}
}

int	close_handler(t_mrt *mrt)
{
	printf("Close handler...\n");
	printf("Destroying mlx...\n");
	if (mrt->mlx.img.img)
		mlx_destroy_image(mrt->mlx.ptr, mrt->mlx.img.img);
	if (mrt->mlx.win)
	{
		mlx_clear_window(mrt->mlx.ptr, mrt->mlx.win);
		mlx_destroy_window(mrt->mlx.ptr, mrt->mlx.win);
	}
	printf("Freeing mrt...\n");
	free_obj(mrt);
	free(mrt->mlx.ptr);

	exit(EXIT_SUCCESS);
}

static int	key_hook(int keycode, t_mrt *mrt)
{
	printf("Key hook...\n");
	if (keycode == ESC_KEY)
		close_handler(mrt);
	return (1);
}

void	mrt_loop(t_mrt *mrt)
{
	mlx_key_hook(mrt->mlx.win, key_hook, mrt);
	mlx_hook(mrt->mlx.win, 17, 0, close_handler, mrt);
	printf("Looping...(main)\n");
	mlx_loop(mrt->mlx.ptr);
}