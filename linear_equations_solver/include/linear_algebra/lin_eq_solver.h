//
// Created by potato_coder on 09.02.23.
//

#ifndef COUNTMATHLAB1_LIN_EQ_SOLVER_H
#define COUNTMATHLAB1_LIN_EQ_SOLVER_H

#include "matrix.h"

enum equation_error {
    DET_IS_EQ_ZERO = 1000
};

int64_t matrix_to_triangular_view(matrix *matrix, error_s *error);

double matrix_det_from_triangular_view(matrix *matrix, int64_t rows_swaps, error_s *error);

void gauss_method_inverse(matrix *matrix, double *results, error_s *error);

void matrix_destroy(matrix *matrix);

void print_SLAE(matrix *matrix);

void print_double(double k);

#endif //COUNTMATHLAB1_LIN_EQ_SOLVER_H
//matrix_get_matrix(matrix);
//matrix_get_rows(matrix);
//matrix_get_columns(matrix);