/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:49:31 by tluanamn          #+#    #+#             */
/*   Updated: 2023/09/13 14:12:45 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		++s;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	dup = malloc(len);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}
*/

char	*ft_strjoin_and_free_old(char *old, const char *buf)
{
	char	*joined;
	size_t	old_len;
	size_t	buf_len;
	size_t	i;
	size_t	j;

	old_len = ft_strlen(old);
	buf_len = ft_strlen(buf);
	joined = (char *)malloc(sizeof(char) * (old_len + buf_len + 1));
	if (!joined || !buf)
		return (NULL);
	i = -1;
	while (++i < old_len)
		joined[i] = old[i];
	j = -1;
	while (++j < buf_len)
		joined[i + j] = buf[j];
	joined[i + j] = '\0';
	free(old);
	return (joined);
}

/*
char	*ft_substr(const char *str, unsigned int start, size_t size)
{
	char	*substr;
	size_t	i;

	if (ft_strlen(str) <= start)
		return (ft_strdup(""));
	substr = (char *)malloc((size + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < size && str[start + i])
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
*/
