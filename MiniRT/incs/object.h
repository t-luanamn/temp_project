/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:31:54 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/16 09:31:56 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "define.h"

typedef struct s_colour
{
	int	r;
	int	g;
	int	b;
}	t_colour;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		line_length;
}	t_img;

typedef struct s_ambient
{
	float		ratio;
	t_colour	colour;
}	t_ambient;

typedef struct s_camera
{
	t_vector	view_point;
	t_vector	orientation;
	int			fov;
	float		scale;
	float		aspect_ratio;
}	t_camera;

typedef struct s_camera_basis
{
	t_vector right;
	t_vector up;
	t_vector forward;
}	t_camera_basis;

// Colour is unused in mandatory part
typedef struct s_light
{
	t_vector	position;
	float		brightness;
	t_colour	colour;
}	t_light;

typedef struct s_sphere
{
	t_vector	position;
	float		diameter;
	t_colour	colour;
}	t_sphere;

typedef struct s_plane
{
	t_vector	position;
	t_vector	normal_vec;
	t_colour	colour;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	position;
	t_vector	axis;
	float		diameter;
	float		height;
	t_colour	colour;
}	t_cylinder;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_hit
{
	float		closest_t;
	t_sphere	*closest_sphere;
	t_plane		*closest_plane;
	t_cylinder	*closest_cylinder;
	t_vector	hit_point;
}	t_hit;

#endif
