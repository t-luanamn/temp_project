/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:34:42 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 13:34:44 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	parse_fractional_part(char **str)
{
	float	precision;
	float	divisor;

	precision = 0.0;
	divisor = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			divisor *= 10.0;
			precision += (**str - '0') / divisor;
			(*str)++;
		}
	}
	return (precision);
}

float	ft_atof(char *str)
{
	float	sum;
	float	sign;
	float	precision;

	sign = 1.0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1.0;
		str++;
	}
	sum = (float)ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		str++;
	precision = parse_fractional_part(&str);
	return ((sum + precision) * sign);
}
