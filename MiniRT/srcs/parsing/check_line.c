/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:19:06 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/15 21:19:07 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

/*
Check type identifier

# Ambient light: A
Number of parameters: 3
- identifier: A
- ambient lighting ratio in range [0.0,1.0]: 0.2
- R,G,B colors in range [0-255]: 255,255,255

# Camera: C
Number of parameters: 4
- identifier: C
- x,y,z coordinates of the view point: -50.0,0,20
- 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
- FOV : Horizontal field of view in degrees in range [0,180]: 70

# Light: L
Number of parameters: 3
- identifier: L
- x,y,z coordinates of the light point: -40.0,50.0,0.0
- the light brightness ratio in range [0.0,1.0]: 0.6
- (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255

-------

# Sphere: sp
Number of parameters: 4
- identifier: sp
- x,y,z coordinates of the sphere center: 0.0,0.0,20.6
- the sphere diameter: 12.6
- R,G,B colors in range [0-255]: 10,0,255

# Plane: pl
Number of parameters: 4
- identifier: pl
- x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
- 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
- R,G,B colors in range [0-255]: 0,0,225

# Cylinder: cy
Number of parameters: 6
- identifier: cy
- x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
- 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
- the cylinder diameter: 14.2
- the cylinder height: 21.42
- R,G,B colors in range [0,255]: 10, 0, 255
*/

// read the line; extract text seperate by space " " or tab "\t" and store it in temp_line[][][]
// File can have multiple empty lines it should be ignored
/*
	temp_line structure: temp_line[i][j][k]
	temp_line[i] stores the line number i
	temp_line[i][j] stores the word number j of line i
	temp_line[i][j][k] stores the character number k of word j of line i
*/

char	*format_line(char *line)
{
	char	*token;
	char	*formatted_line;

	formatted_line = (char *)malloc(BUFFER_SIZE);
	token = ft_strtok(line, "\t ");
	while (token != NULL)
	{
		ft_strcat(formatted_line, token);
		ft_strcat(formatted_line, " ");
		token = ft_strtok(NULL, "\t ");
	}
	if (ft_strlen(formatted_line) > 0)
	{
		formatted_line[ft_strlen(formatted_line) - 1] = '\0';
	}
	return (formatted_line);
}

// Function to split a formatted line into words and store them in the 3D array
char ***ft_split_line(char *formatted_line, char ***tmp_line, int *line_idx, int *word_count) {
    char *token;
    int word_idx = 0;

    token = strtok(formatted_line, " ");
    while (token != NULL) {
        tmp_line[*line_idx][word_idx] = strdup(token);  // Store each word
        token = strtok(NULL, " ");
        word_idx++;
    }

    // Update word count for the line
    word_count[*line_idx] = word_idx;
    (*line_idx)++;
    return tmp_line;
}

bool	check_line(const char *file_name)
{
	int		fd;
	char	*line;
	int		i;
	char	***tmp_line;
// resize buffer
	tmp_line = (char ***)malloc(BUFFER_SIZE * sizeof(char **));
	i = 0;
	while (i < BUFFER_SIZE)
	{
		tmp_line[i] = (char **)malloc(BUFFER_SIZE * sizeof(char *));
		i++;
	}
	int line_idx = 0;
	int word_count[BUFFER_SIZE] = {0};

	printf("tmp_line:\n");

	i = 0;
	fd = open(file_name, O_RDONLY);
	while (true) // Read the file line by line while not EOF
	{
		line = get_next_line(fd);

		printf("line: %s\n", line);

		if (!line)
			break ;
		if (ft_strlen(line) == 0 || ft_strspn(line, " \t\n") == ft_strlen(line))
		{
			free(line);
			continue ;
		}
		// Format the line and store in the 3D array
        char *formatted_line = format_line(line);

		printf("formatted_line: %s\n", formatted_line);

        tmp_line = ft_split_line(formatted_line, tmp_line, &line_idx, word_count);
        free(formatted_line);
        free(line);
	}
	printf("Check type:\n");
	close(fd);
	print_3D_array(tmp_line);
	return (true);
}

// recheck allocated memory for tmp_line

