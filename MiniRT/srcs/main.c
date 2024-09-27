/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:18:39 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/15 21:18:41 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

void	mrt_obj_num_init(t_mrt *mrt)
{
	mrt->num_ambient = 0;
	mrt->num_camera = 0;
	mrt->num_lights = 0;
	mrt->num_spheres = 0;
	mrt->num_planes = 0;
	mrt->num_cylinders = 0;
}

int	main(int ac, char **av)
{
	t_mrt	*mrt;

	mrt = (t_mrt *)malloc(sizeof(t_mrt));
	mrt_obj_num_init(mrt);
	if (ac != 2)
	{
		print_error("Error: ac number\nTry: ./miniRT *.rt\n");
		free_mrt(mrt);
		return (EXIT_FAILURE);
	}
	if (!check_file(mrt, av[1]))
	{
		free_mrt(mrt);
		return (EXIT_FAILURE);
	}
	print_mrt(mrt);
	mrt_init(mrt);
	mrt_render(mrt);
	printf("Looping...(main)\n");
	mlx_loop(mrt->mlx);
	return (EXIT_SUCCESS);
}
