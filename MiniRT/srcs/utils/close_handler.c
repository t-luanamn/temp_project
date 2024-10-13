/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:35:46 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/14 08:35:47 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

int	close_handler(t_mrt *mrt)
{
	printf("Closing...\n");
	printf("Destroying mlx...\n");
	if (mrt->mlx.img.img)
		mlx_destroy_image(mrt->mlx.ptr, mrt->mlx.img.img);
	if (mrt->mlx.win)
	{
		mlx_clear_window(mrt->mlx.ptr, mrt->mlx.win);
		mlx_destroy_window(mrt->mlx.ptr, mrt->mlx.win);
	}
	printf("Freeing mrt...\n");
	free_obj(mrt);
	free(mrt->mlx.ptr);
	printf("Cleaned...\n");
	exit(EXIT_SUCCESS);
}
