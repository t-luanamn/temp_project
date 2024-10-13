/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:39:26 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 13:39:31 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

static bool	compare_vector(t_vector *vec, float x, float y, float z)
{
	return (vec->x == x && vec->y == y && vec->z == z);
}

static bool	validate_vector(char **components, bool range_check)
{
	int		i;
	float	num;

	i = 0;
	while (i < 3)
	{
		if (!ft_isfloat(components[i]))
			return (false);
		num = ft_atof(components[i]);
		if (range_check && (num < -1.0 || num > 1.0))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_vector(char *input, t_vector *vector, bool range_check)
{
	char	**components;
	bool	return_value;

	return_value = true;
	components = ft_split(input, ',');
	if (!components || count_parameters(components) != 3)
		return_value = false;
	if (!validate_vector(components, range_check))
		return_value = false;
	else
	{
		vector->x = ft_atof(components[0]);
		vector->y = ft_atof(components[1]);
		vector->z = ft_atof(components[2]);
	}
	if (range_check)
	{
		if (compare_vector(vector, 0, 0, 0))
			return_value = false;
	}
	free_array(components);
	return (return_value);
}

static bool	validate_colour(char **components)
{
	int	i;
	int	num;

	i = 0;
	while (i < 3)
	{
		if (!ft_isnumber(components[i]))
			return (false);
		num = ft_atoi(components[i]);
		if (num < 0 || num > 255)
			return (false);
		i++;
	}
	return (true);
}

bool	parse_colour(char *input, t_colour *colour)
{
	char	**components;
	bool	return_value;

	return_value = true;
	components = ft_split(input, ',');
	if (!components || count_parameters(components) != 3)
		return_value = false;
	if (!validate_colour(components))
		return_value = false;
	else
	{
		colour->r = ft_atoi(components[0]);
		colour->g = ft_atoi(components[1]);
		colour->b = ft_atoi(components[2]);
	}
	free_array(components);
	return (return_value);
}
