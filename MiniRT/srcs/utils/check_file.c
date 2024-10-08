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
Check file:
- Check Correct file extention .rt
- return if check empty file
- return if check empty file the have only space, tab, newline
- return if check incorrect file, file not found

Read line:
- open file, file is already checked
- read file line by line using get_next_line() function until the EOF
- if line is empty (have only space, tab, newline), continue to read next line
- if line is not empty, format the line and store it in a temporary variable
*/
bool	check_file_type(const char *file_name)
{
	char	*ext;

	ext = ft_strrchr(file_name, '.');
	if (!ext || ft_strcmp(ext, ".rt") != 0)
	{
		print_error("Incorrect file extension");
		return (false);
	}
	return (true);
}

bool	check_file_content(const char *file_name)
{
	int		fd;
	char	*line;
	bool	has_non_whitespace;

	has_non_whitespace = false;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (print_error("File not found or cannot be opened"), false);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strlen(line) != 0 && ft_strspn(line, " \t\n") != ft_strlen(line))
			has_non_whitespace = true;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	if (!has_non_whitespace)
	{
		print_error("Empty file");
		return (false);
	}
	return (true);
}

bool	check_file(t_mrt *mrt, const char *file_name)
{
	printf("Checking file...\n");
	if (check_file_type(file_name) == false)
		return (false);
	if (check_file_content(file_name) == false)
		return (false);
	if (check_line(mrt, file_name) == false)
		return (false);
	return (true);
}
