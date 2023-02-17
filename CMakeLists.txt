project(CountMathLab1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_COMPILER 11)
set(PROJECT_TARGET CountMathLab1)

cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

add_executable(${PROJECT_TARGET} linear_equations_solver/src/main.c linear_equations_solver/src/utils/printer.c linear_equations_solver/include/utils/printer.h linear_equations_solver/src/app.c linear_equations_solver/include/app.h linear_equations_solver/src/io/io_handler.c linear_equations_solver/include/io/io_handler.h linear_equations_solver/src/string_utils/string_s.c linear_equations_solver/include/string_utils/string_s.h linear_equations_solver/src/exceptions/exceptions.c linear_equations_solver/include/exceptions/exceptions.h linear_equations_solver/src/containers/singly_linked_list.c linear_equations_solver/include/containers/singly_linked_list.h linear_equations_solver/src/command/command.c linear_equations_solver/include/command/command.h linear_equations_solver/src/console/console.c linear_equations_solver/include/console/console.h linear_equations_solver/src/linear_algebra/matrix.c linear_equations_solver/include/linear_algebra/matrix.h linear_equations_solver/src/linear_algebra/lin_eq_solver.c linear_equations_solver/include/linear_algebra/lin_eq_solver.h linear_equations_solver/src/chart/gtk_chart.c linear_equations_solver/include/chart/gtk_chart.h)

target_link_libraries(${PROJECT_TARGET} PRIVATE ${GTK_LIBRARIES})

if (UNIX)
    set(CMAKE_EXE_LINKER_FLAGS "-rdynamic")
endif ()

target_include_directories(${PROJECT_TARGET} PRIVATE ${GTK_INCLUDE_DIRS})
target_link_directories(${PROJECT_TARGET} PRIVATE ${GTK_LIBRARY_DIRS})
target_compile_options(${PROJECT_TARGET} PRIVATE ${GTK_CFLAGS_OTHER})