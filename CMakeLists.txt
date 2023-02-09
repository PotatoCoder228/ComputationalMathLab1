cmake_minimum_required(VERSION 3.25)
project(CountMathLab1 C)

set(CMAKE_C_STANDARD 11)

add_executable(CountMathLab1 linear_equations_solver/src/main.c linear_equations_solver/src/utils/printer.c linear_equations_solver/include/utils/printer.h linear_equations_solver/src/app.c linear_equations_solver/include/app.h linear_equations_solver/src/io/io_handler.c linear_equations_solver/include/io/io_handler.h linear_equations_solver/src/string_utils/string_s.c linear_equations_solver/include/string_utils/string_s.h linear_equations_solver/src/exceptions/exceptions.c linear_equations_solver/include/exceptions/exceptions.h linear_equations_solver/src/containers/singly_linked_list.c linear_equations_solver/include/containers/singly_linked_list.h linear_equations_solver/src/command/command.c linear_equations_solver/include/command/command.h linear_equations_solver/src/console/console.c linear_equations_solver/include/console/console.h linear_equations_solver/src/linear_algebra/matrix.c linear_equations_solver/include/linear_algebra/matrix.h linear_equations_solver/src/linear_algebra/lin_eq_solver.c linear_equations_solver/include/linear_algebra/lin_eq_solver.h)
