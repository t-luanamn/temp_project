#ifndef UTILS_H
# define UTILS_H

# include "mrt.h"

typedef struct s_mrt t_mrt;

// Check
bool	check_file(t_mrt *mrt, const char *file_name);
bool	check_line(t_mrt *mrt, const char *file_name);

// Parsing
bool	parser(t_mrt *mrt, char *line);
bool	parse_vector(char *input, t_vector *vector);
bool	parse_colour(char *input, t_colour *colour);
bool	parse_float(char *input, float *value, float min, float max);
bool	parse_ambient(t_mrt *mrt, char **data);

// Utils
void	free_array(char **arr);
int		count_parameters(char **array);
void	print_array(char **array);

#endif
