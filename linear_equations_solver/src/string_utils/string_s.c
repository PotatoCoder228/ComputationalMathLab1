//
// Created by potato_coder on 07.02.23.
//

#include <errno.h>
#include "../../include/string_utils/string_s.h"

typedef struct string_builder {
    char *string;
    size_t size;
} string_builder;

string_builder *new_string_builder() {
    string_builder *builder = malloc(sizeof(string_builder));
    if (builder != NULL) {
        builder->string = malloc(sizeof(char));
        (builder->string)[0] = '\0';
        builder->size = strlen(builder->string);
    } else {
        printf("%s", strerror(errno));
    }
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

void string_builder_copy(string_builder *src, string_builder *dest) {
    if (src != NULL && dest != NULL && ((src->size) == (dest->size))) {
        strcpy(dest->string, src->string);
    }
}

bool string_builder_concat(string_builder *main, string_builder *from) {
    if (main != NULL && from != NULL) {
        main->string = realloc(main->string, (main->size) + (from->size) + 1);
        if (main->string != NULL) {
            strcat(main->string, from->string);
            main->size = strlen(main->string);
            return true;
        }
        return false;
    }
    return false;
}

void string_builder_destroy(void *builder) {
    free(string_builder_get_string((string_builder *) builder));
    free((string_builder *) builder);
}

bool string_builder_equals(string_builder *builder_1, string_builder *builder_2) {
    if (strcmp(builder_1->string, builder_2->string) != 0) {
        return false;
    }
    return true;
}

linked_list *string_builder_get_token_list(string_builder *string, char *sep, size_t counts) {
    if (string == NULL) {
        return NULL;
    }
    linked_list *result = NULL;
    char *buf;
    string_builder *token;
    buf = strtok(string->string, sep);
    for (size_t i = 0; (i < counts) && buf != NULL; i++) {
        token = new_string_builder();
        if (token == NULL) {
            return NULL;
        }
        string_builder_set_string(token, buf);
        if (i == 0) {
            result = linked_list_init(token, 1);
            if (result == NULL) {
                string_builder_destroy(token);
                return NULL;
            }
            buf = strtok(NULL, sep);
        } else {
            linked_list_push(result, token, 1);
            buf = strtok(NULL, sep);
        }
    }
    return result;
}


void string_builder_print_to(FILE *stream, enum printer_modes mode, void *arg) {
    print_to(stream, mode, ((string_builder *) arg)->string);
}

void string_builder_println_to(FILE *stream, enum printer_modes mode, void *arg) {
    println_to(stream, mode, ((string_builder *) arg)->string);
}