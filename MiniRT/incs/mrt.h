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

# include "mlx.h"
# include "libft.h"
# include "define.h"
# include "object.h"
# include "error.h"
# include "utils.h"

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


#endif
