/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:57:53 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/16 08:57:55 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

// Colour
# define RST	"\033[0m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define CYAN	"\033[1;36m"

// Number of parameters
# define PARAMS_AMBIENT 3
# define PARAMS_CAMERA 4
# define PARAMS_LIGHT 4
# define PARAMS_PLANE 4
# define PARAMS_SPHERE 4
# define PARAMS_CYLINDER 6

// Window
# define W_WIDTH 1280
# define W_HEIGHT 720

// Key
# ifdef __APPLE__
#  define IS_LINUX 0
#  define ESC_KEY 53
#  define LEFT_CLICK 1
#  define RIGHT_CLICK 2
# elif defined __unix__
#  define IS_LINUX 1
#  define ESC_KEY 65307
#  define LEFT_CLICK 1
#  define RIGHT_CLICK 2
# endif

#endif
