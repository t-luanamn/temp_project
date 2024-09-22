/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_acl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:52:22 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 14:52:24 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

void	print_ambient(t_ambient ambient)
{
	printf(CYAN"Ambient:\n"RST);
	printf("     Ratio: %f\n", ambient.ratio);
	print_colour(ambient.colour);
	printf("\n");
}

void	print_camera(t_camera camera)
{
	printf(CYAN"Camera:\n"RST);
	print_vector(camera.view_point);
	print_vector(camera.orientation);
	printf("       FOV: %d\n", camera.fov);
	printf("\n");
}

void	print_light(t_light light)
{
	printf(CYAN"Light:\n"RST);
	print_vector(light.position);
	printf("Brightness: %f\n", light.brightness);
	print_colour(light.colour);
	printf("\n");
}
