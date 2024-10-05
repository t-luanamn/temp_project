/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sp_pl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:01:59 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/05 21:02:01 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

int	intersect_sphere_solutions(float a, float b, float discriminant, float *t)
{
	float	t0;
	float	t1;

	t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t0 > 1e-6)
	{
		*t = t0;
		return (1);
	}
	if (t1 > 1e-6)
	{
		*t = t1;
		return (1);
	}
	return (0);
}

int	intersect_sphere(t_ray ray, t_sphere sphere, float *t)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = vector_subtract(ray.origin, sphere.position);
	a = vector_dot_product(ray.direction, ray.direction);
	b = 2.0 * vector_dot_product(oc, ray.direction);
	c = vector_dot_product(oc, oc) - (sphere.diameter / 2)
		* (sphere.diameter / 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	return (intersect_sphere_solutions(a, b, discriminant, t));
}

int	intersect_plane(t_ray ray, t_plane plane, float *t)
{
	float		denominator;
	t_vector	plane_to_ray_origin;

	denominator = vector_dot_product(vector_normalise(plane.normal_vec),
			ray.direction);
	if (fabs(denominator) > 1e-6)
	{
		plane_to_ray_origin = vector_subtract(plane.position, ray.origin);
		*t = vector_dot_product(plane_to_ray_origin, plane.normal_vec)
			/ denominator;
		return (*t >= 0);
	}
	return (0);
}
