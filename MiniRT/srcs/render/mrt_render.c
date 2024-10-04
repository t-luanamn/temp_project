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

int intersect_plane(t_ray ray, t_plane plane, float *t)
{
    float denom = vector_dot_product(plane.normal_vec, ray.direction);
    if (fabs(denom) > 1e-6) // Avoid division by zero
    {
        t_vector p0l0 = vector_subtract(plane.position, ray.origin);
        *t = vector_dot_product(p0l0, plane.normal_vec) / denom;
        return (*t >= 0);
    }
    return 0;
}

int intersect_cylinder(t_ray ray, t_cylinder cylinder, float *t)
{
    t_vector oc = vector_subtract(ray.origin, cylinder.position);
    t_vector axis = vector_normalise(cylinder.axis);
    t_vector d = vector_subtract(ray.direction, vector_scale(axis, vector_dot_product(ray.direction, axis)));
    t_vector o = vector_subtract(oc, vector_scale(axis, vector_dot_product(oc, axis)));
    float a = vector_dot_product(d, d);
    float b = 2.0 * vector_dot_product(d, o);
    float c = vector_dot_product(o, o) - (cylinder.diameter / 2) * (cylinder.diameter / 2);
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return 0;
    else
    {
        float t0 = (-b - sqrt(discriminant)) / (2.0 * a);
        float t1 = (-b + sqrt(discriminant)) / (2.0 * a);

        // Check if the intersection points are within the height of the cylinder
        t_vector hit_point0 = vector_add(ray.origin, vector_scale(ray.direction, t0));
        t_vector hit_point1 = vector_add(ray.origin, vector_scale(ray.direction, t1));
        t_vector base_to_hit0 = vector_subtract(hit_point0, cylinder.position);
        t_vector base_to_hit1 = vector_subtract(hit_point1, cylinder.position);

        float height0 = vector_dot_product(base_to_hit0, axis);
        float height1 = vector_dot_product(base_to_hit1, axis);

        if (height0 >= 0 && height0 <= cylinder.height)
        {
            *t = t0;
            return 1;
        }
        else if (height1 >= 0 && height1 <= cylinder.height)
        {
            *t = t1;
            return 1;
        }
    }
    return 0;
}
t_colour	ray_trace(t_ray ray, t_mrt *scene)
{
    //float	closest_t = INFINITY;
	float	closest_t = 1000;
    t_sphere	*closest_sphere = NULL;
    t_plane	*closest_plane = NULL;
    t_cylinder	*closest_cylinder = NULL;
    float	t;

    // Iterate over all spheres to find the closest intersection
    for (int i = 0; i < scene->num_spheres; i++)
    {
        if (intersect_sphere(ray, scene->spheres[i], &t) && t < closest_t)
        {
            closest_t = t;
            closest_sphere = &scene->spheres[i];
            closest_plane = NULL;
            closest_cylinder = NULL;
        }
    }

    // Iterate over all planes to find the closest intersection
    for (int i = 0; i < scene->num_planes; i++)
    {
        if (intersect_plane(ray, scene->planes[i], &t) && t < closest_t)
        {
            closest_t = t;
            closest_plane = &scene->planes[i];
            closest_sphere = NULL;
            closest_cylinder = NULL;
        }
    }

    // Iterate over all cylinders to find the closest intersection
    for (int i = 0; i < scene->num_cylinders; i++)
    {
        if (intersect_cylinder(ray, scene->cylinders[i], &t) && t < closest_t)
        {
            closest_t = t;
            closest_cylinder = &scene->cylinders[i];
            closest_sphere = NULL;
            closest_plane = NULL;
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
    else if (closest_plane)
    {
        t_vector	hit_point = vector_add(ray.origin, vector_scale(ray.direction, closest_t));
        t_vector	normal = vector_normalise(closest_plane->normal_vec);
        t_vector	light_dir = vector_normalise(vector_subtract(scene->light.position, hit_point));
        float	diff = fmax(0.0, vector_dot_product(normal, light_dir));
        t_colour	colour = {
            (int)(closest_plane->colour.r * diff * scene->light.brightness),
            (int)(closest_plane->colour.g * diff * scene->light.brightness),
            (int)(closest_plane->colour.b * diff * scene->light.brightness)
        };
        return colour;
    }
    else if (closest_cylinder)
    {
        t_vector	hit_point = vector_add(ray.origin, vector_scale(ray.direction, closest_t));
        t_vector	normal = vector_normalise(vector_subtract(hit_point, closest_cylinder->position));
        t_vector	light_dir = vector_normalise(vector_subtract(scene->light.position, hit_point));
        float	diff = fmax(0.0, vector_dot_product(normal, light_dir));
        t_colour	colour = {
            (int)(closest_cylinder->colour.r * diff * scene->light.brightness),
            (int)(closest_cylinder->colour.g * diff * scene->light.brightness),
            (int)(closest_cylinder->colour.b * diff * scene->light.brightness)
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
