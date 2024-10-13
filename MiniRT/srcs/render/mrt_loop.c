/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tytang <tytang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:57:47 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/11 15:24:09 by tytang           ###   ########.fr       */
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
	if (keycode == W_KEY || keycode == S_KEY
		|| keycode == A_KEY || keycode == D_KEY
		|| keycode == N_KEY || keycode == M_KEY)
		move_camera(mrt, keycode);
	if (keycode == LEFT_ARROW_KEY || keycode == RIGHT_ARROW_KEY
		|| keycode == DOWN_ARROW_KEY || keycode == UP_ARROW_KEY)
		rotate_camera(mrt, keycode);
	return (1);
}

int	move_camera(t_mrt *mrt, int keycode)
{
	float	move_scale;

	move_scale = 2.0f;
	if (keycode == D_KEY)
		mrt->camera.view_point.x += move_scale;
	if (keycode == A_KEY)
		mrt->camera.view_point.x -= move_scale;
	if (keycode == W_KEY)
		mrt->camera.view_point.z += move_scale;
	if (keycode == S_KEY)
		mrt->camera.view_point.z -= move_scale;
	if (keycode == M_KEY)
		mrt->camera.view_point.y += move_scale;
	if (keycode == N_KEY)
		mrt->camera.view_point.y -= move_scale;
	mrt_render(mrt);
	return (1);
}

// t_vector	rotate_vector(t_vector v, t_vector orientation)
// {
// 	float	y1;
// 	float	z1;
// 	float	x2;

// 	y1 = v.y * cos(orientation.x) - v.z * sin(orientation.x);
// 	z1 = v.y * sin(orientation.x) + v.z * cos(orientation.x);
// 	x2 = v.x * cos(orientation.y) + z1 * sin(orientation.y);
// 	return ((t_vector){x2 * cos(orientation.z) - y1 * sin(orientation.z),
// 		x2 * sin(orientation.z) + y1 * cos(orientation.z),
// 		-v.x * sin(orientation.y) + z1 * cos(orientation.y)});
// }

int	rotate_camera(t_mrt *mrt, int keycode)
{
	float		rotate_factor;
	// t_vector	direction;

	rotate_factor = 0.1f;
	if (keycode == LEFT_ARROW_KEY)
		mrt->camera.orientation.x -= rotate_factor;
	if (keycode == RIGHT_ARROW_KEY)
		mrt->camera.orientation.x += rotate_factor;
	if (keycode == DOWN_ARROW_KEY)
		mrt->camera.orientation.y -= rotate_factor;
	if (keycode == UP_ARROW_KEY)
		mrt->camera.orientation.y += rotate_factor;
	// mrt->camera.orientation =
	// 	vector_normalise(rotate_vector(direction, mrt->camera.orientation));
	mrt_render(mrt);
	return (1);
}

void	mrt_loop(t_mrt *mrt)
{
	mlx_key_hook(mrt->mlx.win, key_hook, mrt);
	mlx_hook(mrt->mlx.win, 17, 0, close_handler, mrt);
	printf("Looping...\n");
	mlx_loop(mrt->mlx.ptr);
}
