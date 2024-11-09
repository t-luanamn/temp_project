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
	hit_data->closest_obj = OBJECT_NONE;
}

void	find_closest_sphere(t_ray ray, t_mrt *scene, t_hit *hit_data)
{
	int		i;
	float	t;

	i = 0;
	while (i < scene->num_spheres)
	{
		if (intersect_sphere(ray, scene->spheres[i], &t)
			&& t < hit_data->closest_t)
		{
			hit_data->closest_t = t;
			hit_data->closest_sphere = &scene->spheres[i];
			hit_data->closest_obj = OBJECT_SPHERE;
		}
		i++;
	}
}

void	find_closest_plane(t_ray ray, t_mrt *scene, t_hit *hit_data)
{
	int		i;
	float	t;

	i = 0;
	while (i < scene->num_planes)
	{
		if (intersect_plane(ray, scene->planes[i], &t)
			&& t < hit_data->closest_t)
		{
			hit_data->closest_t = t;
			hit_data->closest_plane = &scene->planes[i];
			hit_data->closest_obj = OBJECT_PLANE;
		}
		i++;
	}
}

void	find_closest_cylinder(t_ray ray, t_mrt *scene, t_hit *hit_data)
{
	int		i;
	float	t;

	i = 0;
	while (i < scene->num_cylinders)
	{
		if (intersect_cylinder(ray, scene->cylinders[i], &t)
			&& t < hit_data->closest_t)
		{
			hit_data->closest_t = t;
			hit_data->closest_cylinder = &scene->cylinders[i];
			hit_data->closest_obj = OBJECT_CYLINDER;
		}
		i++;
	}
}

/*
The find_closest_objects function iterates through all objects in the scene
(spheres, cylinders, and planes) to find the closest intersection point with
a given ray. It updates the hit_data structure with information about the
closest object and calculates the hit point.
*/
void	find_closest_objects(t_ray ray, t_mrt *scene, t_hit *hit_data)
{
	find_closest_cylinder(ray, scene, hit_data);
	find_closest_plane(ray, scene, hit_data);
	find_closest_sphere(ray, scene, hit_data);
	hit_data->hit_point = calculate_hit_point(ray, hit_data->closest_t);
}
