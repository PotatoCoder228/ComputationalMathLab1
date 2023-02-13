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

string_builder *read_string(FILE *stream, error_s *error) {
    string_builder *command = new_string_builder();
    if (command == NULL) {
        throw_exception(error, MEM_ALLOC_DENIED, "read_string: недостаточно памяти для выделения под command.");
        return NULL;
    }
    string_builder *buffer = new_string_builder();
    if (buffer == NULL) {
        throw_exception(error, MEM_ALLOC_DENIED, "read_string: недостаточно памяти для выделения под buffer.");
        return NULL;//err
    }
    char *character = malloc(sizeof(char) * 2);
    if (character == NULL) {//err
        throw_exception(error, MEM_ALLOC_DENIED, "read_string: недостаточно памяти для выделения под character.");
        string_builder_destroy(command);
        string_builder_destroy(buffer);
        return NULL;
    }
    character[0] = fgetc(stream);
    character[1] = '\0';
    while (character[0] == EOF && stream == stdin) {
        print(STRING, "Некорректный ввод, попробуйте ввести ещё раз:");
        character[0] = fgetc(stream);
    }
    while (character[0] != '\0' && character[0] != '\n' && feof(stream) == 0) {
        string_builder_set_string(buffer, character);
        string_builder_concat(command, buffer);
        character[0] = fgetc(stream);
    }
    string_builder_destroy(buffer);
    free(character);
    return command;
}

bool console(error_s *error) {
    while (true) {
        print(STRING, "\nВведите команду:");
        help_list_init(error);
        string_builder *string_command = read_string(stdin, error);
        if (string_command == NULL) {
            throw_exception(error, MEM_ALLOC_DENIED, "concole(): недостаточно места для создания структуры");
            return false;
        }
        linked_list *tokens_list = string_builder_get_token_list(string_command, " \t", 1);
        if (tokens_list == NULL) {
            println(STRING, "\nВы не ввели команду!\n");
            string_builder_destroy(string_command);
            continue;
        }
        user_command *command = get_user_command_from_list(tokens_list);
        if (user_command_get_callback(command) == exit_command) {
            run_command(command, error);
            linked_list_destroy(tokens_list, string_builder_destroy);
            string_builder_destroy(string_command);
            break;
        } else {
            run_command(command, error);
        }
        string_builder_destroy(string_command);
    }
    help_list_destroy();
    return true;
}