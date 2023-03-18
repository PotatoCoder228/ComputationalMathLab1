//
// Created by potato_coder on 06.02.23.
//
#include "../../include/io/io_handler.h"

void open_file(FILE **stream, char *filename, enum open_file_modes mode, error_s *error) {
    *stream = fopen(filename, open_file_modes[mode]);
    if (*stream == NULL) {
        error_set_code(error, -1);
        fprintf(stderr, "%s\n", strerror(errno));
    } else {
        error_set_default(error);
    }
}

void close_file(FILE **stream, error_s *error) {
    int status = fclose(*stream);
    if (status) {
        throw_exception(error, errno, strerror(errno));
    } else {
        error_set_default(error);
    }
}