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

string_builder *read_line(FILE *stream, error_s *error) {
    if (stream == NULL) {
        throw_exception(error, NULL_PTR_ERROR, "read_line: передан NULL указатель на FILE*.");
        return NULL;
    }
    string_builder *line = new_string_builder();
    if (line == NULL) {
        throw_exception(error, MEM_ALLOC_DENIED, "read_line: недостаточно памяти для выделения под line.");
        return NULL;
    }
    string_builder *buffer = new_string_builder();
    if (buffer == NULL) {
        throw_exception(error, MEM_ALLOC_DENIED, "read_line: недостаточно памяти для выделения под buffer.");
        return NULL;//err
    }
    char *character = malloc(sizeof(char) * 2);
    if (character == NULL) {//err
        throw_exception(error, MEM_ALLOC_DENIED, "read_line: недостаточно памяти для выделения под character.");
        string_builder_destroy(line);
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
        if (string_builder_concat(line, buffer)) {
            character[0] = fgetc(stream);
        } else {
            throw_exception(error, MEM_ALLOC_DENIED, "read_line: недостаточно памяти для выделения.");
        }
    }
    string_builder_destroy(buffer);
    free(character);
    character = NULL;
    return line;
}

bool console(error_s *error) {
    double k = 1;
    double a = 0.8999999999999999999999999999999999999999995;
    printf("\n%.51F\n", k-a);
    printf("\n%.128F\n", a);
    while (true) {
        print(STRING, "\nВведите команду:");
        help_list_init(error);
        string_builder *string_command = read_line(stdin, error);
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