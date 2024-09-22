/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:45:35 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 15:45:37 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

bool	parse_sphere(t_mrt *mrt, char *line)
{
	char		**data;
	t_sphere	sphere;
	int			i;

	data = ft_split(line, ' ');
	if (count_parameters(data) != PARAMS_SPHERE)
		return (parsing_error("Invalid number of parameters", data), false);
	ft_bzero(&sphere, sizeof(t_sphere));
	i = 0;
	while (data && data[++i])
	{
		if (i == 1 && !parse_vector(data[i], &sphere.position, false))
			return (parsing_error("Invalid sphere position", data));
		if (i == 2 && !parse_float(data[i], &sphere.diameter, 0.0, FLT_MAX))
			return (parsing_error("Invalid sphere diameter", data));
		if (i == 3 && !parse_colour(data[i], &sphere.colour))
			return (parsing_error("Invalid sphere colour", data));
	}
	if (!add_sphere(mrt, sphere))
		return (free_array(data), false);
	free_array(data);
	return (true);
}

bool	parse_plane(t_mrt *mrt, char *line)
{
	char	**data;
	t_plane	plane;
	int		i;

	data = ft_split(line, ' ');
	if (count_parameters(data) != PARAMS_PLANE)
		return (parsing_error("Invalid number of parameters", data), false);
	ft_bzero(&plane, sizeof(t_plane));
	i = 0;
	while (data && data[++i])
	{
		if (i == 1 && !parse_vector(data[i], &plane.position, false))
			return (parsing_error("Invalid plane position", data));
		if (i == 2 && !parse_vector(data[i], &plane.normal_vec, true))
			return (parsing_error("Invalid plane normal vector", data));
		if (i == 3 && !parse_colour(data[i], &plane.colour))
			return (parsing_error("Invalid plane colour", data));
	}
	if (!add_plane(mrt, plane))
		return (free_array(data), false);
	free_array(data);
	return (true);
}

static bool	parse_cylinder_parameters(char **data, t_cylinder *cylinder)
{
	int	i;

	i = 0;
	while (data && data[++i])
	{
		if (i == 1 && !parse_vector(data[i], &cylinder->position, false))
			return (parsing_error("Invalid cylinder position", data));
		if (i == 2 && !parse_vector(data[i], &cylinder->axis, true))
			return (parsing_error("Invalid cylinder axis vector", data));
		if (i == 3 && !parse_float(data[i], &cylinder->diameter, 0.0, FLT_MAX))
			return (parsing_error("Invalid cylinder diameter", data));
		if (i == 4 && !parse_float(data[i], &cylinder->height, 0.0, FLT_MAX))
			return (parsing_error("Invalid cylinder height", data));
		if (i == 5 && !parse_colour(data[i], &cylinder->colour))
			return (parsing_error("Invalid cylinder colour", data));
	}
	return (true);
}

bool	parse_cylinder(t_mrt *mrt, char *line)
{
	char		**data;
	t_cylinder	cylinder;

	data = ft_split(line, ' ');
	if (count_parameters(data) != PARAMS_CYLINDER)
		return (parsing_error("Invalid number of parameters", data), false);
	ft_bzero(&cylinder, sizeof(t_cylinder));
	if (!parse_cylinder_parameters(data, &cylinder))
		return (free_array(data), false);
	if (!add_cylinder(mrt, cylinder))
		return (free_array(data), false);
	free_array(data);
	return (true);
}
