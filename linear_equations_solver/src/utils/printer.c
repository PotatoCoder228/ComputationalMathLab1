//
// Created by potato_coder on 06.02.23.
//
#include "../../include/utils/printer.h"

void print_num_array(double *array, enum printer_modes mode, size_t arr_size) {
    for (size_t i = 0; i < arr_size; i++) {
        if (i % 9 == 0) {
            printf("%c", '\n');
        }
        printf(printer_mode[mode], array[i]);
    }
}

void print_double_num_array(double **array, size_t arr_width, size_t arr_height) {
    for (size_t i = 0; i < arr_height; i++) {
        printf("%s", "{");
        for (size_t j = 0; j < arr_width; j++) {
            if (j % 9 == 0) {
                printf("%c", '\n');
            }
            printf("%lf ", array[i][j]);
        }
        printf("%s", "},\n");
    }
}

void print(enum printer_modes mode, void *arg) {
    printf(printer_mode[mode], arg);
}

void print_to(FILE *stream, enum printer_modes mode, void *arg) {
    fprintf(stream, printer_mode[mode], arg);
}

void println(enum printer_modes mode, void *arg) {
    printf(printer_mode[mode], arg);
    printf("%s", "\n");
}

void println_to(FILE *stream, enum printer_modes mode, void *arg) {
    fprintf(stream, printer_mode[mode], arg);
    fprintf(stream, "%s", "\n");
}
