/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:17:24 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/15 21:17:25 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_H
# define MRT_H

# include <stdlib.h>   // For malloc, free, exit
# include <unistd.h>   // For open, close, read, write
# include <string.h>   // For strerror
# include <math.h>     // For all functions of the math library
# include <stdio.h>    // For printf

# include "mlx.h"
# include "libft.h"
# include "define.h"
# include "object.h"

typedef struct s_mrt
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	*spheres;  // Use dynamic arrays or linked lists to store multiple objects
	t_plane		*planes;
	t_cylinder	*cylinders;
	int			num_spheres;
	int			num_planes;
	int			num_cylinders;
}	t_mrt;

// Error
void	print_error(const char *message);
bool	parsing_error(const char *message, char **data);

// Check
bool	check_file(t_mrt *mrt, const char *file_name);
bool	check_line(t_mrt *mrt, const char *file_name);

// Parsing
bool	parser(t_mrt *mrt, char *line);
bool	parse_vector(char *input, t_vector *vector);
bool	parse_colour(char *input, t_colour *colour);
bool	parse_float(char *input, float *value, float min, float max);
bool	parse_ambient(t_mrt *mrt, char *line);

// Utils
void	free_array(char **arr);
void	free_mrt(t_mrt *mrt);
int		count_parameters(char **array);
void	print_array(char **array);


#endif
