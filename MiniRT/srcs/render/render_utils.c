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

t_colour	calculate_diffuse(t_colour obj_colour, float diff, t_mrt *scene)
{
	t_colour	diffuse_colour;

	diffuse_colour.r = fmin(255, fmax(0, (int)(obj_colour.r * diff
					* scene->light.brightness + scene->ambient.colour.r
					* scene->ambient.ratio)));
	diffuse_colour.g = fmin(255, fmax(0, (int)(obj_colour.g * diff
					* scene->light.brightness + scene->ambient.colour.g
					* scene->ambient.ratio)));
	diffuse_colour.b = fmin(255, fmax(0, (int)(obj_colour.b * diff
					* scene->light.brightness + scene->ambient.colour.b
					* scene->ambient.ratio)));
	return (diffuse_colour);
}
