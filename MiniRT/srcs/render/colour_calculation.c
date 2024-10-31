/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:01:20 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/05 21:01:22 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

t_colour	calculate_hit_colour(t_mrt *scene, t_hit *hit_data,
	t_vector light_dir)
{
	if (hit_data->closest_sphere)
		return (calculate_sphere_colour(scene, hit_data, light_dir));
	if (hit_data->closest_plane)
		return (calculate_plane_colour(scene, hit_data, light_dir));
	if (hit_data->closest_cylinder)
		return (calculate_cylinder_colour(scene, hit_data, light_dir));
	return ((t_colour){0, 0, 0});
}

void apply_shadow(t_mrt *scene, t_hit *hit_data, t_ray light_ray, t_colour *colour)
{
    t_ray shadow_ray;
    t_hit shadow_hit;

    init_hit_data(&shadow_hit);
    shadow_ray.origin = vector_add(hit_data->hit_point, vector_scale(light_ray.direction, 0.0001f));
    shadow_ray.direction = light_ray.direction;

    find_closest_objects(shadow_ray, scene, &shadow_hit);
    if (shadow_hit.closest_t < vector_length(vector_subtract(scene->light.position, hit_data->hit_point)))
	{
		colour->r *= 0.5;
		colour->g *= 0.5;
		colour->b *= 0.5;
    }
}

void add_ambient_light(t_mrt *scene, t_colour *colour)
{
    colour->r = fmin(255, fmax(0, (int)(colour->r + (scene->ambient.colour.r + 10) * scene->ambient.ratio * 0.5)));
    colour->g = fmin(255, fmax(0, (int)(colour->g + (scene->ambient.colour.g + 10) * scene->ambient.ratio * 0.5)));
    colour->b = fmin(255, fmax(0, (int)(colour->b + (scene->ambient.colour.b + 10) * scene->ambient.ratio * 0.5)));
}

t_colour calculate_sphere_colour(t_mrt *scene, t_hit *hit_data, t_vector light_dir)
{
    t_vector normal;
    t_colour colour;
    float diff;
	t_ray light_ray;

    normal = calculate_normal_sphere(hit_data->hit_point, hit_data->closest_sphere);
	light_ray.origin = normal;
	light_ray.direction = light_dir;
    diff = fmax(0.01, vector_dot(normal, light_dir));
    colour = calculate_diffuse(hit_data->closest_sphere->colour, diff, scene);

    apply_shadow(scene, hit_data, light_ray, &colour);
    add_ambient_light(scene, &colour);

    return colour;
}

t_colour calculate_plane_colour(t_mrt *scene, t_hit *hit_data, t_vector light_dir)
{
    t_vector normal;
    t_colour colour;
    float diff;
	t_ray light_ray;

    normal = calculate_normal_plane(hit_data->closest_plane);
	light_ray.origin = normal;
	light_ray.direction = light_dir;
    diff = fmax(0.1, vector_dot(normal, light_dir));
    colour = calculate_diffuse(hit_data->closest_plane->colour, diff, scene);

    apply_shadow(scene, hit_data, light_ray, &colour);
    add_ambient_light(scene, &colour);

    return colour;
}

t_colour calculate_cylinder_colour(t_mrt *scene, t_hit *hit_data, t_vector light_dir)
{
    t_vector normal;
    t_colour colour;
    float diff;
	t_ray light_ray;

    normal = calculate_normal_cylinder(hit_data->hit_point, hit_data->closest_cylinder);
	light_ray.origin = normal;
	light_ray.direction = light_dir;
    diff = fmax(0.1, vector_dot(normal, light_dir));
    colour = calculate_diffuse(hit_data->closest_cylinder->colour, diff, scene);

    apply_shadow(scene, hit_data, light_ray, &colour);
    add_ambient_light(scene, &colour);

    return colour;
}
