/* TAKE AWAY LESSON: CANNOT FIND SIZE OF DYNAMICALLY ALLOCATED ARRAYS WITH sizeof(),
   must keep track of the size yourself! */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define INITIAL 4

/* function declaration */
void print_array(int *arr, int size);


int main(int argc, char *argv[]) {
    printf("Enter the student IDs for the class list, followed by ^D:\n");

    /* initial array of size 4 */
    /* NOTE using set length like int* list = int[4] = {0,0,0,0} makes it more concrete, avoid! */
    int size = INITIAL;
    int* list = (int*) malloc(sizeof(int)*size);
    assert (list);
    printf("initial array size: %d\n", size);

    /* count of inputs */
    int input = 0;
    int count = 0;
    int index = 0;
    while (scanf("\n%d", &input) != EOF) {
        count += 1;

        if (count > size) {
            list = (int*) realloc(list, sizeof(int)*size*2);
            assert (list);
            size *= 2;
        } 
        list[index] = input;
        index += 1;
    }

    /* debug */
    
    print_array(list, count); 
    return 0; 
}


void print_array(int *arr, int size) {
    int i=0;
    printf("The current array is:\n");
    for (i=0; i<size-1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[size-1]);
}

