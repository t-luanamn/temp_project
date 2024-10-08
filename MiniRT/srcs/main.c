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

int	main(int ac, char **av)
{
	t_mrt	mrt;

	if (ac != 2)
		return (print_error("Try: ./miniRT *.rt\n"), EXIT_FAILURE);
	ft_memset(&mrt, 0, sizeof(t_mrt));
	if (!check_file(&mrt, av[1]))
		return (free_mrt(&mrt), EXIT_FAILURE);
	if (!mrt_init(&mrt.mlx))
		return (print_error("Initialse failed\n"), EXIT_FAILURE);
	print_mrt(&mrt);
	mrt_render(&mrt);
	mrt_loop(&mrt);
	return (EXIT_SUCCESS);
}
