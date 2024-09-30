#include "mrt.h"

void	mrt_clear(t_mrt *mrt)
{
	printf("Clearing...\n");
	if (mrt->mlx_win)
		mlx_destroy_window(mrt->mlx, mrt->mlx_win);
	if (mrt->img.img)
		mlx_destroy_image(mrt->mlx, mrt->img.img);
	if (mrt->mlx)
	{
		printf("Freeing mlx...\n");
		free(mrt->mlx);
	}
	if (mrt->mlx_win)
	{
		printf("Freeing mlx_win...\n");
		free(mrt->mlx_win);
	}
	free_mrt(mrt);
	exit(EXIT_SUCCESS);
}

void	mrt_init(t_mrt *mrt)
{
	printf("Initialising...\n");

	mrt->mlx = NULL;
	mrt->mlx_win = NULL;
	mrt->mlx = mlx_init();
	if (!mrt->mlx)
		mrt_clear(mrt);
	mrt->mlx_win = mlx_new_window(mrt->mlx, WIN_WIDTH, WIN_HEIGHT, "MiniRT");
	mrt->img.img = mlx_new_image(mrt->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!mrt->img.img)
		mrt_clear(mrt);
	mrt->img.addr = mlx_get_data_addr(mrt->img.img, &mrt->img.bits_per_pixel,
			&mrt->img.line_length, &mrt->img.endian);
}
