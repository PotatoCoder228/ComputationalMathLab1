//
// Created by potato_coder on 09.02.23.
//

#include "../../include/command/command.h"

linked_list *commands_list;

typedef struct user_command {
    char *description;

    void (*callback)(void *arg);

    char *arg;
} user_command;


user_command *new_user_command(void callback(void *), char *arg, char *descr) {
    user_command *command = malloc(sizeof(user_command));
    command->callback = callback;
    command->arg = arg;
    command->description = descr;
    return command;
}


void *user_command_get_callback(user_command *command) {
    return command->callback;
}

void user_command_set_callback(user_command *command, void callback(void *)) {
    command->callback = callback;
}

void *user_command_get_arg(user_command *command) {
    return command->arg;
}

void user_command_set_arg(user_command *command, void *arg) {
    command->arg = arg;
}

char *user_command_get_description(user_command *command) {
    return command->description;
}

void user_command_set_description(user_command *command, char *description) {
    command->description = description;
}

void user_command_destroy(user_command *command) {
    //
}

void print_commands_help() {
    linked_list *buffer = commands_list;
    printf("\nСправка по командам:\n");
    while (buffer != NULL) {
        printf("%s\n", ((user_command *) linked_list_get_node_value(buffer))->description);
        buffer = linked_list_get_node_next(buffer);
    }
}

void help_command(void *arg) {
    print_commands_help();
}

void script_command(void *arg) {

}

void undefined_command(void *arg) {
    printf("%s%s", "\nНекорректная команда, попробуйте ввести ещё раз!\n", "help - справка по командам\n");
}

void run_command(user_command *command) {
    void (*command_call)(void *arg) = command->callback;
    command_call(command->arg);
}

user_command *get_user_command_from_list(linked_list *tokens) {
    user_command *user_command = new_user_command(NULL, NULL, NULL);
    string_builder *command = linked_list_get_node_value(tokens);
    if (!strcmp(string_builder_get_string(command), "help")) {
        user_command_set_callback(user_command, help_command);
    } else if (!strcmp(string_builder_get_string(command), "script")) {
        user_command_set_callback(user_command, script_command);
    } else {
        user_command_set_callback(user_command, undefined_command);
    }
    return user_command;
}

void help_list_init() {
    user_command *command_help = new_user_command(help_command, NULL, (void *) descriptions[HELP]);
    user_command *command_script = new_user_command(script_command, NULL, (void *) descriptions[SCRIPT]);
    user_command *command_exit = new_user_command(NULL, NULL, (void *) descriptions[EXIT]);

    commands_list = linked_list_init(command_help, 1);
    linked_list_push(commands_list, command_script, 1);
    linked_list_push(commands_list, command_exit, 1);
}