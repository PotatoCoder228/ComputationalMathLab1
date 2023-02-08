//
// Created by potato_coder on 08.02.23.
//

#include "../../include/containers/singly_linked_list.h"

typedef struct linked_list {
    void *value;
    struct linked_list *next;
    bool value_in_heap;
} linked_list;

void *linked_list_get_node_value(linked_list *list) {
    if (list != NULL) {
        return list->value;
    }
    return NULL;
}

void linked_list_set_node_value(linked_list *list, void *value, bool in_heap) {
    if (list != NULL) {
        list->value = value;
        list->value_in_heap = in_heap;
    }
}

linked_list *linked_list_get_node_next(linked_list *list) {
    if (list != NULL) {
        return list->next;
    }
    return NULL;
}

void linked_list_set_node_next(linked_list *list, linked_list *next) {
    if (list != NULL) {
        list->next = next;
    }
}

void linked_list_destroy(linked_list *list) {
    if (list != NULL) {
        linked_list *buffer;
        while (list != NULL) {
            buffer = list;
            list = list->next;
            if (buffer->value_in_heap == true) {
                free(buffer->value);
            }
            free(buffer);
        }
    }
}

linked_list *linked_list_node_constructor() {
    linked_list *list = malloc(sizeof(linked_list));
    if (list != NULL) {
        list->next = NULL;
        list->value_in_heap = false;
    }
    return list;
}

linked_list *linked_list_init(void *value, bool in_heap) {
    linked_list *list = malloc(sizeof(linked_list));
    if (list != NULL) {
        list->value = value;
        list->next = NULL;
        list->value_in_heap = in_heap;
    }
    return list;
}

linked_list *get_last_node(linked_list *node) {//OK
    if (node != NULL) {
        linked_list *prev_node = node;
        while (node != NULL) {
            prev_node = node;
            node = node->next;
        }
        return prev_node;
    }
    return NULL;
}

void *linked_list_get_last(linked_list *node) {//OK
    if (node != NULL) {
        linked_list *prev_node = node;
        while (node != NULL) {
            prev_node = node;
            node = node->next;
        }
        return prev_node->value;
    }
    return NULL;
}

bool linked_list_push(linked_list *node, void *value, bool in_heap, error_s *error) {//OK
    if (node != NULL) {
        node = get_last_node(node);
        if (node == NULL) {
            return false;
        }
        linked_list *add_node = linked_list_node_constructor();
        add_node->value = value;
        node->next = add_node;
        add_node->value_in_heap = in_heap;
        return true;
    }
    return false;
}

void *linked_list_pop(linked_list *node) {//OK
    if (node != NULL) {
        linked_list *prev_node = node;
        linked_list *last_node = node;
        while (node != NULL) {
            prev_node = last_node;
            last_node = node;
            node = node->next;
        }
        prev_node->next = NULL;
        void *value = last_node->value;
        free(last_node);
        return value;
    }
    return NULL;
}

bool linked_list_add_last(linked_list *node, void *value, bool in_heap) {//OK
    if (node != NULL) {
        node = get_last_node(node);
        if (node == NULL) {
            return false;
        }
        linked_list *add_node = linked_list_node_constructor();
        add_node->value = value;
        node->next = add_node;
        add_node->value_in_heap = in_heap;
        return true;
    }
    return false;
}

bool linked_list_add_first(linked_list **node, void *value, bool in_heap) {//OK
    if (node == NULL) {
        return false;
    }
    linked_list *new_node = linked_list_node_constructor();
    if (new_node == NULL) {
        return false;
    }
    new_node->value = value;
    new_node->value_in_heap = in_heap;
    new_node->next = NULL;
    linked_list *buffer;
    if ((*node)->value != NULL) {
        buffer = new_node;
        new_node = *node;
        *node = buffer;
        (*node)->next = new_node;
    } else {
        *node = new_node;
    }
    return true;
}

size_t linked_list_get_size(linked_list *node) {
    size_t counter = 1;
    while (node != NULL) {
        counter += 1;
        node = node->next;
    }
    return counter;
}

void *linked_list_get(linked_list *node, size_t index) {
    if (node == NULL) {
        return NULL;
    }
    size_t list_size = linked_list_get_size(node);
    if (index > list_size) {
        return NULL;
    }
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }
    return node->value;
}

bool linked_list_insert(linked_list **node, size_t index, void *value, bool in_heap) {
    if (node == NULL) {
        return false;
    }
    size_t list_size = linked_list_get_size(*node);
    if (index > list_size) {
        return false;
    }
    linked_list *new_node = linked_list_node_constructor();
    if (new_node != NULL) {
        new_node->value_in_heap = in_heap;
        if (index == 0) {
            new_node->value = value;
            new_node->next = *node;
            *node = new_node;
            return true;
        }
        new_node->value = value;
        for (size_t i = 1; i < index; i++) {
            *node = (*node)->next;
        }
        new_node->next = (*node)->next;
        (*node)->next = new_node;
        return true;
    }
    return false;
}

typedef void* (*callback)(void* data);

void iterator(linked_list* list, callback iter_func){
    while(list != NULL){
        iter_func(list);
        list = list->next;
    }
}

void linked_list_print(FILE *stream, enum printer_modes mode, linked_list *list,
                       void (printer)(FILE *, enum printer_modes, void *)) {//OK
    if (stream != NULL && list != NULL) {
        size_t counter = 0;
        printer(stream, STRING, "\n[");
        while (list != NULL) {
            fprintf(stream, printer_mode[mode], list->value);
            counter += 1;
            list = list->next;
            if (list != NULL) {
                printer(stream, STRING, ", ");
            }
            if (counter % 10 == 0) {
                printer(stream, STRING, "\n");
            }
        }
        printer(stream, STRING, "]\n");
    }
}