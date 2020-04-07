#include <stdio.h>
#include "list.h"

int main(int argc, char *argv[]) {
    LinkedList *my_list = new_list();
    int size_of_list;
    int i;
    while (scanf("%d", &i) == 1) {
        my_list = add_tail(my_list, i);
        /* printf("\n%d is inserted at tail\n", i); */
        size_of_list = list_length(my_list);
        /* printf("size = %d\n", size_of_list); */
        print_list(my_list, size_of_list); 
    }

    printf("\nI am going to delete the head now!\n");
    my_list = del_head(my_list);
    print_list(my_list, list_length(my_list));

    printf("\nI am going to delete the tail now!\n");
    my_list = del_tail(my_list);
    print_list(my_list, list_length(my_list));
    
    printf("\nThe current head is: %d\n", get_head(my_list));
    printf("\nThe current tail is: %d\n", get_tail(my_list));

    return 0;
}