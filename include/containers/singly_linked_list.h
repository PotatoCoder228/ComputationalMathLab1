//
// Created by potato_coder on 08.02.23.
//

#ifndef COUNTMATHLAB1_SINGLY_LINKED_LIST_H
#define COUNTMATHLAB1_SINGLY_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../include/utils/printer.h"

typedef struct linked_list linked_list;

void *linked_list_get_node_value(linked_list *list);

void linked_list_set_node_value(linked_list *list, void *value, bool in_heap);

linked_list *linked_list_get_node_next(linked_list *list);

void linked_list_set_node_next(linked_list *list, linked_list *next);

linked_list *linked_list_init(void *value, bool in_heap);


linked_list *linked_list_node_constructor();

void *linked_list_get_last(linked_list *node);

void *linked_list_pop(linked_list *node);

int linked_list_push(linked_list *node, void *value, bool in_heap);

int linked_list_add_last(linked_list *node, void *value, bool in_heap);

int linked_list_add_first(linked_list **node, void *value, bool in_heap);

size_t linked_list_get_size(linked_list *node);

void *linked_list_get(linked_list *node, size_t index);

void linked_list_destroy(linked_list *list);

int linked_list_clone(linked_list *list, linked_list **clone);

void print_linked_list(FILE *stream, enum printer_modes mode, linked_list *list);

int linked_list_insert(linked_list **node, size_t index, void *value, bool in_heap);


#endif //COUNTMATHLAB1_SINGLY_LINKED_LIST_H
