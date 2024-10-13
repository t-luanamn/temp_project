/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:36:04 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/14 08:36:06 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

t_vector	calculate_world_up(t_vector forward)
{
	if (fabs(forward.y) > 0.999f)
		return ((t_vector){0, 0, 1});
	else
		return ((t_vector){0, 1, 0});
}

void	calculate_camera_basis(t_vector forward, t_camera_basis *basis)
{
	t_vector	world_up;

	world_up = calculate_world_up(forward);
	basis->right = vector_cross(forward, world_up);
	basis->right = vector_normalise(basis->right);
	basis->up = vector_cross(basis->right, forward);
	basis->forward = forward;
}

t_ray	generate_ray(t_mrt *mrt, int x, int y, t_camera_basis basis)
{
	t_ray	ray;
	float	u;
	float	v;

	u = -(2.0f * ((float)x + 0.5f) / (float)W_WIDTH - 1.0f)
		* mrt->camera.aspect_ratio * mrt->camera.scale;
	v = (1.0f - 2.0f * ((float)y + 0.5f) / (float)W_HEIGHT) * mrt->camera.scale;
	ray.origin = mrt->camera.view_point;
	ray.direction = vector_normalise(vector_add(
				vector_add(vector_scale(basis.right, u),
					vector_scale(basis.up, v)),
				basis.forward));
	return (ray);
}
