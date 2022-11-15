#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "vector.h"

#define COMMAND_COUNT 7
#define STRMAX 256

void print_one_command(command_t *command, char *command_name, int verbose) {
    printf("- '%s'", command_name);
    if (verbose) {
        printf(": ");
        command("   ", NULL, 1);
    }
}

void print_commands(command_t *commands[], char *command_names[], size_t count,
                    int verbose) {
    printf("Available commands:\n");
    if (verbose) printf("\n");
    for (size_t i = 0; i < count; i++) {
        print_one_command(commands[i], command_names[i], verbose);
        printf("\n");
    }
}

size_t match_command(char *command_names[], size_t count,
                     const char *command_name) {
    for (size_t i = 0; i < count; i++)
        if (strcmp(command_name, command_names[i]) == 0) return i;

    return -1;
}

int exit_command(char *str, Vector vec, int help) {
    if (help) {
        printf("Cleans up and stops the program\n");
        printf("%sUse: exit\n", str);
        return 0;
    }

    printf("Exiting ...\n");
    return 1;
}

int help_command(char *str, Vector vec, int help) {
    if (help) {
        printf("Prints information about commands\n");
        printf("%sUse: help [command]\n", str);
        printf("%sExample: help print\n", str);
        return 0;
    }
    return 0;
}

void help(char *str, command_t *commands[], char *command_names[],
          size_t count) {
    char command_name[STRMAX] = "";
    int found = sscanf(str, " %[^ \n]", command_name);

    if (found == 1) {
        size_t i = match_command(command_names, count, command_name);

        if (i == -1) {
            printf("Nothing matches '%s', try again!\n", command_name);
        } else {
            print_one_command(commands[i], command_name, 1);
        }
    } else {  // if (found == 0) {
        print_commands(commands, command_names, count, 1);
    }
    // else {
    //     printf("Incorrect input, expected command (string) or nothing\n");
    // }
}

int main() {
    command_t *commands[COMMAND_COUNT] = {
        init_command,  insert_command, remove_command, process_command,
        print_command, exit_command,   help_command,
    };
    char *command_names[COMMAND_COUNT] = {
        "init", "insert", "remove", "process", "print", "exit", "help",
    };

    printf("Hello, fellow user!\n");
    help("\n", commands, command_names, COMMAND_COUNT);

    Vector vec;
    if (create(&vec, 0)) {
        printf("Could not create a Vector\n");
        return -1;
    }

    while (1) {
        printf(">>> ");
        char command_name[STRMAX], input[STRMAX];
        scanf("%[^ \n]", command_name);
        fgets(input, STRMAX, stdin);  // consume the rest of the line

        if (strcmp(command_name, "help") == 0)
            help(input, commands, command_names, COMMAND_COUNT);

        size_t i = match_command(command_names, COMMAND_COUNT, command_name);

        if (i == -1) {
            printf("Wrong input, try again!\n");
            print_commands(commands, command_names, COMMAND_COUNT, 0);
        } else {
            if (commands[i](input, vec, 0)) break;
        }
    }

    destroy_vector(vec);

    return 0;
}
