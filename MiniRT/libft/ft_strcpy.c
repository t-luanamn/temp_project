/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:51:07 by tluanamn          #+#    #+#             */
/*   Updated: 2023/05/23 16:53:43 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	char	*buf;

	buf = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (buf);
}
/*
int	main(void)
{
	char	*src_str;
	char	*dest_str;

	src_str = "hello world";
	dest_str = (char *)malloc(sizeof(char) * 20);
	printf("%s", ft_strcpy(dest_str, src_str));
}*/
