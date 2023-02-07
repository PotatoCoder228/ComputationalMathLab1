//
// Created by potato_coder on 07.02.23.
//

#ifndef COUNTMATHLAB1_EXCEPTIONS_H
#define COUNTMATHLAB1_EXCEPTIONS_H

#include "../string_utils/string_s.h"
#include <stdlib.h>
#include <stdio.h>
#include <values.h>
#include "../../include/utils/printer.h"

typedef struct error_s error_s;

error_s *new_error();

void error_set_message(error_s *error, string_builder *message);

string_builder *error_get_message(error_s *error);

void error_set_code(error_s *error, int code);

int error_get_code(error_s *error);

void error_print_to(FILE *stream, error_s *error);

void throw_exception(error_s *error, int code, char *message);

void error_destroy(error_s *error);

void error_set_default(error_s *error);

#endif //COUNTMATHLAB1_EXCEPTIONS_H
