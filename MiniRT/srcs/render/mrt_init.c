#include "mrt.h"

void	mrt_clear(t_mrt *mrt)
{
	if (mrt->mlx_win)
		mlx_destroy_window(mrt->mlx, mrt->mlx_win);
	if (mrt->img.img)
		mlx_destroy_image(mrt->mlx, mrt->img.img);
	if (mrt->mlx)
		free(mrt->mlx);
	free_mrt(mrt);
	exit(EXIT_SUCCESS);
}

void	mrt_init(t_mrt *mrt)
{
	mrt->mlx = mlx_init();
	mrt->mlx_win = mlx_new_window(mrt->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	mrt->img.img = mlx_new_image(mrt->mlx, WIN_WIDTH, WIN_HEIGHT);
	mrt->img.addr = mlx_get_data_addr(mrt->img.img, &mrt->img.bits_per_pixel,
			&mrt->img.line_length, &mrt->img.endian);
	if (!mrt->img.img)
		mrt_clear(mrt);
	hook_init(mrt);
}
