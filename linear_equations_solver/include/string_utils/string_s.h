//
// Created by potato_coder on 07.02.23.
//

#ifndef COUNTMATHLAB1_STRING_S_H
#define COUNTMATHLAB1_STRING_S_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/printer.h"
#include "../containers/singly_linked_list.h"
#include <bits/types/FILE.h>

typedef struct string_builder string_builder;

string_builder *new_string_builder();

void string_builder_set_string(string_builder *string_builder, const char *new_string);

char *string_builder_get_string(string_builder *string_builder);

void string_builder_copy(string_builder *src, string_builder *dest);

void string_builder_destroy(void *builder);

bool string_builder_concat(string_builder *main, string_builder *from);

bool string_builder_equals(string_builder *builder_1, string_builder *builder_2);

linked_list* string_builder_get_token_list(string_builder *string, char *sep);

void string_builder_print_to(FILE *stream, enum printer_modes mode, void *arg);

void string_builder_println_to(FILE *stream, enum printer_modes mode, void *arg);

#endif //COUNTMATHLAB1_STRING_S_H
