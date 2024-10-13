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
Angle Between Vectors: Used to find the angle between two vectors.
If the dot product is zero, the vectors are orthogonal (perpendicular).

Projection: The dot product is used to project one vector onto another.

Determining Parallelism: If the dot product of two vectors is equal to the
product of their magnitudes, the vectors are parallel.
*/
float	vector_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
The cross product of two vectors results in a third vector that is perpendicular
to the plane formed by the original two vectors.

Calculating Normals: calculate the normal vector to a surface.
This is essential for determining how light interacts with the surface.

Camera Orientation: The cross product helps in defining the right and up
vectors of the camera's coordinate system, ensuring the camera is correctly
oriented in 3D space.

Reflection and Refraction: In advanced ray tracing, the cross product can be
used to calculate reflection and refraction directions based on the surface
normal and the incoming ray direction.
*/
t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
