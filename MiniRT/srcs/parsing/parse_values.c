#include "utils.h"

bool	parse_vector(char *input, t_vector *vector)
{
	char	**components;
	int		i;

	components = NULL;
	i = 0;
	components = ft_split(input, ',');
	if (!components)
		return (false);
	for (i = 0; i < 3; i++)
	{
		if (!components[i])
		{
			free_array(components);
			return (false);
		}
	}
	vector->x = ft_atof(components[0]);
	vector->y = ft_atof(components[1]);
	vector->z = ft_atof(components[2]);
	free_array(components);
	return (true);
}

static bool	validate_and_assign_colour(char **components, t_colour *colour)
{
	int	i;
	int	num;

	i = 0;
	while (i < 3)
	{
		num = ft_atoi(components[i]);
		if (!ft_isdigit(num))
			return (false);
		if (num < 0 || num > 255)
			return (false);
		if (i == 0) colour->r = num;
		if (i == 1) colour->g = num;
		if (i == 2) colour->b = num;
		i++;
	}
	return (true);
}

bool	parse_colour(char *input, t_colour *colour)
{
	char	**components;

	components = ft_split(input, ',');
	if (!components || count_parameters(components) != 3)
	{
		free_array(components);
		return (false);
	}
	if (!validate_and_assign_colour(components, colour))
	{
		free_array(components);
		return (false);
	}
	free_array(components);
	return (true);
}

bool	parse_float(char *input, float *value, float min, float max)
{
	float	num;

	if (!ft_isfloat(input))
		return (false);
	num = ft_atof(input);
	if (num < min || num > max)
		return (false);
	*value = num;
	return (true);
}
