#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "commands.h"

#define COMMAND_COUNT 5

void greet() {}
void print_commands(const char *command_names[], size_t count) {}
void incorrect_input(const char *command_names[], size_t count) {}

void partition(char *string, char **first, char **second) {
    *first = strtok(string, " ");
    *second = strtok(NULL, "");
    return;
    
    int second_start = -1;
    int state = 0;
    int i = 0;
    while (string[i] != '\0') {
        if (state == 0 && string[i] == ' ') {
            string[i] = '\0';
            printf("%d\n", string[i] == '\0');
            second_start = i;
            state = 1;
        } else if (state == 1 && string[i] != ' ') {
            second_start = i;
            break;
        }
       // putc(string[i], stdout);
        i++;
    }
    *first = string;
    *second = (string + second_start);
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
        if (command_name == command_names[i]) return i;

    return -1;
}

int main() {
    command *commands[COMMAND_COUNT] = {
        init, insert, remove_at, process_data, print,
    };
    const char *command_names[COMMAND_COUNT] = {
        "init", "insert", "remove_at", "process_data", "print",
    };

    char *first, *second;
    char ss[] = "1234  5678 9012";
    /*printf("gg\n");
    first = strtok(ss, " ");
    printf("hh\n");
    second = strtok(NULL, "");
    printf("ss\n");*/
    partition(ss, &first, &second);
    //ss[4] = '\0';
    /*for (int i = 0; i < 16; i ++) {
        if (first[i] == '\0')
            putc('|', stdout);
        else
            putc(first[i], stdout);
    }*/
    printf("'%s' '%s'\n", first, second);
    return 0;

    char *exit_command_name = "exit";

    greet();

    while (1) {
        print_commands(command_names, COMMAND_COUNT);

        char *command_name, *command_input;
        partition(read(), &command_name, &command_input);

        if (command_name == exit_command_name) break;

        ssize_t command_index =
            match_command(command_names, COMMAND_COUNT, command_name);

        if (command_index == -1)
            incorrect_input(command_names, COMMAND_COUNT);
        else
            commands[(size_t)command_index](command_input);
    }
}
