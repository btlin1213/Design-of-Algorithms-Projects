#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* include header file */
#include "list.h"

/* define structs for node and SINGLY-linked list */
struct node {
    int data;
    struct node *next;
};

struct list {
    node_t *head;
    node_t *tail;
};

/* create new linked list */
LinkedList* new_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    assert(list);
    list->head = list->tail = NULL;
    return list;
}

/* insert at front */
LinkedList* add_head(LinkedList *list, int elem) {
    node_t *new;
    new = (node_t*)malloc(sizeof(node_t));
    assert(list && new);
    new->data = elem;

    new->next = list->head;
    list->head = new;

    if (list->tail == NULL) {
        /* this insertion is the first elem in list */
        list->tail = new;
    }
    return list;
}

/* insert at end */
LinkedList* add_tail(LinkedList *list, int elem) {
    node_t *new;
    new = (node_t*)malloc(sizeof(node_t));
    assert(list && new);
    new->data = elem;
    new->next = NULL;
    if (list->tail == NULL) {
        /* first insertion into list */
        list->head = list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
    return list;
}   

/* delete from front */
LinkedList* del_head(LinkedList *list) {
    node_t *toDelete;
    toDelete = (node_t*)malloc(sizeof(node_t));
    assert(list && toDelete);
    
    /* store the current head in toDelete */
    toDelete = list->head;
    /* increment head by 1 */
    list->head = list->head->next;

    /* free the deleted node */
    free(toDelete);

    return list;
    /* debug this program by checking the length later */
}

/* delete from end */
LinkedList* del_tail(LinkedList *list) {
    node_t *toDelete;
    node_t *curr;
    toDelete = (node_t*)malloc(sizeof(node_t));
    assert(list && toDelete);

    /* store the current tail in toDelete */
    toDelete = list->tail;

    /* DO list->tail =  SECOND-LAST NODE */
    curr = list->head;
    while (curr->next != list->tail) {
        /* by the end of this while loop, curr = second-last node */
        curr = curr->next;
    }

    curr->next = NULL;
    list->tail = curr;

    /* free the deleted node */
    free(toDelete);
    return list;
    /* debug later by checking length */
}

/* retrieve data at front of list */
int get_head(LinkedList *list) {
    assert(list && list->head);
    return list->head->data;
}

/* retrieve data at end of list */
int get_tail(LinkedList *list) {
    assert(list && list->tail);
    return list->tail->data;
}

/* find out current size of list */
int list_length(LinkedList *list) {
    int length = 0;
    node_t *temp;
    temp = (node_t*)malloc(sizeof(node_t));
    temp = list->head;

    assert(list);
    while (temp) {
        length += 1;
        temp = temp->next;
    }
    return length;
}

/* free the list */
void free_list(LinkedList *list) {
    node_t *curr, *prev;
    assert(list);
    curr = list->head;
    /* free the nodes one by one */
    while (curr) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    /* free the whole list */
    free(list);
}

/* print the list */
void print_list(LinkedList *list, int len) {
    assert(list);
    node_t *curr;
    curr = list->head;
    int i=0;
    printf("\nThe list currently looks like:\n");
    for (i=0; i<len; i++) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}
