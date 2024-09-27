#include "mrt.h"

void	mrt_render(t_mrt *mrt)
{
	printf("Rendering...\n");
	mlx_put_image_to_window(mrt->mlx, mrt->mlx_win, mrt->img.img, 0, 0);
}
