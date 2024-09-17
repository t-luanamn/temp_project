#include "error.h"

void print_3D_array(char ***tmp_line)
{
	int i = 0;
	int j;

	while (tmp_line[i] != NULL)
	{
		j = 0;
		while (tmp_line[i][j] != NULL)
		{
			printf("%s ", tmp_line[i][j]);
			j++;
		}
		i++;
	}
}