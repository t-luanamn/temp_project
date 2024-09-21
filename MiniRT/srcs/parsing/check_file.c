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

#include "utils.h"

/*
Check file:
- Check Correct file extention .rt
- return if check empty file
- return if check empty file the have only space, tab, newline
- return if check incorrect file, file not found

Create a temporary variable to store the formatted line of the file:
- 3D array to store the formatted line of the file (char ***tmp_line)
- 1st dimension: number of lines in the file
- 2nd dimension: number of words in each line
- 3rd dimension: number of characters in each word

Read line:
- open file, file is already checked
- read file line by line using get_next_line() function until the end of the file
- if line is NULL, continue to read next line
- if line is empty (have only space, tab, newline), continue to read next line
- if line is not empty, format the line and store it in a temporary variable

Format line:
- remove all space and tab at the beginning and end of the line
- remove extra space and tab between words, only keep one space between words
- return the formatted line

Save line:
- Save the formatted line in the temporary variable
- store the temporary variable in the 3D array (tmp_line) using ft_split() function
- Count the number of lines in the file store it in the 1st dimension of the 3D array starting from 0
- free the temporary variable


Recheck function:
- write function to print the 3D Array (tmp_line) to check the correctness of the formatted line
*/

bool	check_file_type(const char *file_name)
{
	char	*ext;

	ext = ft_strrchr(file_name, '.');
	if (!ext || ft_strcmp(ext, ".rt") != 0)
	{
		print_error("Error: Incorrect file extension");
		return (false);
	}
	return (true);
}

bool check_file_content(const char *file_name)
{
	int		fd;
	char	*line;
	bool	has_non_whitespace;

	has_non_whitespace = false;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		print_error("Error: File not found or cannot be opened");
		return (false);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strlen(line) != 0 && ft_strspn(line, " \t\n") != ft_strlen(line))
			has_non_whitespace = true;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!has_non_whitespace)
	{
		print_error("Error: Empty file");
		return (false);
	}
	return (true);
}

bool	check_file(t_mrt *mrt, const char *file_name)
{
	if (check_file_type(file_name) == false)
		return (false);
	if (check_file_content(file_name) == false)
		return (false);
	if (check_line(mrt, file_name) == false)
		return (false);
	return (true);
}
