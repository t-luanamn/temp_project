/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:17:17 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/15 21:17:18 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <stdbool.h>
# include "define.h"



// Check file
bool	check_file(const char *file_name);
bool	check_line(const char *file_name);

// Error
void	print_error(const char *message);

// Debug
void	print_3D_array(char ***tmp_line);


#endif
