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

Correct file type   .rt
empty file
incorrect file
*/

int	check_file_type(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 3)
	{
		printf("Error: Invalid file\n");
		return (false);
	}
	if (ft_strcmp(file_name + len - 3, ".rt") == 0)
	{
		return (true);
	}
	else
	{
		printf("Error: Invalid file extension\n");
		return (false);
	}
}

int	check_file_content(char *file_name)
{

}

int	check_file(char *file_name)
{
	if (check_file_type(file_name) == false)
		return (false);

	// int		fd;
	// char	buf[1];

	// fd = open(file_name, O_RDONLY);
	// if (fd < 0)
	// {
	// 	printf("Error: File not found\n");
	// 	return (false);
	// }
	// if (read(fd, buf, 1) == 0)
	// {
	// 	printf("Error: Empty file\n");
	// 	close(fd);
	// 	return (false);
	// }
	// close(fd);
	// return (true);

	//check type
}