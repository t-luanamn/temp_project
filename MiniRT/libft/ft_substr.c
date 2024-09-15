/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:50:28 by tluanamn          #+#    #+#             */
/*   Updated: 2023/07/25 21:04:47 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	n;

	n = ft_strlen(s);
	if (len > n)
		len = n;
	if (start > n)
		len = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL || str == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] && n > start)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
