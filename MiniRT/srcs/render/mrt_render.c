#include "mrt.h"

# define WHITE				0xFFFFFF

static void	put_pixel(int x, int y, t_img *img, int color)
{
    int	offset;

    offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
    *(unsigned int *)(img->addr + offset) = color;
}

static void	handle_pixel(int x, int y, t_window *my_mlx)
{
    put_pixel(x, y, &my_mlx->img, WHITE);
}

void	fractol_render(t_window *my_mlx)
{
    int	x;
    int	y;

    y = -1;
    while (++y < W_HEIGHT)
    {
        x = -1;
        while (++x < W_WIDTH)
        {
            handle_pixel(x, y, my_mlx);
        }
    }
}

void	mrt_render(t_mrt *mrt)
{
	printf("Rendering...\n");
	//make objects
	fractol_render(&mrt->mlx);
	printf("Putting image to window...\n");
	mlx_put_image_to_window(mrt->mlx.ptr, mrt->mlx.win, mrt->mlx.img.img, 0, 0);
	printf("Putting image to window done\n");
}
