/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:13:26 by tluanamn          #+#    #+#             */
/*   Updated: 2023/07/18 14:22:25 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//copies up to dstsize - 1 characters from the string src to dst
//NUL-terminating the result if dstsize is not 0.
size_t	ft_strlcpy(char *dst, const char *src, size_t dst_n)
{
	size_t	i;
	size_t	src_n;

	src_n = 0;
	while (src[src_n] != '\0')
		src_n++;
	if (dst_n > 0)
	{
		i = 0;
		while (i < dst_n - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_n);
}
