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

# define FLT_MAX 3.402823466e+38F

// Window
# define W_WIDTH 1280
# define W_HEIGHT 720

// Key Apple
# define ESC_KEY 53
// Key Linux
// # define ESC_KEY 65307

/*
math.h constants
M_E 		e 			2.71828182845904523536
M_LOG2E 	log2(e) 	1.44269504088896340736
M_LOG10E 	log10(e) 	0.434294481903251827651
M_LN2 		ln(2) 		0.693147180559945309417
M_LN10 		ln(10) 		2.30258509299404568402
M_PI 		pi 			3.14159265358979323846
M_PI_2 		pi/2 		1.57079632679489661923
M_PI_4 		pi/4 		0.785398163397448309616
M_1_PI 		1/pi 		0.318309886183790671538
M_2_PI 		2/pi 		0.636619772367581343076
M_2_SQRTPI 	2/sqrt(pi) 	1.12837916709551257390
M_SQRT2 	sqrt(2) 	1.41421356237309504880
M_SQRT1_2 	1/sqrt(2) 	0.707106781186547524401
*/

#endif
