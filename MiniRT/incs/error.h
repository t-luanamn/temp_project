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
# include "define.h"



// Check file
int		check_file(const char *file_name);
bool	check_file_type(const char *file_name);
bool	check_file_content(const char *file_name);
int		check_type(const char *file_name, char ***tmp_line);

// Error
void	print_error(const char *message);

#endif
