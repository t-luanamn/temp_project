/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_acl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:45:20 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 15:45:21 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

bool	parse_ambient(t_mrt *mrt, char *line)
{
	char		**data;
	t_ambient	amb;
	int			i;

	if (mrt->num_ambient > 0)
		return (print_error("Only one ambient light is allowed"), false);
	data = ft_split(line, ' ');
	if (count_parameters(data) != PARAMS_AMBIENT)
		return (parsing_error("Invalid number of parameters", data), false);
	ft_bzero(&amb, sizeof(t_ambient));
	i = 0;
	while (data && data[++i])
	{
		if (i == 1 && !parse_float(data[i], &amb.ratio, 0.0, 1.0))
			return (parsing_error("Invalid ambient light ratio", data));
		if (i == 2 && !parse_colour(data[i], &amb.colour))
			return (parsing_error("Invalid ambient light colour", data));
	}
	mrt->ambient = amb;
	mrt->num_ambient += 1;
	free_array(data);
	return (true);
}

bool	parse_camera(t_mrt *mrt, char *line)
{
	char		**data;
	t_camera	cam;
	int			i;

	if (mrt->num_camera > 0)
		return (print_error("Only one camera is allowed"), false);
	data = ft_split(line, ' ');
	if (count_parameters(data) != PARAMS_CAMERA)
		return (parsing_error("Invalid number of parameters", data), false);
	ft_bzero(&cam, sizeof(t_camera));
	i = 0;
	while (data && data[++i])
	{
		if (i == 1 && !parse_vector(data[i], &cam.view_point, false))
			return (parsing_error("Invalid camera view point", data));
		if (i == 2 && !parse_vector(data[i], &cam.orientation, true))
			return (parsing_error("Invalid camera orientation", data));
		if (i == 3 && !parse_int(data[i], &cam.fov, 0, 180))
			return (parsing_error("Invalid camera field of view", data));
	}
	mrt->camera = cam;
	mrt->num_camera += 1;
	free_array(data);
	return (true);
}

// Neet to handle when light colour is unused -> set default colour WHITE
bool	parse_light(t_mrt *mrt, char *line)
{
	char	**data;
	t_light	light;
	int		i;

	if (mrt->num_lights > 0)
		return (print_error("Only one light is allowed"), false);
	data = ft_split(line, ' ');
	if (count_parameters(data) != PARAMS_LIGHT) // Check when light colour is unused
		return (parsing_error("Invalid number of parameters", data), false);
	ft_bzero(&light, sizeof(t_light));
	i = 0;
	while (data && data[++i])
	{
		if (i == 1 && !parse_vector(data[i], &light.position, false))
			return (parsing_error("Invalid light position", data));
		if (i == 2 && !parse_float(data[i], &light.brightness, 0.0, 1.0))
			return (parsing_error("Invalid light brightness ratio", data));
		if (i == 3 && !parse_colour(data[i], &light.colour))
			return (parsing_error("Invalid light colour", data));
	}
	mrt->light = light;
	mrt->num_lights += 1;
	free_array(data);
	return (true);
}
