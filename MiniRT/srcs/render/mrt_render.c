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

/*
Calculate the Memory Address of the Pixel:
img->addr is the base address of the image's pixel data.
y * img->line_length calculates the offset to the start of the row.
x * (img->bits_per_pixel / 8) calculates the offset to the specific pixel
	within the row.
Adding these offsets to img->addr gives the address of the pixel (dst).

Set the Pixel Color:
The color is set by combining the red, green, and blue components.
(colour.r << 16) shifts the red component to the highest byte.
(colour.g << 8) shifts the green component to the middle byte.
colour.b remains in the lowest byte.
The combined value is then stored at the calculated address (dst).

Example:
Assume:
img->addr points to the start of the pixel data.
img->line_length is 800 bytes
(for an image width of 200 pixels and 32 bits per pixel).
img->bits_per_pixel is 32 (4 bytes per pixel).
To set the pixel at coordinates (10, 20) 
to a color with RGB values (255, 0, 0) (red):

Calculate the address:
y * img->line_length = 20 * 800 = 16000
x * (img->bits_per_pixel / 8) = 10 * 4 = 40
dst = img->addr + 16000 + 40 = img->addr + 16040

Set the color:
colour.r = 255, colour.g = 0, colour.b = 0
Combined color value: (255 << 16) | (0 << 8) | 0 = 0xFF0000
Store 0xFF0000 at img->addr + 16040.
*/
void	put_pixel(t_img *img, int x, int y, t_colour colour)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = (colour.r << 16) | (colour.g << 8) | colour.b;
}

/*
** render_pixel **
function calculates the ray for each pixel, traces it through the scene,
and determines the color to be displayed

** Camera FOV**
The camera's FOV determines how wide the camera's view is. (Full angle)
	fov * M_PI / 180.0 converts the FOV from degrees to radians
	Half-Angle Calculation: * 0.5
The tangent of the half-angle is used to scale the ray directions so that
they correctly represent the camera's perspective.
The fov_scale is used to adjust the direction of the rays cast from the camera
through each pixel. It ensures that the rays spread out correctly according to
the camera's field of view.

** Ray Direction **
determines the direction in which the ray will be cast from the camera through
each pixel on the screen
- Normalized Screen Coordinates:
	u(horizontal) and v(vertical), from 0 to 1
- Offset and Scaling:
	- Offset by 0.5 to center the ray in the pixel
	(u - 0.5) and (v - 0.5) centre the coordinates around the middle of
	the screen. This shifts the range from [0, 1] to [-0.5, 0.5].
	- Scale by the aspect ratio (image does not get distorted)
	and the field of view (camera's perspective)
*/
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
