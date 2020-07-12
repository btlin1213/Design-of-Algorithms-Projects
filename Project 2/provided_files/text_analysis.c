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
extern char* strdup(const char*);


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
  node->prev = NULL;
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
      curr->character[*string -'a'+1]->prev = curr;
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
    curr->character[0]->prev = curr;
    curr->character[0]->isLeaf = 1;
  }
  increase_freq(curr->character[0]);
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
  if (prefix_len <= 0) {
    // if required prefix is of length 0 or less then return nothing
    return;
  }
  char* new_prefix_string = (char*)malloc(prefix_len*sizeof(char));
  assert(new_prefix_string);
  int initial_level = -1;
  int initial_index = 0;
  recursive_find_prefix(root, new_prefix_string, initial_level, initial_index, prefix_len);
  free(new_prefix_string);
  free(root);
}


// Recursive function to find prefix of size required_len (modified pre-order traversal)
void recursive_find_prefix(Node* node, char* prefix_string, int level, int index, int required_len) {
  // base case - if adding the next char makes the required length (level+1==required_len) 
  // and the next char is $ (index > 0)
  if (level+1 == required_len && index > 0) {
    prefix_string[level] = node->data;
    // do not add the $ in level+1, make it an '\0' instead
    prefix_string[level+1] = END_OF_STRING;
    printf("%s %d\n", prefix_string, node->frequency);
    return;
  }
  // recursion - appending each letter to string
  // whenever $ is reached, it still goes through the for loop,
  // but a string with $ won't be printed as $ is always stored at index 0 
  // (so does not satisfy the if statement in base case)
  else {
    for (int i=0; i<ALPHABET_SIZE; i++) {
      if (node->character[i] != NULL) {
        prefix_string[level+1] = node->character[i]->data;
        recursive_find_prefix(node->character[i], prefix_string, level+1, i, required_len);
      }
    }
  }
}


void problem_2_c() {
  // 1. create root node
  Node *root = new_node(START_CHAR);
  // 2. read in N value
  int n=0;
  scanf("%d", &n);
  // 3. read in the stub string
  char* stub = (char*)malloc(MAX_STRING_LEN*sizeof(char));
  assert(stub);
  scanf("%s", stub);
  // 4. pass each subsequent string to insert_char to build trie
  for (int i=0; i<n; i++) {
    char* curr_string = (char*)malloc(MAX_STRING_LEN*sizeof(char));
    assert(curr_string);
    scanf("%s\n", curr_string);
    insert_char(root, curr_string);
  }
  // 5. pass stub to an altered search function to find node of last letter
  Node* stub_leaf = stub_search(root, stub);
  // 6. initialise priority queue 
  priorityQ* pq = new_priority_q();
  // 7. traverse its subtree
  int stub_freq = stub_leaf->frequency;
  char* string = (char*)malloc(MAX_STRING_LEN*sizeof(char));
  assert(string);
  int initial_level = -1;
  int initial_index = 0;
  traverse_subtree(stub_leaf, stub_freq, initial_level, initial_index, string, stub, pq);
  // 8. print out priority queue
  if (pq_is_empty(pq)) {
    return;
  }
  print_pq(pq, stub, MAX_AUTO_COMPLETE);
  // 9. free everything
  free(root);
  free(stub);
  free(stub_leaf);
}

void traverse_subtree(Node* node, int stub_freq, int level, int index, char* string, char* stub, priorityQ* pq) {
  for (int i=0; i<ALPHABET_SIZE; i++) {
    if (node->character[i] != NULL) {
      if (node->character[i]->data == END_CHAR) {
        // child is null, add current node to string and print it
        string[level] = node->data;
        string[level+1] = END_OF_STRING;
        int freq_w = node->character[i]->frequency;
        float probability = (float)freq_w/stub_freq;
        push_pq(pq, string, probability);
      }
      else {
        string[level+1] = node->character[i]->data; // add non-null child to string
        traverse_subtree(node->character[i], stub_freq, level+1, i, string, stub, pq);
      }
    }
  }
}

// iterative function to search for a string in Trie
Node* stub_search(Node* root, char* string) {
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
  // curr is last char in string
  return curr;
}

priorityQ *new_priority_q() {
  priorityQ *pq = malloc(sizeof(*pq));
  assert(pq);
  pq->top = NULL;
  pq->size = 0;
  return pq;
}

pqNode* new_pq_node(char* string, float probability) {
  pqNode* temp = malloc(sizeof(pqNode));
  temp->string = strdup(string);
  temp->priority = probability;
  temp->next = NULL;
  return temp;
}

void push_pq(priorityQ* pq, char* string, float probability) {
  pqNode* new = new_pq_node(string, probability);
  pqNode* curr = pq->top;
  // case 1: list is empty
  if (pq_is_empty(pq)) {
    pq->top = new;
    pq->size += 1;
  }
  // case 2: head of list has lower priority than new node
  // insert new node before head and change head
  else if (priority_cmp(curr, new)) {
    pq->top = new;
    pq->top->next = curr;
    pq->size += 1;
  }
  // case 3: head of list has higher priority than new node
  // insert new node in appropriate position
  else {
    while (curr->next != NULL && priority_cmp(new, curr->next)) {
      curr = curr->next;
    }
    // while loop finish either curr is end of list or curr's next element has smaller probability than new
    // insert new after curr
    new->next = curr->next;
    curr->next = new;
    pq->size += 1;   
  }
}

void print_pq(priorityQ* pq, char* stub, int k) {
  pqNode* curr = pq->top; 
  for (int i=0; i<k; i++) {
    if (curr) {
      printf("%.2f %s%s\n", curr->priority, stub, curr->string);
    }
    else {
      return;
    }
    // if there is no more nodes (less than 5 available, just break)
    if (curr->next == NULL) {
      return;
    }
    curr = curr->next;
  }
}

int pq_is_empty(priorityQ* pq) {
  return pq->top == NULL;
}

int priority_cmp(pqNode* a, pqNode* b) {
  // compare their probability
  if (a->priority < b->priority) {
    return TRUE;
  }
  else if (a->priority > b->priority) {
    return FALSE;
  }
  else {
    // equal probability, compare their string 
    // \0 > a > aa
    char* a_string = a->string;
    char* b_string = b->string;
    while (*a_string != END_OF_STRING && *b_string != END_OF_STRING) {
      if (*a_string > *b_string) {
        return TRUE;
      }
      else if (*a_string < *b_string) {
        return FALSE;
      }
      // move to next character
      a_string++;
      b_string++;
    }
    // if a_string finished earlier than b_string, then a is larger
    if (!*a_string) {
      return FALSE;
    }
    else {
      return TRUE;
    }
  }
}




