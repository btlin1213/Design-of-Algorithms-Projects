/* * * * * * *
 * Text Analysis module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

#include "text_analysis.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define START_CHAR "^"
#define END_CHAR "$"
#define END_OF_STRING "\0"
#define MAX_STRING_LEN 99
#define ALPHABET_SIZE 26
#define TRUE 1
#define FALSE 0

// The input to your program is an integer N followed by N lines containing words of length < 100 characters, containing only lowercase letters.
// Branches should be ordered in alphabetic order.
// Output the pre-order traversal of the characters in the trie, on a single line.
void problem_2_a() {
  // 1. create root node
  Node *root = new_node(START_CHAR);

  // 2. read in N value
  int n=0;
  scanf("%d", &n);

  // 3. pass each string to insert function
  for (int i=0; i<n; i++) {
    char* curr_string = (char*)malloc(MAX_STRING_LEN*sizeof(char));
    assert(curr_string);
    scanf("%s\n", curr_string);
    insert(root, curr_string);
  }
  
  // 4. starting from root, do pre-order traversal and print each node data
  pre_order(root);
}

Node *new_node(Data data) {
  Node *node = malloc(sizeof(*node));
  assert(node);
  node->data = data;
  node->frequency = 0;
  node->firstChild = NULL;
  node->sibling = NULL;
  return node;
}

// insert characters of this string into trie
void insert(Node* root, char* string) {
  // increase frequency of root
  increase_freq(root);
  // iterate through each char of string
  int i=0;
  Node* head = root;
  while (string[i] != END_OF_STRING) {
    // place current character in a node
    Node *curr_char = new_node(string[i]);
    // if root has no children yet, insert this char as first child
    if (head->firstChild == NULL) {
      head->firstChild = curr_char;
    }
    // go to next node and go to next char in string
    head = head->firstChild;
    i++;    
  }
  // insert leaf node to indicate end of this string
  Node *leaf = new_node(END_CHAR);
  head->firstChild = leaf;
}

// determine whether this prefix is in trie
int search() {

}

// determine whether this node is the end of a string
int is_leaf(Node node) {

}

// print preorder traversal of tree
void pre_order(Node* root) {

}

// increase frequency of a node
void increase_freq(Node* node) {
  node->frequency += 1;
}


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
void problem_2_b() {
  // TODO: Implement Me!
}

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
void problem_2_c() {
  // TODO: Implement Me!
}
