#include <stdlib.h>

#include "commands.h"

#define COMMAND_COUNT 5

void greet() {}
void print_commands(const char *command_names[], size_t count) {}
void incorrect_input(const char *command_names[], size_t count) {}
void partition(const char *string, char **first, char **second) {}
int match_command(const char *command_names[], size_t count,
                  const char *command_name) {
    for (int i = 0; i < count; i++)
        if (command_name == command_names[i]) return i;

    return -1;
}

int main() {
    command *commands[COMMAND_COUNT] = {
        init, insert, remove_at, process_data, print,
    };
    char *command_names[COMMAND_COUNT] = {
        "init", "insert", "remove_at", "process_data", "print",
    };

    char *exit_command_name = "exit";

    greet();

    while (1) {
        print_commands(command_names, COMMAND_COUNT);

        char *command_name, command_input;
        partition(getline(), &command_name, &command_input);

        if (command_name == exit_command_name) break;

        int command_index =
            match_command(command_names, COMMAND_COUNT, command_name);

        if (command_index == -1)
            incorrect_input(command_names, COMMAND_COUNT);
        else
            commands[command_index](command_input);
    }
}
