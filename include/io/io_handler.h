//
// Created by potato_coder on 06.02.23.
//

#ifndef COUNTMATHLAB1_IO_HANDLER_H
#define COUNTMATHLAB1_IO_HANDLER_H

#include "../exceptions/exceptions.h"
#include <bits/types/FILE.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

enum open_file_modes {
    R = 0,
    W,
    A,
    RB,
    WB,
    AB,
    R_EXTENDED,
    W_EXTENDED,
    A_EXTENDED,
    RB_EXTENDED,
    WB_EXTENDED,
    AB_EXTENDED,
    RT,
    WT,
    AT,
    RT_EXTENDED,
    WT_EXTENDED,
    AT_EXTENDED
};

static char *open_file_modes[] = {
        "r", "w", "a", "rb", "wb", "ab",
        "r+", "w+", "a+", "r+b", "w+b",
        "a+b", "rt", "wt", "at", "r+t",
        "w+t", "a+t"
};

void open_file(FILE **stream, char *filename, enum open_file_modes mode, error_s *error);

void close_file(FILE **stream, error_s *error);

#endif //COUNTMATHLAB1_IO_HANDLER_H
