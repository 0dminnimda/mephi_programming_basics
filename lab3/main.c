#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"

#define COMMAND_COUNT 6
#define STRMAX 256

void print_commands(const char *command_names[], size_t count) {
    printf("Available commands:\n");
    for (size_t i = 0; i < count; i++) {
        printf("- '%s'\n", command_names[i]);
    }
}

void partition(char *string, char *delim, char **first, char **second) {
    char *rest;

    *first = strtok_s(string, delim, &rest);
    if (*first == NULL) *first = "";

    // *second = strtok(NULL, "\n");
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

int exit_command(char *s) {
    printf("Exiting ...\n");
    return 1;
}

int main() {
    command *commands[COMMAND_COUNT] = {
        init, insert, remove_at, process_data, print, exit_command,
    };

    const char *command_names[COMMAND_COUNT] = {
        "init", "insert", "remove_at", "process_data", "print", "exit",
    };

    printf("Hello world!\n");
    print_commands(command_names, COMMAND_COUNT);

    while (1) {
        char string[STRMAX];
        char *command_name, *command_input;
        read_command(string, &command_name, &command_input);
        printf("'%s' '%s'\n", command_name, command_input);


        size_t command_index =
            match_command(command_names, COMMAND_COUNT, command_name);

        if (command_index == -1) {
            printf("Wrong input, try again!\n");
            print_commands(command_names, COMMAND_COUNT);
        } else {
            if (commands[command_index](command_input))
                break;
        }
    }
}
