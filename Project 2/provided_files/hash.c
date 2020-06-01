/* * * * * * *
 * Hashing module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Dian Lin
 */

#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAX_STRING_LENGTH 256
#define UPPERCASE_CHR_DIFFERENCE -39
#define LOWERCASE_CHR_DIFFERENCE -97
#define NUMBER_CHR_DIFFERENCE 4
#define BINARY_LENGTH 64
#define TRUE 1
#define FALSE 0

// command for testing files
// diff -B tests/p1a-out-1.txt <(./a2 p1a < tests/p1a-in-1.txt)

// Implements a solution to Problem 1 (a), which reads in from stdin:
//   N M
//   str_1
//   str_2
//   ...
//   str_N
// And outputs (to stdout) the hash values of the N strings 1 per line.
void problem_1_a() {
  // 1. read in the N and M values
  int n = 0, m = 0;
  scanf("%d %d", &n, &m);
  
  // 2. initialise an int array of size N
  int *hash_values = (int*)malloc(n*sizeof(int));
  assert(hash_values);

  // 3. read in strings and calculate their hash value and store in hash_values array
  for (int j=0; j<n; j++) {
    char* string = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
    assert(string);
    scanf("%s\n", string);
    int hash_value = hash(string, m);
    hash_values[j] = hash_value;
  }

  // // 4. print the hash values to stdout
  // for (int k=0; k<n; k++) {
  //   printf("%d\n", hash_values[k]);
  // }
}

int hash(char* string, int m) {
  // initial hash_value is chr(first_character)
  int hash_value = chr(string[0]);
  int length = strlen(string);
  // calculate and accumulate hash value for each letter
  for (int i=1; i<length; i++) {
    char character = string[i];
    int chr_value = chr(character);
    hash_value = (hash_value * BINARY_LENGTH + chr_value) % m;
  }
  return hash_value;
}

int chr(char character) {
  int chr_value;
  // classify character as capital/small letter or number
    if (character >= 'A' && character <= 'Z') {
      // case 1: upper case
      chr_value = (int) character + UPPERCASE_CHR_DIFFERENCE;
    }
    else if (character >= 'a' && character <= 'z') {
      // case 2: lower case
      chr_value = (int) character + LOWERCASE_CHR_DIFFERENCE;
    }
    else {
      // case 3: number
      chr_value = (int) character + NUMBER_CHR_DIFFERENCE;
    }
  return chr_value;
}



// Implements a solution to Problem 1 (b), which reads in from stdin:
//   N M K
//   str_1
//   str_2
//   ...
//   str_N
// Each string is inputed (in the given order) into a hash table with size
// M. The collision resolution strategy must be linear probing with step
// size K. If an element cannot be inserted then the table size should be
// doubled and all elements should be re-hashed (in index order) before
// the element is re-inserted.
//
// This function must output the state of the hash table after all insertions
// are performed, in the following format
//   0: str_k
//   1:
//   2: str_l
//   3: str_p
//   4:
//   ...
//   (M-2): str_q
//   (M-1):
void problem_1_b() {
  // 1. read in the N, M and K values
  int n = 0, m = 0, k = 0;
  scanf("%d %d %d", &n, &m, &k);
  int* m_ptr = &m;
  // 2. create initial hash table of size M
  char** hash_table = (char**)malloc(m*sizeof(*hash_table));
  assert(hash_table);
  for (int i=0; i<m; i++) {
    hash_table[i] = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
    assert(hash_table[i]);
    hash_table[i] = NULL;
  }
  for (int i=0; i<n; i++) {
    // 3. read in a string and find its hash value
    char* string = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
    assert(string);
    scanf("%s\n", string);
    int hash_value = hash(string, m);
    // 4. insert into hashtable 
    hash_table = insert(hash_table, string, hash_value, m, k, m_ptr);
  }
  // 5. print to stdout
  for (int i=0; i<*m_ptr; i++) {
    if (hash_table[i]==NULL) {
      printf("%d:\n", i);
    }
    else {
       printf("%d: %s\n", i, hash_table[i]);
    }
  }
}

// insert returns hash table after this insertion 
char** insert(char** hash_table, char* string, int hash_value, int m, int k, int* m_ptr) {
  // NOTE there will never be case where initial hash value is out of range (because mod m)
  // case 1 - spot is free
  if (hash_table[hash_value] == NULL) {
    // insert string in its spot
    hash_table[hash_value] = string; 
  }
  // case 2 - spot is not free 
  else {
    // traverse
    int initial_hash_value = hash_value;
    
    while (hash_table[hash_value] != NULL) {
      // printf("string %s with hash value %d\n", string, hash_value);
      hash_value += k;
      if (hash_value > m) {
        // wrap around
      hash_value %= m;
      }
      if (hash_table[hash_value] == NULL) {
        // if space found, insert string 
        hash_table[hash_value] = string;
        break;
      }
      else if (hash_value == initial_hash_value) {
        // cycle, need to resize hashtable
        // printf("string %s with hash value %d needs resize\n", string, hash_value);
        hash_table = resize_hash_table(hash_table, m, k, string, m_ptr);
        // printf("current string is %s with hash value %d and hash table size %d\n", string, hash_value, m);
        break; // BREAK HERE IS NECESSARY, UNCOMMENT PRINT STATEMENT ABOVE TO SEE WHY 
      }
    }
  }
  // printf("\n below printing from within insert()\n");
  // for (int i=0; i<12; i++) {
  //   printf("%d: %s\n", i, hash_table[i]);
  // }
  return hash_table;
}


char** resize_hash_table(char** hash_table, int m, int k, char* string, int* m_ptr) {
  // printf("string %s with hashtable size %d and stepsize %d\n", string, m, k);
  
  // make new hashtable of double the original size
  char** new_hash_table = (char**)malloc(2*m*sizeof(*hash_table));
  assert(new_hash_table);
  
  // make each pointer in new hashtable point to null
  for (int i=0; i<2*m; i++) {
    new_hash_table[i] = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
    assert(new_hash_table[i]);
    new_hash_table[i] = NULL;
  }
  // traverse old hash table and rehash each string into new hashtable
  for (int i=0; i<m; i++) {
    if (hash_table[i] != NULL) {
      *m_ptr = 2*m;
      new_hash_table = insert(new_hash_table, hash_table[i], hash(hash_table[i], 2*m), 2*m, k, m_ptr);
    }
  }
  // re-insert current string
  new_hash_table = insert(new_hash_table, string, hash(string, 2*m), 2*m, k, m_ptr);
  free(hash_table);
  hash_table = new_hash_table;
  return hash_table;
}


void free_hash_table(char** hash_table, int m) {
  for (int i=0; i < m; i++) {
    free(hash_table[i]);
  }
  free(hash_table);
}
