//
// Created by potato_coder on 06.02.23.
//

#ifndef COUNTMATHLAB1_PRINTER_H
#define COUNTMATHLAB1_PRINTER_H

#include "../string_utils/string_s.h"
#include <bits/types/FILE.h>
#include <stdio.h>

enum printer_modes {
    STRING = 0,
    ONE_CHAR,
    SIGN_INT,
    SIGN_LONG_INT,
    SIGN_DOUBLE,
};

static char *printer_mode[] = {
        "%s", "%c", "%d", "%ld", "lf"
};

void println(enum printer_modes mode, void *arg);

void println_to(FILE *stream, enum printer_modes mode, void *arg);

#endif //COUNTMATHLAB1_PRINTER_H
