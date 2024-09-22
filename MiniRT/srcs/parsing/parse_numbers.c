/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:32:15 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 14:32:17 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

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

bool	parse_int(char *input, int *value, int min, int max)
{
	int	num;

	if (!ft_isnumber(input))
		return (false);
	num = ft_atoi(input);
	if (num < min || num > max)
		return (false);
	*value = num;
	return (true);
}
