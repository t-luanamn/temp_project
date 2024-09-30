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
	mrt->spheres = NULL;
	mrt->planes = NULL;
	mrt->cylinders = NULL;
}

int	main(int ac, char **av)
{
	t_mrt	mrt;

	if (ac != 2)
		return (print_error("Error: Try: ./miniRT *.rt\n"), EXIT_FAILURE);
	mrt_obj_num_init(&mrt);
	if (!check_file(&mrt, av[1]))
		return (free_mrt(&mrt), EXIT_FAILURE);
	print_mrt(&mrt);
	mrt_init(&mrt);
	mrt_render(&mrt);
	free_mrt(&mrt);
	mlx_key_hook(mrt.mlx_win, key_hook, &mrt);
	mlx_hook(mrt.mlx_win, 17, 1L<<17, close_handler, &mrt);
	printf("Looping...(main)\n");
	mlx_loop(&mrt.mlx);
	return (EXIT_SUCCESS);
}
