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
}	t_camera;

typedef struct s_light
{
	t_vector	position;
	float		brightness;
	t_colour	colour; // unused in mandatory part
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

#endif
