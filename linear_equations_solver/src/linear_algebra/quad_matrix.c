//
// Created by potato_coder on 09.02.23.
//

#include "../../include/linear_algebra/quad_matrix.h"


typedef struct quad_matrix {
    double **matrix;
    size_t size;
} quad_matrix;

quad_matrix *new_quad_matrix() {
    return (quad_matrix *) malloc(sizeof(quad_matrix));
}

void quad_matrix_init(quad_matrix *matrix, double **array, size_t size) {
    matrix->matrix = array;
    matrix->size = size;
}

double **quad_matrix_get_matrix(quad_matrix *matrix) {
    return matrix->matrix;
}

size_t quad_matrix_get_size(quad_matrix *matrix) {
    return matrix->size;
}

int64_t quad_matrix_swap_rows(quad_matrix *matrix, size_t first_row, size_t second_row, error_s *error) {
    if (matrix != NULL) {
        double **ptrs_array = matrix->matrix;
        double *buf = ptrs_array[first_row];
        ptrs_array[first_row] = ptrs_array[second_row];
        ptrs_array[second_row] = buf;
        return 1;
    } else {
        throw_exception(error, NULL_PTR_ERROR, "quad_matrix_swap_rows: передан null указатель.");
        return 0;
    }
}


void quad_matrix_print(quad_matrix *matrix) {
    double **m_array = matrix->matrix;
    for (size_t i = 0; i < matrix->size; i++) {
        for (size_t j = 0; j < matrix->size; j++) {
            printf("%lf ", m_array[i][j]);
        }
        printf("%s", "\n");
    }
}

int64_t quad_matrix_to_triangular_view(quad_matrix *matrix, error_s *error) {
    int64_t rows_swaps = 0;
    if (matrix != NULL) {
        double **m_array = matrix->matrix;
        println(STRING, "Прямой ход Гаусса:");
        for (size_t i = 0; i < matrix->size; i++) {
            for (size_t aboba = i + 1; (m_array[i][i]) == 0 && aboba < matrix->size; aboba++) {
                if (matrix->matrix[aboba][i] != 0) {
                    quad_matrix_swap_rows(matrix, i, aboba, error);
                }
            }
            double k;

            for (size_t row = i + 1; row < matrix->size; row++) {
                k = m_array[row][i] / m_array[i][i];
                for (size_t col = 0; col < matrix->size; col++) {
                    m_array[row][col] -= (k * m_array[i][col]);
                }
            }

            print(STRING, "\n");
            quad_matrix_print(matrix);
        }
    } else {
        throw_exception(error, NULL_PTR_ERROR, "quad_matrix_to_triangular_view: передан NULL указатель.");
    }
    return rows_swaps;
}

double quad_matrix_det_from_triangular_view(quad_matrix *matrix, int64_t rows_swaps) {
    double result = -1;
    for (size_t i = 0; i < matrix->size; i++) {

    }
    return result;
}

static void test2(quad_matrix *matrix, error_s *error) {
    double **m_array = matrix->matrix;
    println(STRING, "Прямой ход Гаусса:");
    for (size_t i = 0; i < matrix->size; i++) {
        for (size_t aboba = i + 1; (m_array[i][i]) == 0 && aboba < matrix->size; aboba++) {
            if (matrix->matrix[aboba][i] != 0) {
                quad_matrix_swap_rows(matrix, i, aboba, error);
            }
        }
        double k;

        for (size_t row = i + 1; row < matrix->size; row++) {
            k = m_array[row][i] / m_array[i][i];
            for (size_t col = 0; col < matrix->size; col++) {
                m_array[row][col] -= (k * m_array[i][col]);
            }
        }

        print(STRING, "\n");
        quad_matrix_print(matrix);
    }
}

void test(error_s *error) {
    quad_matrix *matrix = new_quad_matrix();

    double **m_array = malloc(sizeof(double) * 3);
    double first[3] = {10, -7, 0};
    double second[3] = {-3, 2, 6};
    double third[3] = {5, -1, 5};

    m_array[0] = first;
    m_array[1] = second;
    m_array[2] = third;

    quad_matrix_init(matrix, m_array, 3);
    quad_matrix_print(matrix);

    print(STRING, "\n");

    quad_matrix_to_triangular_view(matrix, error);
    free(m_array);
}

/*
double matrix_determinant(quad_matrix* quad_matrix, error_s* error){
    double result = 0;
    if(quad_matrix != NULL){
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
    quad_matrix quad_matrix;
} matrix_2d;

matrix_2d *new_matrix_2d() {
    return (matrix_2d *) malloc(sizeof(matrix_2d));
}
*/




