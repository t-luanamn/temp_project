/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tytang <tytang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:57:53 by tluanamn          #+#    #+#             */
/*   Updated: 2024/10/10 19:14:34 by tytang           ###   ########.fr       */
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
# define F1_KEY 122
# define F2_KEY 120
# define F3_KEY 99
# define F4_KEY 118
# define F5_KEY 96
# define F6_KEY 97
# define F7_KEY 98
# define F8_KEY 100
# define F9_KEY 101
# define F10_KEY 109
# define F11_KEY 103
# define F12_KEY 111
# define GRAVE_ACCENT_KEY 50
# define ONE_KEY 18
# define TWO_KEY 19
# define THREE_KEY 20
# define FOUR_KEY 21
# define FIVE_KEY 23
# define SIX_KEY 22
# define SEVEN_KEY 26
# define EIGHT_KEY 28
# define NINE_KEY 25
# define ZERO_KEY 29
# define MINUS_KEY 27
# define EQUAL_KEY 24
# define DELETE_KEY 51
# define TAB_KEY 48
# define Q_KEY 12
# define W_KEY 13
# define E_KEY 14
# define R_KEY 15
# define T_KEY 17
# define Y_KEY 16
# define U_KEY 32
# define I_KEY 34
# define O_KEY 35
# define P_KEY 19
# define LEFT_BRACKET_KEY 33
# define RIGHT_BRACKET_KEY 30
# define BACKSLASH_KEY 42
# define CAPS_LOCK_KEY 57
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define F_KEY 3
# define G_KEY 5
# define H_KEY 4
# define J_KEY 38
# define K_KEY 40
# define L_KEY 37
# define SEMICOLON_KEY 41
# define QUOTE_KEY 39
# define RETURN_KEY 36
# define LEFT_SHIFT_KEY 56
# define Z_KEY 6
# define X_KEY 7
# define C_KEY 8
# define V_KEY 9
# define B_KEY 11
# define N_KEY 45
# define M_KEY 46
# define COMMA_KEY 43
# define PERIOD_KEY 47
# define SLASH_KEY 44
# define RIGHT_SHIFT_KEY 60
# define LEFT_CONTROL_KEY 59
# define LEFT_OPTION_KEY 58
# define LEFT_COMMAND_KEY 55
# define SPACE_KEY 49
# define RIGHT_CONTROL_KEY 62
# define RIGHT_OPTION_KEY 63
# define RIGHT_COMMAND_KEY 64
# define LEFT_ARROW_KEY 123
# define RIGHT_ARROW_KEY 124
# define DOWN_ARROW_KEY 125
# define UP_ARROW_KEY 126

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
