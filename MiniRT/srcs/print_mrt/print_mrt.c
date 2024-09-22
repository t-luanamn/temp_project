/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:52:33 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 14:52:34 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

void	print_vector(t_vector vec)
{
	printf("    Vector: x = %f, y = %f, z = %f\n", vec.x, vec.y, vec.z);
}

void	print_colour(t_colour col)
{
	printf("    Colour: r = %d, g = %d, b = %d\n", col.r, col.g, col.b);
}

void	print_mrt(t_mrt *mrt)
{
	int	i;

	printf(CYAN"\n=== MRT Content ===\n\n"RST);
	print_ambient(mrt->ambient);
	print_camera(mrt->camera);
	print_light(mrt->light);
	i = 0;
	while (i < mrt->num_spheres)
	{
		print_sphere(mrt->spheres[i], i);
		i++;
	}
	i = 0;
	while (i < mrt->num_planes)
	{
		print_plane(mrt->planes[i], i);
		i++;
	}
	i = 0;
	while (i < mrt->num_cylinders)
	{
		print_cylinder(mrt->cylinders[i], i);
		i++;
	}
}
