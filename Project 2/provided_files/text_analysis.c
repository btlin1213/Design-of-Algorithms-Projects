/* * * * * * *
 * Text Analysis module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Dian Lin
 */

#include "text_analysis.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define START_CHAR '^'
#define END_CHAR '$'
#define END_OF_STRING '\0'
#define MAX_STRING_LEN 100 // 99 letters + '\0'
#define ALPHABET_SIZE 27 // 26 letters + $
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
  // 3. pass each string to insert_char function
  for (int i=0; i<n; i++) {
    char* curr_string = (char*)malloc(MAX_STRING_LEN*sizeof(char));
    assert(curr_string);
    scanf("%s\n", curr_string);
    insert_char(root, curr_string);
  }
  // 4. starting from root, do pre-order traversal and print each node data
  pre_order(root);
}

Node *new_node(char data) {
  Node *node = (Node*)malloc(sizeof(*node));
  assert(node);
  node->data = data;
  node->frequency = 0;
  node->isLeaf = 0;
  for (int i=0; i<ALPHABET_SIZE; i++) {
    node->character[i] = NULL;
  }
  return node;
}

// insert_char characters of this string into trie
void insert_char(Node* root, char* string) {
  // increase frequency of root everytime a string is insert_chared
  increase_freq(root);
  // iterate through each char of string
  Node* curr = root;
  while (*string) {
    if (curr->character[*string-'a'+1] == NULL) {
      // create new node if this path does not exist yet
      curr->character[*string -'a'+1] = new_node(*string);
    }
    // go to next node
    curr = curr->character[*string-'a'+1];
    increase_freq(curr);
    // move to next character
    string++;
  }
  if (curr->character[0] == NULL) {
    // insert leaf node and mark it as leaf
    curr->character[0] = new_node(END_CHAR);
    curr->character[0]->isLeaf = 1;
  }
  increase_freq(curr->character[0]);
}

// iterative function to search for a string in Trie
int search(Node* root, char* string) {
  // return 0 (false) if trie is empty
  if (root == NULL) {
    return 0;
  }
  Node* curr = root;
  while (*string) {
    // go to next node
    curr = curr->character[*string-'a'+1];
    // if reached leaf node, this string is invalid
    if (curr->data == END_CHAR) {
      return 0;
    }
    // move to next character
    string++;
  }
  // we are at end of string now, so if current node's next node is a $ then valid string
  curr = curr->character[0];
  return curr->isLeaf;
}

// print preorder traversal of tree
void pre_order(Node* root) {
  if (root == NULL) {
    return;
  }
  printf("%c\n", root->data);
  for (int i=0; i<ALPHABET_SIZE; i++) {
    if (root->character[i] != NULL) {
      pre_order(root->character[i]);
    }
  }
  // free this node
  free(root);
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
  // 1. create root node
  Node *root = new_node(START_CHAR);
  // 2. read in N and K value
  int n=0, prefix_len=0;
  scanf("%d %d", &n, &prefix_len);
  // 3. pass each string to insert_char to build trie
  for (int i=0; i<n; i++) {
    char* curr_string = (char*)malloc(MAX_STRING_LEN*sizeof(char));
    assert(curr_string);
    scanf("%s\n", curr_string);
    insert_char(root, curr_string);
  }
  // 4. find and print prefix of length n and their respective frequency
  // flag to indicate whether we are in middle of putting together a prefix string
  if (prefix_len <= 0) {
    // if required prefix is of length 0 or less then return nothing
    return;
  }
  prefixList *prefix_list = new_prefix_list();
  int initial_level = 1;

  for (int i=0; i<ALPHABET_SIZE; i++) {
    if (root->character[i] != NULL) {
      
      recursive_find_prefix(root->character[i], prefix_len, initial_level, prefix_list, NULL);
    }
  }

  // // 5. print the prefix list as required
  // prefixListNode* curr_prefix_list_node = prefix_list->top;
  // for (int i=0; i<prefix_list->size; i++) {
  //   printf("%s %d\n", curr_prefix_list_node->string, curr_prefix_list_node->frequency);
  //   curr_prefix_list_node = curr_prefix_list_node->next;
  // }
}


// Recursive function to find prefix of size prefix_len
void recursive_find_prefix(Node* node, int prefix_len, int level, prefixList* prefix_list, char* prefix) {
  size_t unit = 1;
  if (prefix == NULL) {
    // malloc memory for a new string (starting to put together a new prefix)
    char* prefix = malloc(unit*sizeof(char));
    assert(prefix);
  }

  // debug statements
  printf("finding the children of %c on level %d\n", node->data, level);
  printf("prefix list looks like: \n");
  print_prefix_list(prefix_list);

  // append current node value to prefix
  Node* curr = node;
  prefix = realloc(prefix, unit*sizeof(char));
  assert(prefix);  
  append_to_string(prefix, curr->data);

  printf("prefix string is %s right now\n", prefix);
  // printf("curr is pointing to %c\n", curr->data);
  // printf("currently putting together prefix string %s, up to level %d\n", prefix, level);

  // if reached prefix_len then stop checking further
  if (level == prefix_len) {
    // add prefix to prefix list
    int freq = curr->frequency;
    add_prefix_to_list(prefix_list, prefix, freq);
    // delete last char from prefix string?
    prefix = prefix
    free(prefix);
    return;
  }
  // if have not reached prefix_len, keep recursively traversing its children
  else {
    for (int i=0; i<ALPHABET_SIZE; i++) {
      if (curr->character[i]->data == END_CHAR) {
        continue;
      }
      else if (curr->character[i] != NULL) {
        recursive_find_prefix(curr->character[i], prefix_len, level+1, prefix_list, prefix);
        printf("when we are on node %c of level %d, the prefix string so far is %s\n", curr->data, level, prefix);
      }
    } 
  }
}

void append_to_string(char* string, char character) {
  size_t length = strlen(string);
  string[length] = character;
  string[length+1] = END_OF_STRING;
}


// Return new node for prefix list
prefixListNode *new_prefixList_node(char* string, int freq) {
  prefixListNode *node = (prefixListNode*)malloc(sizeof(*node));
  assert(node);
  node->string = (char*)malloc(MAX_STRING_LEN*sizeof(char));
  assert(node->string);
  node->string = string;
  node->frequency = freq;
  node->next = NULL;
  return node;
}


// Add an element to the bottom of a prefix list
void add_prefix_to_list(prefixList* prefix_list, char* prefix, int freq) {
  prefixListNode *new_prefix_node = new_prefixList_node(prefix, freq);

  if (prefix_list->size > 0) {
    prefix_list->bottom->next = new_prefix_node;
  }
  else {
    prefix_list->top = new_prefix_node;
  }
  prefix_list->bottom = new_prefix_node;
  prefix_list->size += 1;
}

// Return a new prefix lsit
prefixList *new_prefix_list() {
	prefixList *newPrefixList = (prefixList*)malloc(sizeof(prefixList*));
	assert(newPrefixList);
  newPrefixList->top = NULL;
  newPrefixList->bottom = NULL;
  newPrefixList->size=0;
	return newPrefixList;
}

void print_prefix_list(prefixList *list) {
  prefixListNode *current = list->top;
  int i = 0;
  printf("[");
  while (current) {
    printf("%s %d", current->string, current->frequency);
    // Print a comma unless we just printed the final element
    if (i < list->size - 1) {
      printf(", ");
    }
    current = current->next;
    i++;
  }
  printf("]\n");
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
//   // 1. create root node
//   Node *root = new_node(START_CHAR);
//   // 2. read in N value
//   int n=0;
//   scanf("%d", &n);
//   // 3. read in the stub string
//   char* stub = (char*)malloc(MAX_STRING_LEN*sizeof(char));
//   assert(stub);
//   scanf("%s", stub);
//   // 4. pass each subsequent string to insert_char to build trie
//   for (int i=0; i<n; i++) {
//     char* curr_string = (char*)malloc(MAX_STRING_LEN*sizeof(char));
//     assert(curr_string);
//     scanf("%s\n", curr_string);
//     insert_char(root, curr_string);
//   }
//   // 5. pass stub to an altered search function
//   search_prefix(root, stub);
  
}

// void search_prefix(Node* root, char* stub) {
//   // return 0 (false) if trie is empty
//   if (root == NULL) {
//     return 0;
//   }
//   Node* curr = root;
//   while (*stub) {
//     // go to next node
//     curr = curr->character[*stub-'a'+1];
//     // if reached leaf node, this string is invalid
//     if (curr->data == END_CHAR) {
//       return 0;
//     }
//     // move to next character
//     stub++;
//   }
//   // we are at end of stub now, so add the rest of current node's children to a list and print out
//   preorder_prediction(curr);
// }

// void preorder_prediction(Node* root) {
//   // singly linked list to store print-outs
//   prefixList *newList = new_prefix_list();

//   if (root == NULL) {
//     printf("0");
//     return;
//   }

//   prefixListNode *newNode = new_prefixList_node();
// }