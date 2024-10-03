#include "mrt.h"

// void set_scene(t_scene *scene)
// {
//     scene->camera.view_point = (t_vector){0, 0, -5};
//     scene->camera.orientation = (t_vector){0, 0, 1};
//     scene->camera.fov = 90;

//     scene->light.position = (t_vector){10, 10, -10};
//     scene->light.brightness = 1.0;
//     scene->light.colour = (t_colour){255, 255, 255};

//     scene->ambient.ratio = 0.1;
//     scene->ambient.colour = (t_colour){255, 255, 255};

//     scene->sphere.position = (t_vector){0, 0, 0};
//     scene->sphere.diameter = 1.0;
//     scene->sphere.colour = (t_colour){255, 0, 0};
// }

int intersect_sphere(t_ray ray, t_sphere sphere, float *t)
{
	t_vector	oc = vector_subtract(ray.origin, sphere.position);
	float	a = vector_dot_product(ray.direction, ray.direction);
	float	b = 2.0 * vector_dot_product(oc, ray.direction);
	float	c = vector_dot_product(oc, oc) - (sphere.diameter / 2) * (sphere.diameter / 2);
	float	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return 0;
	else
	{
		*t = (-b - sqrt(discriminant)) / (2.0 * a);
		return 1;
	}
}

t_colour	ray_trace(t_ray ray, t_mrt *scene)
{
    float	closest_t = INFINITY;
    t_sphere	*closest_sphere = NULL;
    float	t;

    // Iterate over all spheres to find the closest intersection
    for (int i = 0; i < scene->num_spheres; i++)
    {
        if (intersect_sphere(ray, scene->spheres[i], &t) && t < closest_t)
        {
            closest_t = t;
            closest_sphere = &scene->spheres[i];
        }
    }

    // If there is an intersection, calculate the color
    if (closest_sphere)
    {
        t_vector	hit_point = vector_add(ray.origin, vector_scale(ray.direction, closest_t));
        t_vector	normal = vector_normalise(vector_subtract(hit_point, closest_sphere->position));
        t_vector	light_dir = vector_normalise(vector_subtract(scene->light.position, hit_point));
        float	diff = fmax(0.0, vector_dot_product(normal, light_dir));
        t_colour	colour = {
            (int)(closest_sphere->colour.r * diff * scene->light.brightness),
            (int)(closest_sphere->colour.g * diff * scene->light.brightness),
            (int)(closest_sphere->colour.b * diff * scene->light.brightness)
        };
        return colour;
    }

    // Return background color if no intersection
    return (t_colour){0, 0, 0};
}

void	put_pixel(t_img *img, int x, int y, t_colour colour)
{
    char	*dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = (colour.r << 16) | (colour.g << 8) | colour.b;
}

void	mrt_render(t_mrt *mrt)
{
	printf("Rendering...\n");

	int width = W_WIDTH;
	int height = W_HEIGHT;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			float u = (float)x / (float)width;
			float v = (float)y / (float)height;
			t_ray ray;
			ray.origin = mrt->camera.view_point;
			ray.direction = vector_normalise((t_vector){u - 0.5, v - 0.5, 1});
			t_colour colour = ray_trace(ray, mrt);
			put_pixel(&mrt->mlx.img, x, y, colour);
		}
	}

	printf("Putting image to window...\n");
	mlx_put_image_to_window(mrt->mlx.ptr, mrt->mlx.win, mrt->mlx.img.img, 0, 0);
	printf("Putting image to window done\n");
}
