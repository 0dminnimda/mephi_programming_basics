#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "vector.h"

#define COMMAND_COUNT 6
#define STRMAX 256

void print_commands(const char *command_names[], size_t count) {
    printf("Available commands:\n");
    for (size_t i = 0; i < count; i++) {
        printf("- '%s'\n", command_names[i]);
    }
}

void partition(char *string, char *delim, char **first, char **second) {
    char *rest = NULL;

    if (string != NULL) *first = strtok_s(string, delim, &rest);
    if (*first == NULL) *first = "";

    *second = rest;
    if (*second == NULL) *second = "";
}

void read_command(char *string, char **first, char **second) {
    fgets(string, STRMAX, stdin);
    partition(string, " \n", first, second);
}

size_t match_command(const char *command_names[], size_t count,
                     const char *command_name) {
    for (size_t i = 0; i < count; i++)
        if (strcmp(command_name, command_names[i]) == 0) return i;

    return -1;
}

int exit_command(char *str, Vector vec) {
    printf("Exiting ...\n");
    return 1;
}

int main() {
    command_t *commands[COMMAND_COUNT] = {
        init_command,         insert_command, remove_at_command,
        process_data_command, print_command,  exit_command,
    };
    const char *command_names[COMMAND_COUNT] = {
        "init", "insert", "remove_at", "process_data", "print", "exit",
    };

    printf("Hello, fellow user!\n");
    print_commands(command_names, COMMAND_COUNT);

    Vector vec;
    if (create(&vec, 0)) {
        printf("Could not create a Vector\n");
        return -1;
    }

    while (1) {
        printf(">>> ");
        char string[STRMAX], *command, *input;
        read_command(string, &command, &input);

        size_t index = match_command(command_names, COMMAND_COUNT, command);

        if (index == -1) {
            printf("Wrong input, try again!\n");
            print_commands(command_names, COMMAND_COUNT);
        } else {
            if (commands[index](input, vec)) break;
        }
    }

    printf("destroy\n");
    destroy(vec);

    return 0;
}
