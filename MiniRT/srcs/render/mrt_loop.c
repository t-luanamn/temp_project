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

static int	key_hook(int keycode, t_mrt *mrt)
{
	printf("Key hook... %d\n", keycode);
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

t_vector	rotate_vector(t_vector v, t_vector rotation)
{
	t_vector	rotated;
	t_vector	temp;

	temp.x = v.x * cos(rotation.y) + v.z * sin(rotation.y);
	temp.z = -v.x * sin(rotation.y) + v.z * cos(rotation.y);
	temp.y = v.y;
	rotated.y = temp.y * cos(rotation.x) - temp.z * sin(rotation.x);
	rotated.z = temp.y * sin(rotation.x) + temp.z * cos(rotation.x);
	rotated.x = temp.x;
	return (rotated);
}

int	rotate_camera(t_mrt *mrt, int keycode)
{
	float		rotate_factor;
	t_vector	rotation;

	rotation = (t_vector){0, 0, 0};
	rotate_factor = 0.1f;
	if (keycode == LEFT_ARROW_KEY)
		rotation.y = -rotate_factor;
	if (keycode == RIGHT_ARROW_KEY)
		rotation.y = rotate_factor;
	if (keycode == UP_ARROW_KEY)
		rotation.x = rotate_factor;
	if (keycode == DOWN_ARROW_KEY)
		rotation.x = -rotate_factor;
	mrt->camera.orientation = rotate_vector(mrt->camera.orientation, rotation);
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
