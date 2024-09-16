/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:18:54 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/15 21:18:56 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

/*
File management

Correct file type .rt
empty file
incorrect file
*/

bool	check_file_type(const char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 3)
	{
		print_error("Invalid file");
		return (false);
	}
	if (ft_strcmp(file_name + len - 3, ".rt") == 0)
	{
		return (true);
	}
	else
	{
		print_error("Invalid file extension");
		return (false);
	}
}

bool	check_file_content(const char *file_name)
{
	int		fd;
	char	buf[1];

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		print_error("Error: File not found");
		return (false);
	}
	if (read(fd, buf, 1) == 0)
	{
		print_error("Empty file");
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

int	check_file(const char *file_name)
{
	char	**tmp_line;

	tmp_line = NULL;
	if (check_file_type(file_name) == false)
		return (false);
	
	if (check_file_content(file_name) == false)
		return (false);
	if (check_type(file_name, &tmp_line) == false)
		return (false);
	// Parsing: use tmp_line
	return (true);
}
