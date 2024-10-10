/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:58:43 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/05 14:58:45 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

// https://www.geeksforgeeks.org/vector-operations/
/*
Function to add two vectors
Calculating Positions: Finding the resultant position
when moving from one point to another.
Computer Graphics: Calculating the position of objects in a scene.
*/
t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

/*
Function operation that subtracts one vector from another
Calculating Displacement: Finding the displacement vector between two points.
Ray Tracing: Calculating the vector from the ray's origin to
the intersection point.
*/
t_vector	vector_subtract(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

// Function to multiply a vector by a scalar
t_vector	vector_scale(t_vector v, float scalar)
{
	t_vector	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

/*
Function to calculate the dot product of two vectors
Angle Between Vectors: Used to find the angle between two vectors.
If the dot product is zero, the vectors are orthogonal (perpendicular).

Projection: The dot product is used to project one vector onto another.

Determining Parallelism: If the dot product of two vectors is equal to the
product of their magnitudes, the vectors are parallel.
*/
float	vector_dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
The vector_normalise function normalises a given vector.
Normalising a vectormeans scaling it to have a length (or magnitude) of 1
while maintaining its direction. This is useful in many applications,
such as computer graphics, where unit vectors are often required.
*/
t_vector	vector_normalise(t_vector v)
{
	float		length;
	t_vector	normalised_vector;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	normalised_vector.x = v.x / length;
	normalised_vector.y = v.y / length;
	normalised_vector.z = v.z / length;
	return (normalised_vector);
}
