//
// Created by potato_coder on 07.02.23.
//

#ifndef COUNTMATHLAB1_STRING_S_H
#define COUNTMATHLAB1_STRING_S_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct string_builder string_builder;

string_builder *new_string_builder();

void string_builder_set_string(string_builder *string_builder, const char *new_string);

char *string_builder_get_string(string_builder *string_builder);

void string_builder_copy(string_builder *src, string_builder *dest);

void string_builder_destroy(string_builder *builder);

bool string_builder_concat(string_builder *main, string_builder *from);

#endif //COUNTMATHLAB1_STRING_S_H
