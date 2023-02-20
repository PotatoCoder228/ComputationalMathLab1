//
// Created by potato_coder on 09.02.23.
//

#include <ctype.h>
#include "../../include/command/command.h"
#include "../../include/console/console.h"
#include "../../include/linear_algebra/matrix.h"
#include "../../include/linear_algebra/lin_eq_solver.h"
#include "../../include/io/io_handler.h"
#include "../../include/chart/gtk_chart.h"

linked_list *commands_list;
int checker = 0;

typedef struct user_command {
    char *description;

    void (*callback)(error_s *error);
} user_command;


user_command *new_user_command(void callback(error_s *), char *descr) {
    user_command *command = malloc(sizeof(user_command));
    if (command != NULL) {
        command->callback = callback;
        command->description = descr;
    }
    return command;
}


void *user_command_get_callback(user_command *command) {
    return command->callback;
}

void user_command_set_callback(user_command *command, void callback(error_s *)) {
    command->callback = callback;
}

char *user_command_get_description(user_command *command) {
    return command->description;
}

void user_command_set_description(user_command *command, char *description) {
    command->description = description;
}

void user_command_destroy(user_command *command) {
    free(command);
}

void print_commands_help() {
    linked_list *buffer = commands_list;
    printf("\nСправка по командам:\n");
    while (buffer != NULL) {
        printf("%s\n", ((user_command *) linked_list_get_node_value(buffer))->description);
        buffer = linked_list_get_node_next(buffer);
    }
}

void help_command(error_s *error) {
    print_commands_help();
}

void string_builder_list_to_doubles_array(double **m_array, size_t arr_size, linked_list *list, error_s *error) {
    if (list != NULL && m_array != NULL) {
        for (size_t i = 0; i < arr_size; i++) {
            string_builder *string = linked_list_get(list, i);
            char **end = NULL;
            (*m_array)[i] = strtod(string_builder_get_string(string), end);
        }
    } else {
        throw_exception(error, NULL_PTR_ERROR, "string_builder_list_to_doubles_array: передан NULL указатель");
    }
}

void gauss_method_from(FILE *stream, error_s *error) {
    error_set_default(error);
    if (stream == NULL) {
        throw_exception(error, NULL_PTR_ERROR, "gauss_method_from: передан NULL указатель на FILE*.");
    }
    string_builder *matrix_string = read_line(stream, error);
    linked_list *k_list = string_builder_get_token_list(matrix_string, " \t", 20);
    if (k_list == NULL) {
        printf("Ничего не введено.");
        string_builder_destroy(matrix_string);
        return;
    }
    const size_t matrix_width = linked_list_get_size(k_list);
    double *m_array[matrix_width];
    for (size_t i = 0; i < matrix_width; i++) {
        m_array[i] = malloc(sizeof(double) * (matrix_width + 1));
    }
    double r_array[matrix_width][matrix_width + 1];

    string_builder_list_to_doubles_array(&(m_array[0]), matrix_width, k_list, error);
    linked_list_destroy(k_list, string_builder_destroy);
    k_list = NULL;
    string_builder_destroy(matrix_string);
    matrix_string = NULL;


    for (size_t i = 1; i < matrix_width; i++) {
        matrix_string = read_line(stream, error);
        k_list = string_builder_get_token_list(matrix_string, " \t", matrix_width);
        if (linked_list_get_size(k_list) != matrix_width) {
            println(STRING, "Количество коэффициентов не равно размерности матрицы!");
            for (size_t k = 0; k < i - 1; k++) {
                free(m_array[k]);
            }
            linked_list_destroy(k_list, string_builder_destroy);
            string_builder_destroy(matrix_string);
            return;
        }
        m_array[i] = malloc(sizeof(double) * (matrix_width + 1));
        string_builder_list_to_doubles_array(&(m_array[i]), matrix_width, k_list, error);
        linked_list_destroy(k_list, string_builder_destroy);
        k_list = NULL;
        string_builder_destroy(matrix_string);
        matrix_string = NULL;
    }
    println(STRING, "\nВведите вектор B:");
    matrix_string = read_line(stream, error);
    print(STRING, "\n");
    k_list = string_builder_get_token_list(matrix_string, " \t", matrix_width);
    if (linked_list_get_size(k_list) != matrix_width) {
        printf("Некорректный ввод: вектор В должен быть равен по длине размерности матрицы.");
        for (size_t k = 0; k < matrix_width; k++) {
            free(m_array[k]);
        }
        linked_list_destroy(k_list, string_builder_destroy);
        k_list = NULL;
        string_builder_destroy(matrix_string);
        matrix_string = NULL;
        return;
    }
    double *array = malloc(sizeof(double) * (matrix_width));
    if (array == NULL) {
        throw_exception(error, MEM_ALLOC_DENIED, "gauss_method_from: недостаточно памяти для выделения под array.");
    }
    string_builder_list_to_doubles_array(&array, matrix_width, k_list, error);
    for (size_t i = 0; i < matrix_width; i++) {
        m_array[i][matrix_width] = array[i];
    }
    for (size_t i = 0; i < matrix_width; i++) {
        for (size_t j = 0; j <= matrix_width; j++) {
            r_array[i][j] = m_array[i][j];
        }
    }
    linked_list_destroy(k_list, string_builder_destroy);
    k_list = NULL;
    string_builder_destroy(matrix_string);
    matrix_string = NULL;
    matrix *matrix = new_matrix();
    matrix_init(matrix, m_array, matrix_width, matrix_width + 1);
    print_SLAE(matrix);
    print(STRING, "\n");
    int64_t k = matrix_to_triangular_view(matrix, error);
    if (error_get_code(error) != 0) {
        for (size_t i = 0; i < matrix_width; i++) {
            free(m_array[i]);
        }
        matrix_destroy(matrix);
        matrix = NULL;
        return;
    }
    double det = matrix_det_from_triangular_view(matrix, k, error);
    printf("\n%s: %lf\n\n", "Детерминант", det);
    if (det == 0) {
        println(STRING, "СЛАУ имеет бесконечное множество решений или не имеет вовсе!\n");
        for (size_t i = 0; i < matrix_width; i++) {
            free(m_array[i]);
        }
        matrix_destroy(matrix);
        matrix = NULL;
        return;
    }
    double *results = malloc(sizeof(double) * matrix_width);
    if (results == NULL) {
        throw_exception(error, MEM_ALLOC_DENIED, "gauss_method_from: недостаточно памяти для выделения под results.");
    }
    gauss_method_inverse(matrix, results, error);
    print(STRING, "\nВектор искомых неизвестных:\n");
    for (size_t i = 0; i < matrix_width; i++) {
        printf("x_%ld = ", i + 1);
        print_double(results[i]);
        print(STRING, "\n");
    }
    for (size_t i = 0; i < matrix_width; i++) {
        free(m_array[i]);
        m_array[i] = NULL;
    }
    double rs[20] = {0};
    print(STRING, "\nВектор невязки:\n");
    for (size_t i = 0; i < matrix_width; i++) {
        rs[i] = r_array[i][matrix_width];
        for (size_t j = 0; j < matrix_width; j++) {
            rs[i] -= results[j] * r_array[i][j];
        }
        printf("r_%ld: ", i + 1);
        printf("%.51F", rs[i]);
        print(STRING, "\n");
    }
    matrix_destroy(matrix);
    matrix = NULL;
}

void gauss_command(error_s *error) {
    println(STRING, "Введите коэффициенты СЛАУ для 1 строки.");
    println(STRING, "Матрица должна получиться квадратной.\n"
                    "Количество строк/столбцов определяется по количеству чисел в 1 строке.\n"
                    "Не более 20 элементов(все остальные не будут считываться в матрицу).");
    gauss_method_from(stdin, error);
}

void gauss_f_command(error_s *error) {
    print(STRING, "Введите имя файла:");
    string_builder *arg = read_line(stdin, error);
    if (arg == NULL) {
        throw_exception(error, INPUT_STREAM_READ_ERROR, "gauss_f_command: Не удалось прочитать строку.");
    }
    FILE *file;
    open_file(&file, string_builder_get_string(arg), R, error);
    if (file == NULL) {
        string_builder_destroy(arg);
        return;
    }
    gauss_method_from(file, error);
    close_file(&file, error);
    string_builder_destroy(arg);
}

void exit_command(error_s *error) {
    println(STRING, "Производится выход из программы...");
}

void chart_command(error_s *error) {
    double *array = NULL;
    build_gtk_chart(array);
}

void undefined_command(error_s *error) {
    printf("%s%s", "\nНекорректная команда, попробуйте ввести ещё раз!\n", "help - справка по командам\n");
}

void run_command(user_command *command, error_s *error) {
    void (*command_call)(error_s *) = command->callback;
    command_call(error);
}

user_command *get_user_command_from_list(linked_list *tokens) {
    user_command *user_command = new_user_command(NULL, NULL);
    string_builder *command = linked_list_get_node_value(tokens);
    if (!strcmp(string_builder_get_string(command), "help")) {
        user_command_set_callback(user_command, help_command);
    } else if (!strcmp(string_builder_get_string(command), "gauss_f")) {
        user_command_set_callback(user_command, gauss_f_command);
    } else if (!strcmp(string_builder_get_string(command), "exit")) {
        user_command_set_callback(user_command, exit_command);
    } else if (!strcmp(string_builder_get_string(command), "gauss")) {
        user_command_set_callback(user_command, gauss_command);
    } else if (!strcmp(string_builder_get_string(command), "chart")) {
        user_command_set_callback(user_command, chart_command);
    } else {
        user_command_set_callback(user_command, undefined_command);
    }
    return user_command;
}

void help_list_init(error_s *error) {
    user_command *command_help = new_user_command(help_command, (void *) descriptions[HELP]);
    if (command_help == NULL) {
        throw_exception(error, MEM_ALLOC_DENIED,
                        "help_list_init: Не удалось выделить память для инициализации справки.");
        return;
    }
    user_command *command_gauss_f = new_user_command(gauss_f_command, (void *) descriptions[GAUSS_F]);
    if (command_gauss_f == NULL) {
        user_command_destroy(command_help);
        throw_exception(error, MEM_ALLOC_DENIED,
                        "help_list_init: Не удалось выделить память для инициализации справки.");
        return;
    }
    user_command *command_exit = new_user_command(exit_command, (void *) descriptions[EXIT]);

    if (command_exit == NULL) {
        user_command_destroy(command_help);
        user_command_destroy(command_gauss_f);
        throw_exception(error, MEM_ALLOC_DENIED,
                        "help_list_init: Не удалось выделить память для инициализации справки.");
        return;
    }

    user_command *command_gauss = new_user_command(gauss_command, (void *) descriptions[GAUSS]);

    if (command_exit == NULL) {
        user_command_destroy(command_help);
        user_command_destroy(command_gauss_f);
        user_command_destroy(command_gauss);
        throw_exception(error, MEM_ALLOC_DENIED,
                        "help_list_init: Не удалось выделить память для инициализации справки.");
        return;
    }

    commands_list = linked_list_init(command_help, 0);
    if (commands_list == NULL) {
        user_command_destroy(command_help);
        user_command_destroy(command_gauss_f);
        user_command_destroy(command_exit);
        user_command_destroy(command_gauss);
        throw_exception(error, MEM_ALLOC_DENIED,
                        "help_list_init: Не удалось выделить память для инициализации справки.");
        return;
    }
    linked_list_push(commands_list, command_gauss_f, 0);
    linked_list_push(commands_list, command_gauss, 0);
    linked_list_push(commands_list, command_exit, 0);
}

void help_list_destroy() {
    linked_list_destroy(commands_list, free);
}