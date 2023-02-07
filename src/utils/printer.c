//
// Created by potato_coder on 06.02.23.
//
#include "../../include/utils/printer.h"


void println(enum printer_modes mode, void *arg) {
    printf(printer_mode[mode], arg);
    printf("%s", "\n");
}

void println_to(FILE *stream, enum printer_modes mode, void *arg) {
    fprintf(stream, printer_mode[mode], arg);
    fprintf(stream, "%s", "\n");
}
