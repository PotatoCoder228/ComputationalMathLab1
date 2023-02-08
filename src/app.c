//
// Created by potato_coder on 06.02.23.
//
#include "../include/app.h"
#include "../include/containers/singly_linked_list.h"


int app_start() {
    println(STRING, "Добро пожаловать в консольное приложение.");
    void *num = (void *) 222201;
    void *num1 = (void *) 2224;
    linked_list *list = linked_list_init(num, false);
    linked_list_add_first(&list, num1, false);
    linked_list_print(stdout, SIGN_INT, list, print_to);
    linked_list_print(stdout, SIGN_INT, list, print_to);
    linked_list_destroy(list);
    return 0;
}