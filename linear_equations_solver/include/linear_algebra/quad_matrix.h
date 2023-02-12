//
// Created by potato_coder on 09.02.23.
//

#ifndef COUNTMATHLAB1_QUAD_MATRIX_H
#define COUNTMATHLAB1_QUAD_MATRIX_H

#include <stdlib.h>
#include "../../include/exceptions/exceptions.h"

typedef struct quad_matrix quad_matrix;
//typedef struct matrix_2d matrix_2d;

void quad_matrix_init(quad_matrix *matrix, double **array, size_t quad);

quad_matrix *new_quad_matrix();

double quad_matrix_determinant(quad_matrix *matrix, error_s *error);

void test(error_s *error);


#endif //COUNTMATHLAB1_QUAD_MATRIX_H
