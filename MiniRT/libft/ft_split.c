/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:51:13 by tluanamn          #+#    #+#             */
/*   Updated: 2023/07/25 10:16:40 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	count;
	int	word;

	count = 0;
	word = 0;
	while (*str)
	{
		if (*str != c && !word)
		{
			count++;
			word = 1;
		}
		else if (*str == c && word)
		{
			word = 0;
		}
		str++;
	}
	return (count);
}

static char	*extract_word(const char *str, char c)
{
	const char	*start;
	int			len;
	int			i;
	char		*word;

	start = str;
	len = 0;
	while (*str && *str != c)
	{
		str++;
		len++;
	}
	word = (char *)malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	free_memory(char **result, int count)
{
	while (count > 0)
		free(result[--count]);
	free(result);
}

static void	extract_store_word(char **result, const char **s, char c, int *i)
{
	result[*i] = extract_word(*s, c);
	if (result[*i] == NULL)
	{
		free_memory(result, *i);
		*i = 0;
	}
	else
	{
		(*i)++;
		while (**s && **s != c)
			(*s)++;
	}
}

char	**ft_split(const char *s, char c)
{
	int		word_count;
	char	**result;
	int		i;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
			extract_store_word(result, &s, c, &i);
		else
		{
			while (*s == c)
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
