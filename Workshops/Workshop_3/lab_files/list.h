/* include guard */
#ifndef LIST_H /* if not defined */
#define LIST_H /* then define it */ 
/* NOTE: C doesn't like it when you define things more than once */

/* declare a new type called LinkedList 
that is a struct called list */ 
typedef struct list LinkedList;
typedef struct node node_t;

/* function declarations */

/* create new linked list */
LinkedList* new_list();
/* add node at front of list */
LinkedList* add_head(LinkedList *list, int elem);
/* add node at back of list */
LinkedList* add_tail(LinkedList *list, int elem);
/* delete node from front of list */
LinkedList* del_head(LinkedList *list);
/* delete node from back of list */
LinkedList* del_tail(LinkedList *list);
/* retrieve data at front of list */
int get_head(LinkedList *list);
/* retrieve data at end of list */
int get_tail(LinkedList *list); 
/* find length of list */
int list_length(LinkedList *list);
/* free linked list */
void free_list(LinkedList *list);
/* print list */
void print_list(LinkedList *list, int len);
#endif
