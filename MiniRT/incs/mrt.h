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
#include <float.h>
# include <stdio.h>    // For printf

# include "mlx.h"
# include "libft.h"
# include "define.h"
# include "object.h"

typedef struct s_window
{
	void	*ptr;
	void	*win;
	t_img	img;
}	t_window;

typedef struct s_mrt
{
	t_window	mlx;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	int			num_ambient;
	int			num_camera;
	int			num_lights;
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
bool	parse_vector(char *input, t_vector *vector, bool range_check);
bool	parse_colour(char *input, t_colour *colour);
bool	parse_float(char *input, float *value, float min, float max);
bool	parse_int(char *input, int *value, int min, int max);
bool	parse_ambient(t_mrt *mrt, char *line);
bool	parse_camera(t_mrt *mrt, char *line);
bool	parse_light(t_mrt *mrt, char *line);
bool	parse_sphere(t_mrt *mrt, char *line);
bool	parse_plane(t_mrt *mrt, char *line);
bool	parse_cylinder(t_mrt *mrt, char *line);
bool	add_sphere(t_mrt *mrt, t_sphere sphere);
bool	add_plane(t_mrt *mrt, t_plane plane);
bool	add_cylinder(t_mrt *mrt, t_cylinder cylinder);

// Utils
void	free_array(char **arr);
void	free_mrt(t_mrt *mrt);
int		count_parameters(char **array);
void	print_array(char **array);

// Print values
void	print_mrt(t_mrt *mrt);
void	print_colour(t_colour colour);
void	print_vector(t_vector vector);
void	print_ambient(t_ambient ambient);
void	print_camera(t_camera camera);
void	print_light(t_light light);
void	print_sphere(t_sphere sphere, int i);
void	print_plane(t_plane plane, int i);
void	print_cylinder(t_cylinder cylinder, int i);

// Init and clear
bool	mrt_init(t_window *mlx);
void	mrt_loop(t_mrt *mrt);
void	free_obj(t_mrt *mrt);
int		close_handler(t_mrt *mrt);


// Render
void	mrt_render(t_mrt *mrt);

#endif
