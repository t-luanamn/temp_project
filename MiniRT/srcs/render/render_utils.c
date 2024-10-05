/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:01:10 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/05 21:01:11 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

t_vector	calculate_hit_point(t_ray ray, float t)
{
	t_vector	result;

	result = vector_add(ray.origin, vector_scale(ray.direction, t));
	return (result);
}

t_vector	calculate_normal_sphere(t_vector hit_point, t_sphere *sphere)
{
	t_vector	result;

	result = vector_normalise(vector_subtract(hit_point, sphere->position));
	return (result);
}

t_vector	calculate_normal_plane(t_plane *plane)
{
	t_vector	result;

	result = vector_normalise(plane->normal_vec);
	return (result);
}

// t_vector	calculate_normal_cylinder(t_vector hit_point, t_cylinder *cylinder)
// {
// 	t_vector	axis;
// 	t_vector	base_to_hit;
// 	t_vector	hit_base_proj;
// 	t_vector	result;

// 	axis = vector_normalise(cylinder->axis);
// 	base_to_hit = vector_subtract(hit_point, cylinder->position);
// 	hit_base_proj = vector_scale(axis, vector_dot_product(base_to_hit, axis));
// 	result = vector_normalise(vector_subtract(hit_point,
// 				vector_add(cylinder->position, hit_base_proj)));
// 	return (result);
// }
t_vector	calculate_normal_cylinder(t_vector hit_point, t_cylinder *cylinder)
{
	t_vector	to_hit;
	t_vector	axis_normal;
	t_vector	normal;

	// Vector from cylinder base to hit point
	to_hit = vector_subtract(hit_point, cylinder->position);

	// Project to_hit vector onto the cylinder axis to get the normal on the side surface
	axis_normal = vector_scale(cylinder->axis, vector_dot_product(to_hit, cylinder->axis));

	// Subtract axis_normal from to_hit to get the correct surface normal
	normal = vector_subtract(to_hit, axis_normal);

	return (vector_normalise(normal));
}

int	calculate_diffuse(int object_colour, float diff, t_mrt *scene)
{
	return (fmin(255, fmax(0, (int)(object_colour * diff
				* scene->light.brightness
				+ scene->ambient.colour.r
				* scene->ambient.ratio))));
}
