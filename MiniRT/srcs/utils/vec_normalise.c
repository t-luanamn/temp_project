/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:58:43 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/05 14:58:45 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

float	vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
The normalise function normalises a given vector.
Normalising a vectormeans scaling it to have a length (or magnitude) of 1
while maintaining its direction. This is useful in many applications,
such as computer graphics, where unit vectors are often required.
*/
t_vector	normalise(t_vector v)
{
	float		length;
	t_vector	normalised_vector;

	length = vector_length(v);
	normalised_vector.x = v.x / length;
	normalised_vector.y = v.y / length;
	normalised_vector.z = v.z / length;
	return (normalised_vector);
}
