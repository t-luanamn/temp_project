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
// Function to add two vectors
t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

// Function to subtract two vectors
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

// Function to calculate the dot product of two vectors
float	vector_dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

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
