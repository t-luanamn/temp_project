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
	t_mrt	*mrt;
	int		status;

	status = EXIT_SUCCESS;
	mrt = (t_mrt *)malloc(sizeof(t_mrt));
	if (ac != 2)
	{
		print_error("Error: ac number\nTry: ./miniRT *.rt\n");
		status = EXIT_FAILURE;
	}
	if (!check_file(mrt, av[1]))
		status = EXIT_FAILURE;
	printf("Parsing file...\n");
	printf("Ratio: %f\n", mrt->ambient.ratio);
	printf("Colour: %d %d %d\n", mrt->ambient.colour.r, mrt->ambient.colour.g, mrt->ambient.colour.b);
	free_mrt(mrt);
	return (status);
}
