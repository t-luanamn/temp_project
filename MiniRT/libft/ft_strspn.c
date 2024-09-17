/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:37:14 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/17 21:37:15 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *str, const char *accept)
{
	size_t		count;
	const char	*a;
	bool		char_found;

	count = 0;
	while (*str)
	{
		a = accept;
		char_found = false;
		while (*a)
		{
			if (*str == *a)
			{
				char_found = true;
				break ;
			}
			++a;
		}
		if (!char_found)
			break ;
		++count;
		++str;
	}
	return (count);
}
