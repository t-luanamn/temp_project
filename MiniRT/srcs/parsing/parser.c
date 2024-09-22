/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:39:52 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 13:39:53 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

bool	parser(t_mrt *mrt, char *line)
{
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_ambient(mrt, line));
	if (ft_strncmp(line, "C", 1) == 0)
		return (parse_camera(mrt, line));
	if (ft_strncmp(line, "L", 1) == 0)
		return (parse_light(mrt, line));
	if (ft_strncmp(line, "sp", 2) == 0)
		return (parse_sphere(mrt, line));
	if (ft_strncmp(line, "pl", 2) == 0)
		return (parse_plane(mrt, line));
	if (ft_strncmp(line, "cy", 2) == 0)
		return (parse_cylinder(mrt, line));
	else
	{
		print_error("Unknown identifier");
		print_error(line);
	}
	return (false);
}
