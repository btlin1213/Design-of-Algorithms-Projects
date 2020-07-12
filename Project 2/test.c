#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAX_STRING_LENGTH 256
char** resize_hash_table(char** hash_Table, int m, char* string);

int main(int argc, char**argv) {
   
    char **hash_table = (char**)malloc(3*sizeof(char*));
    assert(hash_table);
    for (int i=0; i<3; i++) {
        hash_table[i] = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
        assert(hash_table[i]);
        hash_table[i] = "yo";
    } 

    printf("this is hashtable before resize:\n");
    for (int i=0; i<3; i++) {
      printf("%d: %s\n", i, hash_table[i]);
    }

    hash_table = resize_hash_table(hash_table, 3, "hello");

    printf("this is new hashtable after resize:\n");

    int i=0;
    while (hash_table[i] != '\0') {
      printf("%d: %s\n", i, hash_table[i]);
      i++;
    }

    return 0;
} 



char** resize_hash_table(char** hash_table, int m, char* string) {
  // make new hashtable of double the original size, +1 to insert an ending flag
  char** new_hash_table = (char**)realloc(hash_table, (2*m+1)*sizeof(char*));

  assert(new_hash_table);


  // make each pointer in new hashtable point to null
  for (int i=0; i<2*m; i++) {
    new_hash_table[i] = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
    assert(new_hash_table[i]);
    new_hash_table[i] = NULL;
  }

  // traverse old hash table and rehash each string into new hashtable, also free them after rehashing
  for (int i=0; i<m; i++) {
    if (hash_table[i] != NULL) {
      new_hash_table[i] = hash_table[i]; 
    }
    // free it outside if-loop (still need to free even if null pointer)
    // free(hash_table[i]);
  }

  // insert new string to remainder of new hashtable
  for (int i=m; i<2*m; i++) {
    new_hash_table[i] = string;
  }

  // insert end flag to last elem of new hashtable
  new_hash_table[2*m+1] = "\0";

  // do not free old hashtable pointer
  // free(hash_table);
  return new_hash_table;
}

