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

/*
- Calculate the two possible solutions for t
- Check if the first solution is valid (greater than a small epsilon)
*/
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

/*
Vector Calculation:
oc is the vector from the ray's origin to the sphere's center.
a, b, and c are coefficients for the quadratic equation derived
from the ray-sphere intersection formula.

Quadratic Equation:
The quadratic equation is derived from the geometric equation of a sphere
and the parametric equation of a ray.
The discriminant (b^2 - 4ac) determines the nature of the intersection:
If the discriminant is negative, there are no real roots,
meaning the ray does not intersect the sphere.
If the discriminant is zero or positive, there are one or two real roots,
indicating potential intersection points.

Intersection Points:
The function intersect_sphere_solutions calculates the potential intersection
points (t0 and t1).
It checks if these points are valid (greater than a small epsilon to avoid
floating-point precision issues).

Return Value:
The function returns 1 if there is a valid intersection and 0 otherwise.
The intersection point is stored in the variable pointed to by t.
*/
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

/*
the quadratic equation for the intersection of a ray with a cylinder can be
derived from the geometric properties of the cylinder and the ray.
[ at^2 + bt + c = 0 ]
Where:
(a),(b),and(c) are coefficients that depend on the ray and cylinder parameters.
( t ) is the parameter along the ray direction.

Parallel Check:
The function checks if the absolute value of the denominator is greater than
a small epsilon value (1e-6). This check ensures that the ray is not parallel
to the plane. If the ray is parallel, the function returns 0, no intersection.

Vector Calculation:
If the ray is not parallel, the function calculates the vector from the
plane's position to the ray's origin.

Intersection Point Calculation:
The intersection point t is calculated using the plane equation.
The dot product of plane_to_ray_origin and the plane's normal vector
is divided by the denominator.

Intersection Validity:
The function checks if the calculated intersection point t is greater than
or equal to 0. If it is, the function returns 1 indicating a valid intersection
in front of the ray's origin. Otherwise, it returns 0.

Return Value:
The function returns 1 if there is a valid intersection and 0 otherwise.
The intersection point is stored in the variable pointed to by t.
*/
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
