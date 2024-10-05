/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:45:26 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 15:45:28 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

bool	add_sphere(t_mrt *mrt, t_sphere sphere)
{
	t_sphere	*sp;

	sp = ft_realloc(mrt->spheres, sizeof(t_sphere) * (mrt->num_spheres + 1));
	if (!sp)
		return (print_error("Sphere: Memory allocation failed"), false);
	mrt->spheres = sp;
	mrt->spheres[mrt->num_spheres] = sphere;
	mrt->num_spheres += 1;
	return (true);
}

bool	add_plane(t_mrt *mrt, t_plane plane)
{
	t_plane	*pl;

	pl = ft_realloc(mrt->planes, sizeof(t_plane) * (mrt->num_planes + 1));
	if (!pl)
		return (print_error("Plane: Memory allocation failed"), false);
	mrt->planes = pl;
	mrt->planes[mrt->num_planes] = plane;
	mrt->num_planes += 1;
	return (true);
}

bool	add_cylinder(t_mrt *mrt, t_cylinder cylinder)
{
	t_cylinder	*cy;

	cy = ft_realloc(mrt->cylinders,
			sizeof(t_cylinder) * (mrt->num_cylinders + 1));
	if (!cy)
		return (print_error("Memory allocation failed"), false);
	mrt->cylinders = cy;
	mrt->cylinders[mrt->num_cylinders] = cylinder;
	mrt->num_cylinders += 1;
	return (true);
}
