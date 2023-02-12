//
// Created by potato_coder on 09.02.23.
//

#ifndef COUNTMATHLAB1_LIN_EQ_SOLVER_H
#define COUNTMATHLAB1_LIN_EQ_SOLVER_H

#include "matrix.h"

int64_t matrix_to_triangular_view(matrix *matrix, error_s *error);

double matrix_det_from_triangular_view(matrix *matrix, int64_t rows_swaps, error_s *error);

void test(error_s *error);

#endif //COUNTMATHLAB1_LIN_EQ_SOLVER_H
//matrix_get_matrix(matrix);
//matrix_get_rows(matrix);
//matrix_get_columns(matrix);