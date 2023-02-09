#include <stdlib.h>
#include "../include/app.h"
#include "../include/exceptions/exceptions.h"

int main() {
    error_s* error = new_error();
    app_start(error);
    return EXIT_SUCCESS;
}
