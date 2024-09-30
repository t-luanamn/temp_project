/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:40:34 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/22 13:40:36 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

void	free_mrt(t_mrt *mrt)
{
	printf("Freeing obj...\n");
	if (mrt->spheres)
	{
		printf("Freeing spheres...\n");
		free(mrt->spheres);
		mrt->spheres = NULL;
	}
	if (mrt->planes)
	{
		printf("Freeing planes...\n");
		free(mrt->planes);
		mrt->planes = NULL;
	}
	if (mrt->cylinders)
	{
		printf("Freeing cylinders...\n");
		free(mrt->cylinders);
		mrt->cylinders = NULL;
	}
}
