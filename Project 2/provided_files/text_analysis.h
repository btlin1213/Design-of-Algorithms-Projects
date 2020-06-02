/* * * * * * *
 * Text Analysis module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Dian Lin
 */

#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H


// The Nodes which make up the doubly-linked list
typedef struct node Node;
typedef struct prefix_list_node prefixListNode;
typedef struct prefix_list prefixList;

struct node {
    char data;
    int frequency;
    int isLeaf;
    Node* character[27];
    Node* prev;
};

struct prefix_list {
  prefixListNode *top;
  prefixListNode *bottom;
  int size;
};

struct prefix_list_node {
    char* string;
    int frequency;
    prefixListNode* next;
};

void problem_2_a();
Node *new_node(char data);
void insert_char(Node* root, char* string);
int search(Node* root, char* string);
void pre_order(Node* root);
void increase_freq(Node* node);

// Using the trie constructed in Part (a) this program should output all
// prefixes of length K, in alphabetic order along with their frequencies
// with their frequencies. The input will be:
//   n k
//   str_0
//   ...
//   str_(n-1)
// The output format should be as follows:
//   an 3
//   az 1
//   ba 12
//   ...
//   ye 1
void problem_2_b();
void recursive_find_prefix(Node* node, int level, int index, int size, char* prefix);
// void recursive_find_prefix(Node* node, char* prefix_string, prefixList* prefix_list, int required_len);
prefixListNode *new_prefixList_node(char* string, int freq);
void add_prefix_to_list(prefixList* prefix_list, char* prefix, int freq);
prefixList *new_prefix_list();
void search_prefix(Node* root, char* stub);
void print_prefix_list(prefixList *list);
void append_to_string(char* string, char character);
// Again using the trie data structure you implemented for Part (a) you will
// provide a list (up to 5) of the most probable word completions for a given
// word stub.
//
// For example if the word stub is "al" your program may output:
//   0.50 algorithm
//   0.25 algebra
//   0.13 alright
//   0.06 albert
//   0.03 albania
//
// The probabilities should be formatted to exactly 2 decimal places and
// should be computed according to the following formula, for a word W with the
// prefix S:
//   Pr(word = W | stub = S) = Freq(word = W) / Freq(stub = S)
//
// The input to your program will be the following:
//   n
//   stub
//   str_0
//   ...
//   str_(n-1)
// That is, there are n + 1 strings in total, with the first being the word
// stub.
//
// If there are two strings with the same probability ties should be broken
// alphabetically (with "a" coming before "aa").
void problem_2_c();

#endif
