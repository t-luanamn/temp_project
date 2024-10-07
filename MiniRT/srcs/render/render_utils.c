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

t_vector	calculate_normal_cylinder(t_vector hit_point, t_cylinder *cylinder)
{
	t_vector	to_hit;
	t_vector	axis_normal;
	t_vector	normal;

	to_hit = vector_subtract(hit_point, cylinder->position);
	axis_normal = vector_scale(cylinder->axis, vector_dot_product(to_hit,
				cylinder->axis));
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
