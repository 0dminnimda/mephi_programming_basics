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
        init_command,         insert_command, remove_command,
        process_data_command, print_command,  exit_command,
    };
    const char *command_names[COMMAND_COUNT] = {
        "init", "insert", "remove", "process_data", "print", "exit",
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
        char command[STRMAX], input[STRMAX];
        scanf_s("%[^ \n]", command, STRMAX);
        fgets(input, STRMAX, stdin);  // consume the rest of the line

        size_t index = match_command(command_names, COMMAND_COUNT, command);

        if (index == -1) {
            printf("Wrong input, try again!\n");
            print_commands(command_names, COMMAND_COUNT);
        } else {
            if (commands[index](input, vec)) break;
        }
    }

    printf("destroy\n");
    destroy_vector(vec);

    return 0;
}
