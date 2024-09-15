/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:49:18 by tluanamn          #+#    #+#             */
/*   Updated: 2023/09/13 14:12:26 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_next_line(char **temp)
{
	char	*line;
	char	*ptr;

	ptr = *temp;
	while (*ptr && *ptr != '\n')
		ptr++;
	ptr += (*ptr == '\n');
	line = ft_substr(*temp, 0, (size_t)(ptr - *temp));
	if (!line)
	{
		free(*temp);
		return (NULL);
	}
	ptr = ft_strdup(ptr);
	free(*temp);
	*temp = ptr;
	return (line);
}

static char	*ft_read_buffer(char *temp, int fd)
{
	ssize_t	r;
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	r = 1;
	while (!ft_strchr(temp, '\n') && r > 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r >= 0)
		{
			buf[r] = '\0';
			temp = ft_strjoin_and_free_old(temp, buf);
		}
		else
		{
			free(temp);
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!temp[fd])
		temp[fd] = ft_strdup("");
	temp[fd] = ft_read_buffer(temp[fd], fd);
	if (!temp[fd] || !*temp[fd])
	{
		free(temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	return (ft_next_line(&temp[fd]));
}

/*
int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s <file_path>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/

/*
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

./a.out test.txt


test.txt

0123456789012345678901234567890123456789x2
0123456789012345678901234567890123456789x3

0123456789012345678901234567890123456789x5


0123456789012345678901234567890123456789x8



0123456789012345678901234567890123456789x12
Number = 0-9 x 4, 12 line
*/
