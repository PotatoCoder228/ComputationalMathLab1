//
// Created by potato_coder on 09.02.23.
//

#include "../../include/linear_algebra/matrix.h"


typedef struct matrix {
    double **matrix;
    size_t rows;
    size_t columns;
} matrix;

matrix *new_matrix() {
    return (matrix *) malloc(sizeof(matrix));
}

void matrix_init(matrix *matrix, double **array, size_t rows, size_t columns) {
    matrix->matrix = array;
    matrix->rows = rows;
    matrix->columns = columns;
}

double **matrix_get_matrix(matrix *matrix) {
    return matrix->matrix;
}

size_t matrix_get_rows(matrix *matrix) {
    return matrix->rows;
}

size_t matrix_get_columns(matrix *matrix) {
    return matrix->columns;
}

int64_t matrix_swap_rows(matrix *matrix, size_t first_row, size_t second_row, error_s *error) {
    if (matrix != NULL) {
        double **ptrs_array = matrix->matrix;
        double *buf = ptrs_array[first_row];
        ptrs_array[first_row] = ptrs_array[second_row];
        ptrs_array[second_row] = buf;
        return 1;
    } else {
        throw_exception(error, NULL_PTR_ERROR, "matrix_swap_rows: передан null указатель.");
        return 0;
    }
}


void matrix_print(matrix *matrix) {
    double **m_array = matrix->matrix;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->columns; j++) {
            printf("%lf ", m_array[i][j]);
        }
        printf("%s", "\n");
    }
}

void matrix_destroy(matrix *matrix) {
    free(matrix);
}

/*
double matrix_determinant(matrix* matrix, error_s* error){
    double result = 0;
    if(matrix != NULL){
        //TODO после
    }
    else{
        throw_exception(error, NULL_PTR_ERROR, "matrix_determinant: передан NULL указатель.");
    }
    return result;
}
*/


/*
typedef struct matrix_2d {
    matrix matrix;
} matrix_2d;

matrix_2d *new_matrix_2d() {
    return (matrix_2d *) malloc(sizeof(matrix_2d));
}
*/




