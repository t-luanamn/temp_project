/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tytang <tytang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:17:24 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/11 15:26:06 by tytang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_H
# define MRT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
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
void		print_error(const char *message);
bool		parsing_error(const char *message, char **data);

// Check
bool		check_file(t_mrt *mrt, const char *file_name);
bool		check_line(t_mrt *mrt, const char *file_name);

// Parsing
bool		parser(t_mrt *mrt, char *line);
bool		parse_vector(char *input, t_vector *vector, bool range_check);
bool		parse_colour(char *input, t_colour *colour);
bool		parse_float(char *input, float *value, float min, float max);
bool		parse_int(char *input, int *value, int min, int max);
bool		parse_ambient(t_mrt *mrt, char *line);
bool		parse_camera(t_mrt *mrt, char *line);
bool		parse_light(t_mrt *mrt, char *line);
bool		parse_sphere(t_mrt *mrt, char *line);
bool		parse_plane(t_mrt *mrt, char *line);
bool		parse_cylinder(t_mrt *mrt, char *line);
bool		add_sphere(t_mrt *mrt, t_sphere sphere);
bool		add_plane(t_mrt *mrt, t_plane plane);
bool		add_cylinder(t_mrt *mrt, t_cylinder cylinder);

// Utils
void		free_array(char **arr);
void		free_mrt(t_mrt *mrt);
int			count_parameters(char **array);
void		print_array(char **array);

// Vector operations
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_subtract(t_vector v1, t_vector v2);
t_vector	vector_scale(t_vector v, float scalar);
float		vector_dot(t_vector v1, t_vector v2);
t_vector	vector_cross(t_vector v1, t_vector v2);
t_vector	normalise(t_vector v);
float		vector_length(t_vector v);

// Print values
void		print_mrt(t_mrt *mrt);
void		print_colour(t_colour colour);
void		print_vector(t_vector vector);
void		print_ambient(t_ambient ambient);
void		print_camera(t_camera camera);
void		print_light(t_light light);
void		print_sphere(t_sphere sphere, int i);
void		print_plane(t_plane plane, int i);
void		print_cylinder(t_cylinder cylinder, int i);

// Init and clear
bool		mrt_init(t_window *mlx);
void		mrt_loop(t_mrt *mrt);
void		free_obj(t_mrt *mrt);
int			close_handler(t_mrt *mrt);
int			move_camera(t_mrt *mrt, int keycode);
int			rotate_camera(t_mrt *mrt, int keycode);

// Render
void		mrt_render(t_mrt *mrt);
t_colour	ray_trace(t_ray ray, t_mrt *scene);
void		put_pixel(t_img *img, int x, int y, t_colour colour);
void		render_pixel(t_mrt *mrt, int x, int y);
t_vector	rotate_vector(t_vector v, t_vector orientation);
t_vector	calculate_world_up(t_vector forward);
void		calculate_camera_basis(t_vector forward, t_camera_basis *basis);
t_ray		generate_ray(t_mrt *mrt, int x, int y, t_camera_basis basis);

t_vector	calculate_hit_point(t_ray ray, float t);
t_vector	calculate_normal_sphere(t_vector hit_point, t_sphere *sphere);
t_vector	calculate_normal_plane(t_plane *plane);
t_vector	calculate_normal_cylinder(t_vector hit_point, t_cylinder *cylinder);

int			intersect_sphere(t_ray ray, t_sphere sphere, float *t);
int			intersect_sphere_solutions(float a, float b, float discriminant,
				float *t);
int			intersect_plane(t_ray ray, t_plane plane, float *t);
int			intersect_cylinder(t_ray ray, t_cylinder cylinder, float *t);
int			intersect_cylinder_solutions(t_ray ray, t_cylinder cylinder,
				float *t_vals, float *t);
void		init_hit_data(t_hit *hit_data);
void		find_closest_objects(t_ray ray, t_mrt *scene, t_hit *hit_data);
void		find_closest_sphere(t_ray ray, t_mrt *scene, float *closest_t,
				t_sphere **closest_sphere);
void		find_closest_plane(t_ray ray, t_mrt *scene, float *closest_t,
				t_plane **closest_plane);
void		find_closest_cylinder(t_ray ray, t_mrt *scene, float *closest_t,
				t_cylinder **closest_cylinder);

float		calculate_diffuse(float diff, t_mrt *scene);
void		add_ambient_light(t_mrt *scene, t_colour *colour);
void		apply_shadow(t_mrt *scene, t_hit *hit_data, t_ray light_ray,
				t_colour *colour);
float		calculate_specular(t_vector light_dir, t_vector view_dir,
				t_vector normal, t_mrt *scene);
t_colour	calculate_hit_colour(t_mrt *scene, t_hit *hit_data,
				t_vector light_dir);
t_colour	blend(float diffuse, float specular, t_colour obj_colour);

#endif
