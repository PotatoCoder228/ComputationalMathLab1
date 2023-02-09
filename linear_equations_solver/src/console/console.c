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
string_builder *read_command(error_s* error) { //TODO "включить" обработку ошибок
    string_builder* command = new_string_builder();
    string_builder* buffer = new_string_builder();
    char *character = malloc(sizeof(char));
    character[0] = getchar();
    while (character[0] != EOF && character[0] != '\n') {
        string_builder_set_string(buffer, character);
        string_builder_concat(command, buffer);
        character[0] = getchar();
    }
    string_builder_destroy(buffer);
    free(character);
    return command;
}

bool console(error_s* error){
    string_builder* command = read_command(error);
    return true;
}