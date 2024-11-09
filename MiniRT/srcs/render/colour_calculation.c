/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tytang <tytang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:01:20 by tluanamn          #+#    #+#             */
/*   Updated: 2024/11/08 15:39:10 by tytang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

/*
- Ensure the shadow ray does not incorrectly identify objects
- Check if the shadow ray is correctly oriented
	with respect to the surface normal
*/
void	apply_shadow(t_mrt *scene, t_hit *hit_data, t_ray light_ray,
	t_colour *colour)
{
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	t_vector	normal;
	float		light_distance;

	init_hit_data(&shadow_hit);
	shadow_ray.origin = vector_add(hit_data->hit_point,
			vector_scale(light_ray.direction, 0.001f));
	shadow_ray.direction = light_ray.direction;
	find_closest_objects(shadow_ray, scene, &shadow_hit);
	light_distance = vector_length(vector_subtract(
				scene->light.position, hit_data->hit_point));
	if (shadow_hit.closest_t < light_distance && shadow_hit.closest_t > 0.001f)
	{
		normal = normalise(hit_data->hit_point);
		if (vector_dot(normal, light_ray.direction) < 0)
		{
			colour->r *= 0.5;
			colour->g *= 0.5;
			colour->b *= 0.5;
		}
	}
}

t_colour	calculate_sphere_colour(t_mrt *scene, t_hit *hit_data,
	t_vector light_dir, t_vector view_dir)
{
	t_colour	colour;
	t_vector	normal;
	float		diffuse;
	float		specular;

	normal = calculate_normal_sphere(
			hit_data->hit_point, hit_data->closest_sphere);
	diffuse = calculate_diffuse(
			fmax(0.1, vector_dot(normal, light_dir)), scene);
	specular = calculate_specular(light_dir, view_dir, normal, scene);
	colour = blend(diffuse, specular, hit_data->closest_sphere->colour);
	return (colour);
}

t_colour	calculate_plane_colour(t_mrt *scene, t_hit *hit_data,
	t_vector light_dir, t_vector view_dir)
{
	t_colour	colour;
	t_vector	normal;
	float		diffuse;
	float		specular;

	normal = calculate_normal_plane(hit_data->closest_plane);
	diffuse = calculate_diffuse(
			fmax(0.125, vector_dot(normal, light_dir)), scene);
	specular = calculate_specular(light_dir, view_dir, normal, scene);
	colour = blend(diffuse, specular, hit_data->closest_plane->colour);
	return (colour);
}

t_colour	calculate_cylinder_colour(t_mrt *scene, t_hit *hit_data,
	t_vector light_dir, t_vector view_dir)
{
	t_colour	colour;
	t_vector	normal;
	float		diffuse;
	float		specular;

	normal = calculate_normal_cylinder(
			hit_data->hit_point, hit_data->closest_cylinder);
	diffuse = calculate_diffuse(
			fmax(0.125, vector_dot(normal, light_dir)), scene);
	specular = calculate_specular(light_dir, view_dir, normal, scene);
	colour = blend(diffuse, specular, hit_data->closest_cylinder->colour);
	return (colour);
}

t_colour	calculate_hit_colour(t_mrt *scene, t_hit *hit_data,
	t_vector light_dir)
{
	t_colour	colour;
	t_vector	view_dir;

	view_dir = normalise(vector_subtract(
				scene->camera.view_point, hit_data->hit_point));
	if (hit_data->closest_obj == OBJECT_SPHERE)
		colour = calculate_sphere_colour(scene, hit_data, light_dir, view_dir);
	else if (hit_data->closest_obj == OBJECT_PLANE)
		colour = calculate_plane_colour(scene, hit_data, light_dir, view_dir);
	else if (hit_data->closest_obj == OBJECT_CYLINDER)
		colour = calculate_cylinder_colour(
				scene, hit_data, light_dir, view_dir);
	else
		return ((t_colour){0, 0, 0});
	apply_shadow(
		scene, hit_data, (t_ray){hit_data->hit_point, light_dir}, &colour);
	add_ambient_light(scene, &colour);
	return (colour);
}
