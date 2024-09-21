#include "mrt.h"

void	free_mrt(t_mrt *mrt)
{
	// Free spheres
	if (mrt->spheres)
	{
		free(mrt->spheres);
		mrt->spheres = NULL;
	}

	// Free planes
	if (mrt->planes)
	{
		free(mrt->planes);
		mrt->planes = NULL;
	}

	// Free cylinders
	if (mrt->cylinders)
	{
		free(mrt->cylinders);
		mrt->cylinders = NULL;
	}

	// Free the main mrt structure
	free(mrt);
}
