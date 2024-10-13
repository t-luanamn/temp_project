/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:01:51 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/05 21:01:53 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

// Checks if the intersection point lies within the height of the cylinder.
int	check_cylinder_height(float height, float cy_height, float t_val, float *t)
{
	if (height >= -1e-6 && height <= cy_height + 1e-6)
	{
		*t = t_val;
		return (1);
	}
	return (0);
}

int	intersect_cylinder_solutions(t_ray ray, t_cylinder cylinder,
		float *t_vals, float *t)
{
	t_vector	hit_point[2];
	t_vector	base_to_hit[2];
	float		height[2];

	hit_point[0] = calculate_hit_point(ray, t_vals[0]);
	hit_point[1] = calculate_hit_point(ray, t_vals[1]);
	base_to_hit[0] = vector_subtract(hit_point[0], cylinder.position);
	base_to_hit[1] = vector_subtract(hit_point[1], cylinder.position);
	height[0] = vector_dot(
			base_to_hit[0], vector_normalise(cylinder.axis));
	height[1] = vector_dot(
			base_to_hit[1], vector_normalise(cylinder.axis));
	if (check_cylinder_height(height[0], cylinder.height, t_vals[0], t))
		return (1);
	if (check_cylinder_height(height[1], cylinder.height, t_vals[1], t))
		return (1);
	return (0);
}

void	compute_ray_cylinder_vectors(t_ray ray, t_cylinder cylinder,
			t_vector *d, t_vector *o)
{
	t_vector	axis;
	t_vector	oc;

	oc = vector_subtract(ray.origin, cylinder.position);
	axis = vector_normalise(cylinder.axis);
	*d = vector_subtract(ray.direction, vector_scale(axis,
				vector_dot(ray.direction, axis)));
	*o = vector_subtract(oc, vector_scale(axis, vector_dot(oc, axis)));
}

void	compute_t_values(float *abc, float discriminant, float *t_vals)
{
	t_vals[0] = (-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]);
	t_vals[1] = (-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]);
}

/*
intersect_cylinder_solutions:
This function calculates the hit points for the potential t values and checks
if these points lie within the cylinder's height using the
check_cylinder_height function.

compute_ray_cylinder_vectors:
This function computes the vectors *d* and *o* which are used to form the
quadratic equation. The vector *d* is the direction of the ray projected
onto the plane perpendicular to the cylinder's axis. The vector *o* is the
origin of the ray projected onto the same plane.

The dot product of a vector with itself is used to calculate the magnitude
squared of that vector.
abc[0] = vector_dot(d, d) -> calculates the coefficient ( a )
for the quadratic equation, which is the magnitude squared of
the direction vector ( d ).

compute_t_values:
This function uses the quadratic formula to compute the potential t values for
the intersections. Discriminant is used to determine if real solutions exist.

intersect_cylinder:
This is the main function that integrates all the above functions to determine
if a ray intersects with a cylinder. It first computes the necessary vectors
and coefficients, checks the discriminant, computes the potential t values,
and finally checks if these values correspond to valid intersection points
within the cylinder's height.
*/
int	intersect_cylinder(t_ray ray, t_cylinder cylinder, float *t)
{
	t_vector	d;
	t_vector	o;
	float		abc[3];
	float		discriminant;
	float		t_vals[2];

	compute_ray_cylinder_vectors(ray, cylinder, &d, &o);
	abc[0] = vector_dot(d, d);
	abc[1] = 2.0 * vector_dot(d, o);
	abc[2] = vector_dot(o, o) - pow(cylinder.diameter / 2, 2);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (0);
	compute_t_values(abc, discriminant, t_vals);
	if (intersect_cylinder_solutions(ray, cylinder, t_vals, t))
		return (1);
	return (0);
}
