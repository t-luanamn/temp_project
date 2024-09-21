#include "mrt.h"

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

int	is_number(char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

bool	validate_colour(char **components)
{
	int	i;
	int	num;

	i = 0;
	while (i < 3)
	{
		if (!is_number(components[i]))
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
