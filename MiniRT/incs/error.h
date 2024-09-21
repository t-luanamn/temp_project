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
# include "mrt.h"
# include "define.h"



// Error
void	print_error(const char *message);
bool	parsing_error(const char *message, char **data);


// Debug


#endif
