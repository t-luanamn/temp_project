/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:19:06 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/15 21:19:07 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

/*
Check type identifier

# Ambient light: A
Number of parameters: 3
- identifier: A
- ambient lighting ratio in range [0.0,1.0]: 0.2
- R,G,B colors in range [0-255]: 255,255,255

# Camera: C
Number of parameters: 4
- identifier: C
- x,y,z coordinates of the view point: -50.0,0,20
- 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
- FOV : Horizontal field of view in degrees in range [0,180]: 70

# Light: L
Number of parameters: 3
- identifier: L
- x,y,z coordinates of the light point: -40.0,50.0,0.0
- the light brightness ratio in range [0.0,1.0]: 0.6
- (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255

-------

# Sphere: sp
Number of parameters: 4
- identifier: sp
- x,y,z coordinates of the sphere center: 0.0,0.0,20.6
- the sphere diameter: 12.6
- R,G,B colors in range [0-255]: 10,0,255

# Plane: pl
Number of parameters: 4
- identifier: pl
- x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
- 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
- R,G,B colors in range [0-255]: 0,0,225

# Cylinder: cy
Number of parameters: 6
- identifier: cy
- x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
- 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
- the cylinder diameter: 14.2
- the cylinder height: 21.42
- R,G,B colors in range [0,255]: 10, 0, 255
*/



int	check_type(const char *file_name, char ***tmp_line)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	printf("Check type:\n");
	close(fd);
	return (true);
}