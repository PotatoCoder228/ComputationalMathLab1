//
// Created by potato_coder on 09.02.23.
//

#include "../../include/command/command.h"
#include "../../include/console/console.h"

linked_list *commands_list;

typedef struct user_command {
    char *description;

    void (*callback)(error_s *error);
} user_command;


user_command *new_user_command(void callback(error_s *), char *descr) {
    user_command *command = malloc(sizeof(user_command));
    if (command != NULL) {
        command->callback = callback;
        command->description = descr;
    }
    return command;
}


void *user_command_get_callback(user_command *command) {
    return command->callback;
}

void user_command_set_callback(user_command *command, void callback(error_s *)) {
    command->callback = callback;
}

char *user_command_get_description(user_command *command) {
    return command->description;
}

void user_command_set_description(user_command *command, char *description) {
    command->description = description;
}

void user_command_destroy(user_command *command) {
    free(command);
}

void print_commands_help() {
    linked_list *buffer = commands_list;
    printf("\nСправка по командам:\n");
    while (buffer != NULL) {
        printf("%s\n", ((user_command *) linked_list_get_node_value(buffer))->description);
        buffer = linked_list_get_node_next(buffer);
    }
}

void help_command(error_s *error) {
    print_commands_help();
}

void script_command(error_s *error) {
    print(STRING, "Введите имя файла:");
    string_builder *arg = read_string(error);
    if (arg == NULL) {
        throw_exception(error, INPUT_STREAM_READ_ERROR, "script_command: Не удалось прочитать строку.");
    }
    print(STRING, "Выполнение вычислений с чтением из файла ");
    string_builder_print_to(stdout, STRING, arg);
}

void exit_command(error_s *error) {
    println(STRING, "Производится выход из программы...");
}

void undefined_command(error_s *error) {
    printf("%s%s", "\nНекорректная команда, попробуйте ввести ещё раз!\n", "help - справка по командам\n");
}

void run_command(user_command *command, error_s *error) {
    void (*command_call)(error_s *) = command->callback;
    command_call(error);
}

user_command *get_user_command_from_list(linked_list *tokens) {
    user_command *user_command = new_user_command(NULL, NULL);
    string_builder *command = linked_list_get_node_value(tokens);
    if (!strcmp(string_builder_get_string(command), "help")) {
        user_command_set_callback(user_command, help_command);
    } else if (!strcmp(string_builder_get_string(command), "script")) {
        user_command_set_callback(user_command, script_command);
    } else if (!strcmp(string_builder_get_string(command), "exit")) {
        user_command_set_callback(user_command, exit_command);
    } else {
        user_command_set_callback(user_command, undefined_command);
    }
    return user_command;
}

void help_list_init(error_s *error) {
    user_command *command_help = new_user_command(help_command, (void *) descriptions[HELP]);
    if (command_help == NULL) {
        throw_exception(error, MEM_ALLOC_DENIED,
                        "help_list_init: Не удалось выделить память для инициализации справки.");
        return;
    }
    user_command *command_script = new_user_command(script_command, (void *) descriptions[SCRIPT]);
    if (command_script == NULL) {
        user_command_destroy(command_help);
        throw_exception(error, MEM_ALLOC_DENIED,
                        "help_list_init: Не удалось выделить память для инициализации справки.");
        return;
    }
    user_command *command_exit = new_user_command(exit_command, (void *) descriptions[EXIT]);

    if (command_exit == NULL) {
        user_command_destroy(command_help);
        user_command_destroy(command_script);
        throw_exception(error, MEM_ALLOC_DENIED,
                        "help_list_init: Не удалось выделить память для инициализации справки.");
        return;
    }

    commands_list = linked_list_init(command_help, 0);
    if (commands_list == NULL) {
        user_command_destroy(command_help);
        user_command_destroy(command_script);
        user_command_destroy(command_exit);
        throw_exception(error, MEM_ALLOC_DENIED,
                        "help_list_init: Не удалось выделить память для инициализации справки.");
        return;
    }
    linked_list_push(commands_list, command_script, 0);
    linked_list_push(commands_list, command_exit, 0);
}

void help_list_destroy() {
    linked_list_destroy(commands_list, free);
}