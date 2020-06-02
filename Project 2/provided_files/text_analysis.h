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

struct pq_node {
  char* string;
  float priority;
  pqNode* next;
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
void print_subtree(Node* node, int stub_freq, int level, int index, char* string, char* stub, pqNode* head);

// priority queue functions
pqNode* new_pq_node(char* string, float probability);
// void pop_pq(pqNode** head);
void push_pq(pqNode** head, char* string, float probability);
int pq_is_empty(pqNode** head);


#endif
