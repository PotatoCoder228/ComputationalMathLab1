//
// Created by potato_coder on 06.02.23.
//

#include <stdio.h>
#include "../../headers/utils/printer.h"

void println(enum printer_modes mode, void* arg){
    printf(printer_mode[mode], arg);
    printf("%s", "\n");
}