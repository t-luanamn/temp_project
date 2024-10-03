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

// Function to calculate the cross product of two vectors
// t_vector	vector_cross_product(t_vector v1, t_vector v2)
// {
// 	t_vector	result;

// 	result.x = v1.y * v2.z - v1.z * v2.y;
// 	result.y = v1.z * v2.x - v1.x * v2.z;
// 	result.z = v1.x * v2.y - v1.y * v2.x;
// 	return (result);
// }

float	vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	vector_normalise(t_vector v)
{
	float		length;
	t_vector	normalised_vector;

	length = vector_length(v);
	normalised_vector.x = v.x / length;
	normalised_vector.y = v.y / length;
	normalised_vector.z = v.z / length;
	return (normalised_vector);
}
