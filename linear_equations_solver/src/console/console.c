//
// Created by potato_coder on 09.02.23.
//

#include "../../include/console/console.h"


/*
 * Идея: возможность считывания "псевдо-любого" количества символов.
 * Размер строки ограничен лишь размером максимального блока памяти,
 * который malloc() может выделить в оперативной памяти
 * Для этого есть обёртка string_builder, которая позволяет последовательно добавлять символы
 * из потока ввода.
 * */

string_builder *read_command(error_s *error) { //TODO "включить" обработку ошибок
    print(STRING, "Введите команду:");
    string_builder *command = new_string_builder();
    if (command == NULL) return NULL;//err
    string_builder *buffer = new_string_builder();
    if (buffer == NULL) return NULL;//err
    char *character = malloc(sizeof(char));
    if (character == NULL) {//err
        string_builder_destroy(command);
        string_builder_destroy(buffer);
        return NULL;
    }
    character[0] = getchar();
    while (character[0] == EOF) {
        println(STRING, "Некорректный ввод, попробуйте ввести команду ещё раз.");
        print(STRING, "Введите команду:");
        character[0] = getchar();
    }
    while (character[0] != '\0' && character[0] != '\n') {
        string_builder_set_string(buffer, character);
        string_builder_concat(command, buffer);
        character[0] = getchar();
    }
    string_builder_destroy(buffer);
    free(character);
    return command;
}

bool console(error_s *error) {
    string_builder *string_command = read_command(error);
    if (string_command == NULL) return false;//err
    linked_list *tokens_list = string_builder_get_token_list(string_command, " \t");
    //linked_list_print(stdout, STRING, tokens_list, string_builder_print_to);
    user_command *command;
    return true;
}