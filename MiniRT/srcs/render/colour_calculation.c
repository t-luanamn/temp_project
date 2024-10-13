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
	return (calculate_ambient_colour(scene));
}

t_colour	calculate_sphere_colour(t_mrt *scene, t_hit *hit_data,
	t_vector light_dir)
{
	t_vector	normal;
	t_colour	colour;
	float		diff;

	normal = calculate_normal_sphere(hit_data->hit_point,
			hit_data->closest_sphere);
	diff = fmax(0.0, vector_dot(normal, light_dir));
	colour = calculate_diffuse(hit_data->closest_sphere->colour, diff, scene);
	return (colour);
}

t_colour	calculate_plane_colour(t_mrt *scene, t_hit *hit_data,
	t_vector light_dir)
{
	t_vector	normal;
	t_colour	colour;
	float		diff;

	normal = calculate_normal_plane(hit_data->closest_plane);
	diff = fmax(0.0, vector_dot(normal, light_dir));
	colour = calculate_diffuse(hit_data->closest_plane->colour, diff, scene);
	return (colour);
}

t_colour	calculate_cylinder_colour(t_mrt *scene, t_hit *hit_data,
	t_vector light_dir)
{
	t_vector	normal;
	t_colour	colour;
	float		diff;

	normal = calculate_normal_cylinder(hit_data->hit_point,
			hit_data->closest_cylinder);
	diff = fmax(0.0, vector_dot(normal, light_dir));
	colour = calculate_diffuse(hit_data->closest_cylinder->colour,
			diff, scene);
	return (colour);
}

t_colour	calculate_ambient_colour(t_mrt *scene)
{
	t_colour	colour;

	colour.r = fmin(255, fmax(0, (int)(scene->ambient.colour.r
					* scene->ambient.ratio)));
	colour.g = fmin(255, fmax(0, (int)(scene->ambient.colour.g
					* scene->ambient.ratio)));
	colour.b = fmin(255, fmax(0, (int)(scene->ambient.colour.b
					* scene->ambient.ratio)));
	return (colour);
}
