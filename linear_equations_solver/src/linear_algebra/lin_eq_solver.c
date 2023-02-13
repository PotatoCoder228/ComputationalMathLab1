//
// Created by potato_coder on 09.02.23.
//

#include "../../include/linear_algebra/lin_eq_solver.h"

static double num_pow(int64_t num, int64_t k) {
    if(k == 0){
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

double chain(matrix* matrix, double* results, size_t x){
    double** m_array = matrix_get_matrix(matrix);
    size_t rows = matrix_get_rows(matrix) - 1;
    if(x == 0){
        results[rows-x] = results[rows-x]/m_array[rows-x][rows-x];
        printf("\nВершина рекурсии: %lf\n",results[rows-x]);
        return results[rows-x];
    }
    else{
        /*если выше последней строки, то мы считаем x_n
         * и потом последовательно отнимаем от правой стороны каждой строки
         * (results[i] - m_array[i][x]*x_n)
         * В конце рекурсивного вызова просто делим все результаты на a[j][j]
         * коэффициенты
         */
        double k = chain(matrix, results, x - 1);
        println(STRING,"\nВычисление нового вызова.");
        for(size_t i = 0; i <= matrix_get_rows(matrix)-x-1; i++){
            printf("\nОтнимаем от правой части %lf число (%lf * %lf)\n", results[i], m_array[i][rows-x+1], k);
            printf("\nresults[%ld] - m_array[%ld, %ld]*k\n", i, i, rows-x+1);
            results[i] = (results[i] - (m_array[i][rows-x+1]*k));
            printf("Правая часть строки %ld: %lf\n", x, results[i]);
        }
        //results[rows-x] = results[rows-x]/m_array[x][x];
        println(STRING,"\nКонец нового вызова.");
        /*
        if(x == matrix_get_rows(matrix)-1) {
            for (size_t i = 0; i < matrix_get_rows(matrix) - 1; i++) {
                results[i] = results[i] / m_array[i][i];
            }
        }
        */
        results[rows-x] /= m_array[rows-x][rows-x];
        return results[rows-x];
    }

}

void gauss_method_inverse(matrix* matrix, double* results, error_s* error){
    if(matrix != NULL && results != NULL){
        double** m_array = matrix_get_matrix(matrix);
        size_t rows = matrix_get_rows(matrix);
        size_t columns = matrix_get_columns(matrix);
        for(size_t i = 0; i < rows; i++){
            results[i] = m_array[i][columns-1];
        }
        double result = chain(matrix, results, matrix_get_rows(matrix) - 1);
        for(size_t i = 0; i < matrix_get_rows(matrix); i++) {
            printf("Res %ld: %lf\n", i, results[i]);
        }
    }
    else{
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



void test(error_s *error) {
    matrix *matrix = new_matrix();

    double **m_array = malloc(sizeof(double*) * 4);
    double first[5] = {1, 1, 2, 3, 1};
    double second[5] = {1, 2, 3, -1, -4};
    double third[5] = {3, -1, -1, -2, -4};
    double four[5] =  {2, 3, -1, -1, -6};

    m_array[0] = first;
    m_array[1] = second;
    m_array[2] = third;
    m_array[3] = four;

    matrix_init(matrix, m_array, 4, 5);
    matrix_print(matrix);

    print(STRING, "\n");

    int64_t k = matrix_to_triangular_view(matrix, error);
    double det = matrix_det_from_triangular_view(matrix, k, error);
    printf("%s: %lf\n", "Детерминант", det);
    double* results = malloc(sizeof(double)*4);
    gauss_method_inverse(matrix, results, error);
    free(m_array);
    free(results);
    matrix_destroy(matrix);
}
