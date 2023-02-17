#include <stdlib.h>
#include "../include/app.h"

int main(int argc, char **argv) {
    error_s *error = new_error();
    app_start(error);
    error_destroy(error);
    return EXIT_SUCCESS;
}
