//
// Created by potato_coder on 07.02.23.
//

#include "../../include/string_utils/string_s.h"

typedef struct string_builder {
    char *string;
    size_t size;
} string_builder;

string_builder *new_string_builder() {
    string_builder *builder = malloc(sizeof(string_builder));
    return builder;
}

void string_builder_set_string(string_builder *string_builder, const char *new_string) {
    if (string_builder != NULL) {
        size_t size = strlen(new_string);
        if (string_builder->string == NULL) {
            string_builder->string = malloc(sizeof(char) * size);
            if (string_builder->string != NULL) {
                string_builder->size = size;
            }
        } else {
            string_builder->string = realloc(string_builder->string, sizeof(char) * size);
            if (string_builder->string != NULL) {
                string_builder->size = size;
            }
        }
        strcpy(string_builder->string, new_string);
    }
}

char *string_builder_get_string(string_builder *string_builder) {
    if (string_builder == NULL) {
        return NULL;
    }
    return string_builder->string;
}

//TODO доделать API для работы со строками
void string_builder_copy(string_builder *src, string_builder *dest) {
    if (src != NULL && dest != NULL && ((src->size) == (dest->size))) {
        strcpy(dest->string, src->string);
    }
}

bool string_builder_concat(string_builder *main, string_builder *from) {
    if (main != NULL && from != NULL) {
        if (main->size != 0 && from->size != 0) {
            main->string = realloc(main->string, (main->size) + (from->size));
            if (main->string != NULL) {
                strcat(main->string, from->string);
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

void string_builder_destroy(string_builder *builder) {
    free(string_builder_get_string(builder));
    free(builder);
}

bool string_builder_equals(string_builder *builder_1, string_builder *builder_2) {
    if (strcmp(builder_1->string, builder_2->string) != 0) {
        return false;
    }
    return true;
}