/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:57:47 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/05 14:57:48 by tluanamn         ###   ########.fr       */
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

static int	key_hook(int keycode, t_mrt *mrt)
{
	printf("Key hook...\n");
	if (keycode == ESC_KEY)
		close_handler(mrt);
	return (1);
}

void	mrt_loop(t_mrt *mrt)
{
	mlx_key_hook(mrt->mlx.win, key_hook, mrt);
	mlx_hook(mrt->mlx.win, 17, 0, close_handler, mrt);
	printf("Looping...\n");
	mlx_loop(mrt->mlx.ptr);
}
