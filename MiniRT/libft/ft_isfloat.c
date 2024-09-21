#include "libft.h"

bool	ft_isfloat(char *str)
{
	bool	has_decimal;
	int		i;

	has_decimal = false;
	i = 0;
	if (!str || *str == '\0')
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_decimal)
				return (false);
			has_decimal = true;
		}
		else if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
