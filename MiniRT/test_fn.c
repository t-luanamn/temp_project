#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_TOKENS_PER_LINE 10
#define MAX_TOKEN_LENGTH 50

char ***allocate_data(int lines, int tokens_per_line, int token_length) {
    char ***data = malloc(lines * sizeof(char **));
    if (!data) {
        perror("Failed to allocate memory for data");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < lines; i++) {
        data[i] = malloc(tokens_per_line * sizeof(char *));
        if (!data[i]) {
            perror("Failed to allocate memory for data[i]");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < tokens_per_line; j++) {
            data[i][j] = malloc(token_length * sizeof(char));
            if (!data[i][j]) {
                perror("Failed to allocate memory for data[i][j]");
                exit(EXIT_FAILURE);
            }
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

    char ***data = allocate_data(num_lines, MAX_TOKENS_PER_LINE, MAX_TOKEN_LENGTH);

    for (int i = 0; i < num_lines; i++) {
        char *token = strtok(lines[i], " ");
        int j = 0;
        while (token != NULL) {
            strncpy(data[i][j], token, MAX_TOKEN_LENGTH - 1);
            data[i][j][MAX_TOKEN_LENGTH - 1] = '\0'; // Ensure null-termination
            token = strtok(NULL, " ");
            j++;
        }
        data[i][j][0] = '\0'; // Mark end of tokens for this line
    }

    print_data(data, num_lines, MAX_TOKENS_PER_LINE);

    free_data(data, num_lines, MAX_TOKENS_PER_LINE);

    return 0;
}