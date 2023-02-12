//
// Created by potato_coder on 09.02.23.
//

#ifndef COUNTMATHLAB1_MATRIX_H
#define COUNTMATHLAB1_MATRIX_H

#include <stdlib.h>
#include "../../include/exceptions/exceptions.h"

typedef struct matrix matrix;
//typedef struct matrix_2d matrix_2d;

void matrix_init(matrix *matrix, double **array, size_t rows, size_t columns);

matrix *new_matrix();

double **matrix_get_matrix(matrix *matrix);

size_t matrix_get_rows(matrix *matrix);

size_t matrix_get_columns(matrix *matrix);

int64_t matrix_swap_rows(matrix *matrix, size_t first_row, size_t second_row, error_s *error);

void matrix_print(matrix *matrix);

#endif //COUNTMATHLAB1_MATRIX_H
