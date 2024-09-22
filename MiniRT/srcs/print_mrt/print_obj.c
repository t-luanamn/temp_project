/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:52:43 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 14:52:47 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

void	print_sphere(t_sphere sphere, int i)
{
	printf(CYAN"Sphere: %d\n"RST, i);
	print_vector(sphere.position);
	printf("  Diameter: %f\n", sphere.diameter);
	print_colour(sphere.colour);
}

void	print_plane(t_plane plane, int i)
{
	printf(CYAN"Plane: %d\n"RST, i);
	print_vector(plane.position);
	print_vector(plane.normal_vec);
	print_colour(plane.colour);
}

void	print_cylinder(t_cylinder cylinder, int i)
{
	printf(CYAN"Cylinder: %d\n"RST, i);
	print_vector(cylinder.position);
	print_vector(cylinder.axis);
	printf("  Diameter: %f\n", cylinder.diameter);
	printf("    Height: %f\n", cylinder.height);
	print_colour(cylinder.colour);
}
