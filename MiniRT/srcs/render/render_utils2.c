/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:06:55 by tluanamn          #+#    #+#             */
/*   Updated: 2024/11/04 13:06:56 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

float	calculate_diffuse(float diff, t_mrt *scene)
{
	float	diffuse;

	diffuse = (diff) * scene->light.brightness;
	return (diffuse);
}

void	add_ambient_light(t_mrt *scene, t_colour *colour)
{
	colour->r = fmin(255, fmax(0, (int)(colour->r
					+ (scene->ambient.colour.r) * scene->ambient.ratio)));
	colour->g = fmin(255, fmax(0, (int)(colour->g
					+ (scene->ambient.colour.g) * scene->ambient.ratio)));
	colour->b = fmin(255, fmax(0, (int)(colour->b
					+ (scene->ambient.colour.b) * scene->ambient.ratio)));
}

float	calculate_specular(t_vector light_dir, t_vector view_dir,
	t_vector normal, t_mrt *scene)
{
	float		specular;
	float		specular_strength;
	t_vector	reflect_dir;
	float		spec;

	specular_strength = 0.5;
	reflect_dir = normalise(vector_subtract(vector_scale(
					normal, 2 * vector_dot(normal, light_dir)), light_dir));
	spec = pow(fmax(vector_dot(view_dir, reflect_dir), 0.001), 16);
	specular = specular_strength * spec * scene->light.brightness;
	return (specular);
}

t_colour	blend(float diffuse, float specular, t_colour obj_colour)
{
	t_colour	result;

	result.r = fmin(255, fmax(0, obj_colour.r * (diffuse + specular)));
	result.g = fmin(255, fmax(0, obj_colour.g * (diffuse + specular)));
	result.b = fmin(255, fmax(0, obj_colour.b * (diffuse + specular)));
	return (result);
}
