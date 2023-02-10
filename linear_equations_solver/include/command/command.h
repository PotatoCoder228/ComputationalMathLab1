//
// Created by potato_coder on 09.02.23.
//

#ifndef COUNTMATHLAB1_COMMAND_H
#define COUNTMATHLAB1_COMMAND_H

#include <stdlib.h>
#include <stdint.h>
#include "../containers/singly_linked_list.h"
#include "../../include/string_utils/string_s.h"

enum commands {
    HELP = 0,
    EXIT,
    SCRIPT
};

static const char *descriptions[6] = {
        "help - Выводит справку по командам",
        "exit - Выход из приложения",
        "script <filename> - Выполнение скрипта из файла."
};

typedef struct user_command user_command;

user_command *new_user_command(void callback(void *), char *arg, char *descr);

void *user_command_get_callback(user_command *command);

void user_command_set_callback(user_command *command, void callback(void *));

void *user_command_get_arg(user_command *command);

void user_command_set_arg(user_command *command, void *arg);

char *user_command_get_description(user_command *command);

void user_command_set_description(user_command *command, char *description);

void user_command_destroy(user_command *command);

void run_command(user_command *command);


#endif //COUNTMATHLAB1_COMMAND_H
