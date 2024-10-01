#include "mrt.h"

bool	check_scene(t_mrt *mrt)
{
	printf("Checking scene...\n");
	if (!mrt->num_ambient)
		return (print_error("No ambient light found"), false);
	if (!mrt->num_camera)
		return (print_error("No camera found"), false);
	if (!mrt->num_lights)
		return (print_error("No light found"), false);
	return (true);
}
