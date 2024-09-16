/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:18:54 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/15 21:18:56 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt.h"

/*
File management

Correct file type .rt
empty file
incorrect file
*/

/*
bool	check_file_type(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 3)
	{
		print_error("Invalid file");
		return (false);
	}
	if (ft_strcmp(file_name + len - 3, ".rt") == 0)
	{
		return (true);
	}
	else
	{
		print_error("Invalid file extension");
		return (false);
	}
}

bool	check_file_content(char *file_name)
{
	int		fd;
	char	buf[1];

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		print_error("Error: File not found");
		return (false);
	}
	if (read(fd, buf, 1) == 0)
	{
		print_error("Empty file");
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

void print_tmp_line(char ***tmp_line)
{
    for (int i = 0; tmp_line[i] != NULL; i++)
	{
        for (int j = 0; tmp_line[i][j] != NULL; j++)
		{
            printf("%s ", tmp_line[i][j]);
        }
        printf("\n");
    }
}

int	check_file(char *file_name)
{
	char	***tmp_line;

	tmp_line = NULL;
	if (check_file_type(file_name) == false)
		return (false);
	if (check_file_content(file_name) == false)
		return (false);
	if (check_type(file_name, &tmp_line) == false)
		return (false);
	// Parsing: use tmp_line
	printf("Parsing:\n");
	print_tmp_line(tmp_line);
	return (true);
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_TOKENS_PER_LINE 10
#define MAX_TOKEN_LENGTH 50

char ***allocate_data(int lines, int tokens_per_line, int token_length) {
    char ***data = malloc(lines * sizeof(char **));
    for (int i = 0; i < lines; i++) {
        data[i] = malloc(tokens_per_line * sizeof(char *));
        for (int j = 0; j < tokens_per_line; j++) {
            data[i][j] = malloc(token_length * sizeof(char));
        }
    }
    return data;
}

void free_data(char ***data, int lines, int tokens_per_line) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < tokens_per_line; j++) {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);
}

void print_data(char ***data, int lines, int tokens_per_line) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < tokens_per_line && data[i][j][0] != '\0'; j++) {
            printf("%s ", data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char *lines[] = {
        "A 0.2 255,255,255",
        "C -50,0,20 0,0,0 70",
        "L -40,0,30 0.7 255,255,255",
        "pl 0,0,0 0,1.0,0 255,0,225",
        "sp 0,0,20 20 255,0,0",
        "cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255"
    };
    int num_lines = sizeof(lines) / sizeof(lines[0]);

    char ***data = allocate_data(MAX_LINES, MAX_TOKENS_PER_LINE, MAX_TOKEN_LENGTH);

    for (int i = 0; i < num_lines; i++) {
        char *token = strtok(lines[i], " ");
        int j = 0;
        while (token != NULL) {
            strcpy(data[i][j], token);
            token = strtok(NULL, " ");
            j++;
        }
        data[i][j][0] = '\0'; // Mark end of tokens for this line
    }

    print_data(data, num_lines, MAX_TOKENS_PER_LINE);

    free_data(data, MAX_LINES, MAX_TOKENS_PER_LINE);

    return 0;
}