//
// Created by potato_coder on 09.02.23.
//

#include <stdint-gcc.h>
#include "../../include/linear_algebra/lin_eq_solver.h"
#include "../../include/linear_algebra/matrix.h"

static double num_pow(int64_t num, int64_t k) {
    for (int64_t i = 0; i < k; i++) {
        num *= num;
    }
    return (double) num;
}

int64_t matrix_to_triangular_view(matrix *matrix, error_s *error) {
    int64_t rows_swaps = 0;
    if (matrix != NULL) {
        double **m_array = matrix_get_matrix(matrix);;
        println(STRING, "Прямой ход Гаусса:");
        for (size_t i = 0; i < matrix_get_rows(matrix); i++) {
            for (size_t aboba = i + 1; (m_array[i][i]) == 0 && aboba < matrix_get_rows(matrix); aboba++) {
                if (m_array[aboba][i] != 0) {
                    matrix_swap_rows(matrix, i, aboba, error);
                    rows_swaps++;
                }
            }
            double k;

            for (size_t row = i + 1; row < matrix_get_rows(matrix); row++) {
                k = m_array[row][i] / m_array[i][i];
                for (size_t col = 0; col < matrix_get_columns(matrix); col++) {
                    m_array[row][col] -= (k * m_array[i][col]);
                }
            }

            print(STRING, "\n");
            matrix_print(matrix);
        }
    } else {
        throw_exception(error, NULL_PTR_ERROR, "matrix_to_triangular_view: передан NULL указатель.");
    }
    return rows_swaps;
}


double matrix_det_from_triangular_view(matrix *matrix, int64_t rows_swaps, error_s *error) {
    double result = num_pow(-1, rows_swaps);
    if (matrix != NULL) {
        double **m_array = matrix_get_matrix(matrix);
        for (size_t i = 0; i < matrix_get_rows(matrix); i++) {
            result *= m_array[i][i];
        }
    } else {
        throw_exception(error, NULL_PTR_ERROR, "matrix_det_from_triangular_view: передан NULL указатель.");
    }
    return result;
}

void test(error_s *error) {
    matrix *matrix = new_matrix();

    double **m_array = malloc(sizeof(double) * 3);
    double first[4] = {10, -7, 0, 7};
    double second[4] = {-3, 2, 6, 4};
    double third[4] = {5, -1, 5, 6};

    m_array[0] = first;
    m_array[1] = second;
    m_array[2] = third;

    matrix_init(matrix, m_array, 3, 4);
    matrix_print(matrix);

    print(STRING, "\n");

    int64_t k = matrix_to_triangular_view(matrix, error);
    double det = matrix_det_from_triangular_view(matrix, k, error);
    printf("%s: %lf\n", "Детерминант", det);
    free(m_array);
}
