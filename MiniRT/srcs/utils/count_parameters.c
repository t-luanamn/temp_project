#include "utils.h"

int count_parameters(char **array)
{
    int	count;

	count = 0;
    if (!array)
        return (0);
    while (array[count])
    {
        count++;
    }
    return (count);
}
