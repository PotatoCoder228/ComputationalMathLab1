//
// Created by potato_coder on 09.02.23.
//

#include "../../include/linear_algebra/lin_eq_solver.h"

void print_double(double k) {
    if(k<0.000001&&k>-0.000001){
        k=0.0;
    }
    printf("%10lF ", k);
}

void print_SLAE(matrix *matrix) {
    double **m_array = matrix_get_matrix(matrix);
    for (size_t i = 0; i < matrix_get_rows(matrix); i++) {
        for (size_t j = 0; j < matrix_get_columns(matrix); j++) {
            if (j == matrix_get_columns(matrix) - 1) {
                print(STRING, "|");
            }
            print_double(m_array[i][j]);
        }
        print(STRING, "\n");
    }
}

static double num_pow(int64_t num, int64_t k) {
    if (k == 0) {
        return 1;
    }
    for (int64_t i = 1; i < k; i++) {
        num *= num;
    }
    return (double) num;
}

int64_t matrix_to_triangular_view(matrix *matrix, error_s *error) {
    int64_t rows_swaps = 0;
    if (matrix != NULL) {
        double **m_array = matrix_get_matrix(matrix);
        for (size_t i = 0; i < matrix_get_rows(matrix); i++) {
            double buf = m_array[i][i];
            for (size_t aboba = i + 1; (m_array[i][i]) == 0 && aboba < matrix_get_rows(matrix); aboba++) {
                if (m_array[aboba][i] != 0) {
                    matrix_swap_rows(matrix, i, aboba, error);
                    rows_swaps++;
                }
            }
            if (buf == m_array[i][i] && buf == 0) {
                throw_exception(error, -1,
                                "Детерминант равен 0!\nСЛАУ имеет бесконечное множество решений или не имеет вовсе!\n");
                return 0;
            }
            double k;
            for (size_t row = i + 1; row < matrix_get_rows(matrix); row++) {
                k = m_array[row][i] / m_array[i][i];
                for (size_t col = 0; col < matrix_get_columns(matrix); col++) {
                    m_array[row][col] -= (k * m_array[i][col]);
                }
            }
            print(STRING, "\n");
            print_SLAE(matrix);
        }
    } else {
        throw_exception(error, NULL_PTR_ERROR, "matrix_to_triangular_view: передан NULL указатель.");
    }
    return rows_swaps;
}

static double reverse_substitution(matrix *matrix, double *results, size_t x) {
    double **m_array = matrix_get_matrix(matrix);
    size_t rows = matrix_get_rows(matrix) - 1;
    if (x == 0) {
        results[rows - x] = results[rows - x] / m_array[rows - x][rows - x];
        return results[rows - x];
    } else {
        double k = reverse_substitution(matrix, results, x - 1);
        for (size_t i = 0; i <= matrix_get_rows(matrix) - x - 1; i++) {
            results[i] = (results[i] - (m_array[i][rows - x + 1] * k));
        }
        results[rows - x] /= m_array[rows - x][rows - x];
        return results[rows - x];
    }
}

void gauss_method_inverse(matrix *matrix, double *results, error_s *error) {
    if (matrix != NULL && results != NULL) {
        size_t rows = matrix_get_rows(matrix);
        size_t columns = matrix_get_columns(matrix);
        for (size_t i = 0; i < rows; i++) {
            results[i] = matrix_get_matrix(matrix)[i][columns - 1];
        }
        reverse_substitution(matrix, results, matrix_get_rows(matrix) - 1);
    } else {
        throw_exception(error, NULL_PTR_ERROR, "gauss_method_inverse: передан NULL указатель.");
    }
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
