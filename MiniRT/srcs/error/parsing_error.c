#include "error.h"

bool	parsing_error(const char *message, char **data)
{
	print_error(message);
	print_array(data);
	free_array(data);
	return (false);
}
