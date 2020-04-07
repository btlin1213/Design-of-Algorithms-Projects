#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void print_array(int *arr, int size) {
    int i=0;
    printf("The current array is:\n");
    for (i=0; i<size; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}


int main() {
    int* list = (int*) malloc(sizeof(int)*4);
    assert (list);
    int size = 0;
    size = sizeof(list) / sizeof(int);
    printf("before allocating elements, array size: %d\n", size);

    list[0] = 121212;
    list[1] = 131313;
    list[2] = 141414;
    list[3] = 151515;
    size = sizeof(list) / sizeof(int);
    printf("after allocating elements, array size: %d\n", size);
    print_array(list, 4);
    return 0;
}