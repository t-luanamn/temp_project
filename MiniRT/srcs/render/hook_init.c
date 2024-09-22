#include "mrt.h"

int	close_handler(t_mrt *mrt)
{
	mlx_destroy_image(mrt->mlx,
		mrt->img.addr);
	mlx_clear_window(mrt->mlx,
		mrt->mlx_win);
	mlx_destroy_window(mrt->mlx,
		mrt->mlx_win);
	mrt_clear(mrt);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keysym, t_mrt *mrt)
{
	if (keysym == ESC_KEY)
		close_handler(mrt);
	mrt_render(mrt);
	return (0);
}

static int	handle_no_event(t_mrt *mrt)
{
	(void) mrt;
	return (0);
}

void	hook_init(t_mrt *mrt)
{
	mlx_loop_hook(mrt->mlx, handle_no_event, mrt);
	mlx_hook(mrt->mlx_win, 2, 0, key_hook, mrt);
	mlx_hook(mrt->mlx_win, 17, 0, close_handler, mrt);
	mlx_loop(mrt->mlx);
}
