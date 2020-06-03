/* * * * * * *
 * Text Analysis module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Dian Lin
 */

#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H


// The Nodes which make up the doubly-linked list for trie 
typedef struct node Node;

struct node {
    char data;
    int frequency;
    int isLeaf;
    Node* character[27];
    Node* prev;
};


// Implementing priority queue for 2c
typedef struct pq_node pqNode;
typedef struct priority_q priorityQ;

struct pq_node {
  char* string;
  float priority;
  pqNode* next;
};

struct priority_q {
  pqNode* top;
  int size;
};


void problem_2_a();
Node *new_node(char data);
void insert_char(Node* root, char* string);
void pre_order(Node* root);
void increase_freq(Node* node);


void problem_2_b();
void recursive_find_prefix(Node* node, int level, int index, int required_len, char* prefix);


void problem_2_c();
Node* stub_search(Node* root, char* string);
void traverse_subtree(Node* node, int stub_freq, int level, int index, char* string, char* stub, priorityQ* pq);

// priority queue functions

// Create a new empty priority queue and return a pointer to it
priorityQ *new_priority_q();
// malloc a new pqNode with given string and probability, return pointer to it
pqNode* new_pq_node(char* string, float probability);
// add element to priority queue
void push_pq(priorityQ* pq, char* string, float probability);
// print top k elements of priority queue
void print_pq(priorityQ* pq, char* stub, int k); 
// check if pq is empty
int pq_is_empty(priorityQ* pq);
// compare priority, return 1 if a < b (b goes in front of a in the queue)
int priority_cmp(pqNode* a, pqNode* b);




#endif
