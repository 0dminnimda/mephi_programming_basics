#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "commands.h"

#define COMMAND_COUNT 5

void greet() {
    printf("Hello world!\n");
}

void print_commands(const char *command_names[], size_t count) {
    printf("Available commands:\n");
    for (size_t i = 0; i < count; i++) {
        printf("- '%s'\n", command_names[i]);
    }
}

void incorrect_input(const char *command_names[], size_t count) {
    printf("Wrong input, try again!\n");
    print_commands(command_names, count);
}

void partition(char *string, char **first, char **second) {
    *first = strtok(string, " \n");
    if (*first == NULL)
        *first = "";
    *second = strtok(NULL, "\n");
    if (*second == NULL)
        *second = "";
}

char *read() {
    size_t len = 0;
    char *result = NULL;
    getline(&result, &len, stdin);
    return result;
}

ssize_t match_command(const char *command_names[], size_t count,
                  const char *command_name) {
    for (size_t i = 0; i < count; i++)
        if (strcmp(command_name, command_names[i]) == 0) return i;

    return -1;
}

int main() {
    command *commands[COMMAND_COUNT] = {
        init, insert, remove_at, process_data, print,
    };
    const char *command_names[COMMAND_COUNT] = {
        "init", "insert", "remove_at", "process_data", "print",
    };

    char *exit_command_name = "exit";

    greet();
    print_commands(command_names, COMMAND_COUNT);

    while (1) {
        char *command_name, *command_input;
        partition(read(), &command_name, &command_input);
        printf("'%s' '%s'\n", command_name, command_input);

        if (strcmp(command_name, exit_command_name) == 0) break;

        ssize_t command_index =
            match_command(command_names, COMMAND_COUNT, command_name);

        if (command_index == -1)
            incorrect_input(command_names, COMMAND_COUNT);
        else
            commands[command_index](command_input);
    }
}
