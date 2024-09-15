/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:08:39 by tluanamn          #+#    #+#             */
/*   Updated: 2023/07/25 14:20:46 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//copies n characters from src to dst, but for overlapping memory blocks
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (dst == NULL && src == NULL)
		return (NULL);
	if (src > dst)
		return (ft_memcpy(dst, src, n));
	else
	{
		while (n--)
		{
			((unsigned char *) dst)[n] = ((unsigned char *) src)[n];
		}
	}
	return (dst);
}
