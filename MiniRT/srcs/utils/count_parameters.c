/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:40:07 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 13:40:08 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

int	count_parameters(char **array)
{
	int	count;

	count = 0;
	if (!array)
		return (0);
	while (array[count])
	{
		count++;
	}
	return (count);
}
