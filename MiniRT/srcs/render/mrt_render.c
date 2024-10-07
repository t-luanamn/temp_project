/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:57:57 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/05 14:57:59 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

t_colour	ray_trace(t_ray ray, t_mrt *scene)
{
	t_hit		hit_data;
	t_vector	light_dir;
	t_colour	colour;

	init_hit_data(&hit_data);
	find_closest_objects(ray, scene, &hit_data);
	light_dir = vector_normalise(vector_subtract(
				scene->light.position, hit_data.hit_point));
	colour = calculate_hit_colour(scene, &hit_data, light_dir);
	return (colour);
}

void	put_pixel(t_img *img, int x, int y, t_colour colour)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = (colour.r << 16) | (colour.g << 8) | colour.b;
}

void	render_pixel(t_mrt *mrt, int x, int y, float aspect_ratio)
{
	t_ray		ray;
	t_colour	colour;
	float		u;
	float		v;
	float		fov_scale;

	fov_scale = tan(mrt->camera.fov * 0.5 * M_PI / 180.0);
	u = (float)x / (float)W_WIDTH;
	v = (float)(W_HEIGHT - y) / (float)W_HEIGHT;
	ray.origin = mrt->camera.view_point;
	ray.direction = vector_normalise((t_vector){
			(u - 0.5) * aspect_ratio * fov_scale,
			(v - 0.5) * fov_scale, 1});
	colour = ray_trace(ray, mrt);
	put_pixel(&mrt->mlx.img, x, y, colour);
}

void	mrt_render(t_mrt *mrt)
{
	int		x;
	int		y;
	float	aspect_ratio;

	printf("Rendering...\n");
	aspect_ratio = (float)W_WIDTH / (float)W_HEIGHT;
	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			render_pixel(mrt, x, y, aspect_ratio);
			x++;
		}
		y++;
	}
	printf("Putting image to window...\n");
	mlx_put_image_to_window(mrt->mlx.ptr, mrt->mlx.win, mrt->mlx.img.img, 0, 0);
	printf("Putting image to window done\n");
}
