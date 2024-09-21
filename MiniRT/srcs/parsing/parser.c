#include "mrt.h"

bool	parser(t_mrt *mrt, char *line)
{
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_ambient(mrt, line));
	// else if (ft_strcmp(split_line[0], "C") == 0)
	// 	mrt->camera = parse_camera(split_line);
	// else if (ft_strcmp(split_line[0], "L") == 0)
	// 	mrt->light = parse_light(split_line);
	// else if (ft_strcmp(split_line[0], "sp") == 0)
	// 	add_sphere(mrt, parse_sphere(split_line));
	// else if (ft_strcmp(split_line[0], "pl") == 0)
	// 	add_plane(mrt, parse_plane(split_line));
	// else if (ft_strcmp(split_line[0], "cy") == 0)
	// 	add_cylinder(mrt, parse_cylinder(split_line));
	else
	{
		print_error("Unknown identifier");
		print_error(line);
	}
	return (false);
}

bool	parse_ambient(t_mrt *mrt, char *line)
{
	char		**data;
	t_ambient	amb;
	int			i;

	data = ft_split(line, ' ');
	if (count_parameters(data) != PARAMS_AMBIENT)
	{
		parsing_error("Invalid number of parameters for ambient light", data);
		free_array(data);
		return (false);
	}
	ft_bzero(&amb, sizeof(t_ambient));
	i = 0;
	while (data && data[++i])
	{
		if (i == 1 && !parse_float(data[i], &amb.ratio, 0.0, 1.0))
			return (parsing_error("Invalid ambient light ratio", data));
		if (i == 2 && !parse_colour(data[i], &amb.colour))
			return (parsing_error("Invalid ambient light colour", data));
	}
	mrt->ambient = amb;
	free_array(data);
	return (true);
}

/*


t_camera parse_camera(t_mrt *mrt, char **data)
{
	t_camera cam;
	cam.view_point.x = atof(data[1]);
	cam.view_point.y = atof(data[2]);
	cam.view_point.z = atof(data[3]);
	cam.orientation.x = atof(data[4]);
	cam.orientation.y = atof(data[5]);
	cam.orientation.z = atof(data[6]);
	cam.fov = atoi(data[7]);
	return cam;
}

t_light parse_light(t_mrt *mrt, char **data)
{
	t_light light;
	light.position.x = atof(data[1]);
	light.position.y = atof(data[2]);
	light.position.z = atof(data[3]);
	light.brightness = atof(data[4]);
	return light;
}

// Similar functions for Sphere, Plane, and Cylinder

t_sphere parse_sphere(t_mrt *mrt, char **data)
{
	t_sphere sphere;

	// Expecting format: "sp x,y,z diameter R,G,B"
	sphere.position.x = atof(data[1]); // x-coordinate of the sphere's center
	sphere.position.y = atof(data[2]); // y-coordinate of the sphere's center
	sphere.position.z = atof(data[3]); // z-coordinate of the sphere's center
	sphere.diameter = atof(data[4]);   // Sphere diameter
	sphere.colour.r = atoi(data[5]);   // Red value of sphere color
	sphere.colour.g = atoi(data[6]);   // Green value of sphere color
	sphere.colour.b = atoi(data[7]);   // Blue value of sphere color

	return sphere;
}
t_plane parse_plane(t_mrt *mrt, char **data)
{
	t_plane plane;

	// Expecting format: "pl x,y,z nx,ny,nz R,G,B"
	plane.position.x = atof(data[1]);  // x-coordinate of a point on the plane
	plane.position.y = atof(data[2]);  // y-coordinate of a point on the plane
	plane.position.z = atof(data[3]);  // z-coordinate of a point on the plane
	plane.normal_vec.x = atof(data[4]); // x-component of the plane's normal vector
	plane.normal_vec.y = atof(data[5]); // y-component of the plane's normal vector
	plane.normal_vec.z = atof(data[6]); // z-component of the plane's normal vector
	plane.colour.r = atoi(data[7]);    // Red value of plane color
	plane.colour.g = atoi(data[8]);    // Green value of plane color
	plane.colour.b = atoi(data[9]);    // Blue value of plane color

	return plane;
}
t_cylinder parse_cylinder(t_mrt *mrt, char **data)
{
	t_cylinder cylinder;

	// Expecting format: "cy x,y,z nx,ny,nz diameter height R,G,B"
	cylinder.position.x = atof(data[1]);  // x-coordinate of the cylinder's center
	cylinder.position.y = atof(data[2]);  // y-coordinate of the cylinder's center
	cylinder.position.z = atof(data[3]);  // z-coordinate of the cylinder's center
	cylinder.axis.x = atof(data[4]);      // x-component of the cylinder's axis
	cylinder.axis.y = atof(data[5]);      // y-component of the cylinder's axis
	cylinder.axis.z = atof(data[6]);      // z-component of the cylinder's axis
	cylinder.diameter = atof(data[7]);    // Cylinder diameter
	cylinder.height = atof(data[8]);      // Cylinder height
	cylinder.colour.r = atoi(data[9]);    // Red value of cylinder color
	cylinder.colour.g = atoi(data[10]);   // Green value of cylinder color
	cylinder.colour.b = atoi(data[11]);   // Blue value of cylinder color

	return cylinder;
}
void add_sphere(t_mrt *mrt, t_sphere sphere)
{
	mrt->spheres[mrt->num_spheres] = sphere;
	mrt->num_spheres++;
}
//For memory management, you'd need to dynamically allocate memory for spheres, planes, and cylinders.



*/