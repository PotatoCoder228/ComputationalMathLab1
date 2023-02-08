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
    return list->value;
}

void linked_list_set_node_value(linked_list *list, void *value, bool in_heap) {
    if (list != NULL) {
        list->value = value;
        list->value_in_heap = in_heap;
    }
}

linked_list *linked_list_get_node_next(linked_list *list) {
    return list->next;
}

void linked_list_set_node_next(linked_list *list, linked_list *next) {
    list->next = next;
}

void linked_list_destroy(linked_list *list) {
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

int linked_list_push(linked_list *node, void *value, bool in_heap) {//OK
    if (node != NULL) {
        node = get_last_node(node);
        if (node == NULL) {
            return -1;
        }
        linked_list *add_node = linked_list_node_constructor();
        add_node->value = value;
        node->next = add_node;
        add_node->value_in_heap = in_heap;
        return 0;
    }
    return -1;
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

int linked_list_add_last(linked_list *node, void *value, bool in_heap) {//OK
    if (node != NULL) {
        node = get_last_node(node);
        if (node == NULL) {
            return -1;
        }
        linked_list *add_node = linked_list_node_constructor();
        add_node->value = value;
        node->next = add_node;
        add_node->value_in_heap = in_heap;
        return 0;
    }
    return -1;
}

int linked_list_add_first(linked_list **node, void *value, bool in_heap) {//OK
    linked_list *new_node = linked_list_node_constructor();
    if (new_node == NULL) {
        return -1;
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
    return 0;
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
    size_t list_size = linked_list_get_size(node);
    if (index > list_size) {
        return NULL;
    }
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }
    return node->value;
}

int linked_list_insert(linked_list **node, size_t index, void *value, bool in_heap) {
    size_t list_size = linked_list_get_size(*node);
    if (index > list_size) {
        return -1;
    }
    linked_list *new_node = linked_list_node_constructor();
    if (new_node != NULL) {
        new_node->value_in_heap = in_heap;
        if (index == 0) {
            new_node->value = value;
            new_node->next = *node;
            *node = new_node;
            return 0;
        }
        new_node->value = value;
        for (size_t i = 1; i < index; i++) {
            *node = (*node)->next;
        }
        new_node->next = (*node)->next;
        (*node)->next = new_node;
        return 0;
    }
    return -1;
}

void print_linked_list(FILE *stream, enum printer_modes mode, linked_list *list) {//OK
    if (stream != NULL && list != NULL) {
        size_t counter = 0;
        print_to(stream, STRING, "\n[");
        while (list != NULL) {
            fprintf(stream, printer_mode[mode], list->value);
            counter += 1;
            list = list->next;
            if (list != NULL) {
                print_to(stream, STRING, ", ");
            }
            if (counter % 10 == 0) {
                print_to(stream, STRING, "\n");
            }
        }
        print_to(stream, STRING, "]\n");
    }
}

int linked_list_clone(linked_list *list, linked_list **clone) {//TODO дописать клонирование и итератор по списку
    if (list != NULL) {
        //код копирования связного списка тута
    }
    return -1;
}