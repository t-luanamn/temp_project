#include "utils.h"

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		printf("%s ", array[i]);
		i++;
	}
	printf("\n");
}
