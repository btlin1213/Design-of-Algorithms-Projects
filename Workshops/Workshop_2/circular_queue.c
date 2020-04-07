/* implement circular queue via. unsorted array */

#include <stdio.h>
#define SIZE 5 // define a default size for the queue

/* global variables */
int queue[SIZE];
int front = -1, rear = -1;

/* function prototypes */
void enqueue(int element);
int dequeue();
void display();

int main (int argc, char *argv[]) {
    // fails because front = -1
    dequeue();
    // start adding elements to queue
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);
    // fail to enqueue because front == 0 and rear = SIZE-1 (queue is full)
    enqueue(6);
    // show current queue
    display();    
    // dequeue the first item (1)
    dequeue();
    // show queue without first item
    display();
    // add an item to end of queue, push front and rear pointer along by 1
    enqueue(7);
    // show full queue with last item as 7
    display();
    // fail to enqueue because front == rear + 1
    enqueue(8);
    return 0;
}


void enqueue(int element) {
    // case 1: empty queue
    if (front == -1) {
        front += 1;
        rear += 1;
        queue[rear] = element;
        printf("%d is successfully enqueued at index %d\n", element, rear);
    }
    // case 2: full queue
    else if ((rear+1) % SIZE == front) {
        printf("ERROR: Queue is full. Enqueue failed.\n");
    }
    // case 3: standard queue (at least 1 element in queue, including ONLY 1 element in queue, not impacted by enqueueing)
    else {
        // NOTE: rear+1%SIZE takes care of both wrapping and non-wrapping cases via. Remainders
        rear = (rear+1)%SIZE;
        queue[rear] = element;
        printf("%d is successfully enqueued at index %d\n", element, rear);
        // NOTE: don't need to care about front as front is only incremented by dequeueing
    }
}

int dequeue() {
    int element;
    // case 1: empty queue
    if (front == -1) {
        printf("ERROR: Queue is empty. Dequeue failed.\n");
        return -1;
    }
    // case 2: only 1 element in queue (must reset after dequeueing)
    else if (front == rear) {
        element = queue[front];
        front = -1;
        rear = -1;
        printf("%d is successfully dequeued from index %d\n", element, front);
        return element;
    }
    // case 3: standard queue (at least 1 element in queue, include full queue, not impacted by dequeueing)
    // conditional statement: ((rear+1) % SIZE == front) 
    else {
        element = queue[front];
        front = (front+1)%SIZE;
        printf("%d is successfully dequeued from index %d\n", element, front);
        // NOTE: don't need to care about rear as rear is only incremented by enqueueing
        return element;
    }
}

void display() {
    // case 1: empty queue
    int i=0;
    if (front == -1) {
        printf("The queue is empty.\n");
    }
    // case 2: standard queue (at least 1 element, include full queue)
    else {
        printf("The queue looks like: \n");
        // case 2a: linear queue (no wrapping)
        // front == rear means only 1 element in queue, still linear
        if (front <= rear) {
            for (i=front; i<rear+1; i++) {
                printf("%d\n", queue[i]);
            }
        }
        // case 2b: circular queue (wrapping)
        else {
            // first half of queue
            for (i=0; i<=rear; i++) {
                printf("%d\n", queue[i]);
            }
            // second half of queue
            for (i=front; i<SIZE; i++) {
                printf("%d\n", queue[i]);
            }
        }
    }
}
