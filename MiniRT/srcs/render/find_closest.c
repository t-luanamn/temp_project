/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:01:32 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/05 21:01:34 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

void	init_hit_data(t_hit *hit_data)
{
	hit_data->closest_t = INFINITY;
	hit_data->closest_sphere = NULL;
	hit_data->closest_plane = NULL;
	hit_data->closest_cylinder = NULL;
}

void	find_closest_objects(t_ray ray, t_mrt *scene, t_hit *hit_data)
{
	find_closest_sphere(ray, scene, &hit_data->closest_t,
		&hit_data->closest_sphere);
	find_closest_cylinder(ray, scene, &hit_data->closest_t,
		&hit_data->closest_cylinder);
	find_closest_plane(ray, scene, &hit_data->closest_t,
		&hit_data->closest_plane);
	hit_data->hit_point = calculate_hit_point(ray, hit_data->closest_t);
}

void	find_closest_sphere(t_ray ray, t_mrt *scene, float *closest_t,
	t_sphere **closest_sphere)
{
	int		i;
	float	t;

	i = 0;
	while (i < scene->num_spheres)
	{
		if (intersect_sphere(ray, scene->spheres[i], &t) && t < *closest_t)
		{
			*closest_t = t;
			*closest_sphere = &scene->spheres[i];
		}
		i++;
	}
}

void	find_closest_plane(t_ray ray, t_mrt *scene, float *closest_t,
	t_plane **closest_plane)
{
	int		i;
	float	t;

	i = 0;
	while (i < scene->num_planes)
	{
		if (intersect_plane(ray, scene->planes[i], &t) && t < *closest_t)
		{
			*closest_t = t;
			*closest_plane = &scene->planes[i];
		}
		i++;
	}
}

void	find_closest_cylinder(t_ray ray, t_mrt *scene, float *closest_t,
	t_cylinder **closest_cylinder)
{
	int		i;
	float	t;

	i = 0;
	while (i < scene->num_cylinders)
	{
		if (intersect_cylinder(ray, scene->cylinders[i], &t) && t < *closest_t)
		{
			*closest_t = t;
			*closest_cylinder = &scene->cylinders[i];
		}
		i++;
	}
}
