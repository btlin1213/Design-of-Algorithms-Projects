/* * * * * * *
 * Park Ranger module for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Dian Lin
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parkranger.h"
#include "util.h"
#include "deque.h"
// This function must read in a ski slope map and determine whether or not
// it is possible for the park ranger to trim all of the trees on the ski slope
// in a single run starting from the top of the mountain.
//
// The ski slope map is provided via stdin in the following format:
//
//   n m
//   from to
//   from to
//   ...
//   from to
//
// Here n denotes the number of trees that need trimming, which are labelled
// {1, ..., n}. The integer m denotes the number "reachable pairs" of trees.
// There are exactly m lines which follow, each containing a (from, to) pair
// which indicates that tree `to` is directly reachable from tree `from`.
// `from` and `to` are integers in the range {0, ..., n}, where {1, ..., n}
// denote the trees and 0 denotes the top of the mountain.
//
// For example the following input represents a ski slope with 3 trees and
// 4 reachable pairs of trees.
//
// input:            map:          0
//   3 4                          / \
//   0 1                         /  2
//   0 2                        / /
//   2 1                        1
//   1 3                          \
//                                 3
//
// In this example your program should return `true` as there is a way to trim
// all trees in a single run. This run is (0, 2, 1, 3).
//
// Your function should must:
//  - Read in this data from stdin
//  - Store this data in an appropriate data structure
//  - Run the algorithm you have designed to solve this problem
//  - Do any clean up required (e.g., free allocated memory)
//  - Return `true` or `false` (included in the stdbool.h library)
//
// For full marks your algorithm must run in O(n + m) time.

bool is_single_run_possible() {

  // read from stdin
  // v = number of trees (range (1 to v+1)) 
  // e = number of edges (subsequent lines to be read)
  int v, e;
  int from, to;
  scanf("%d %d", &v, &e);

  // create the graph
  Graph *graph = create_graph(v);

  // read in subsequent lines and add edges
  for (int i=0; i<e; i++) {
    scanf("%d %d", &from, &to);
    add_edge(graph, from, to);
  }

  // print the graph if needed
  // print_graph(graph);

  // topo-sort 
  Deque* topo_deque = top_sort(graph, v);
  // reverse stack for topo-sorted order 
  iterative_reverse(topo_deque);
  
  // check if every node in topo_deque has direct edge
  Node* curr = topo_deque->top;
  while (curr->next != NULL) {
    if (check_stack(curr->next->data, &graph->array[curr->data]) == 0) {
      return false;
    }
    curr = curr->next; 
  }
  return true;
  // exit_with_error("is_single_run_possible not implemented");
}

// function to create graph of total_v number of vertices 
// (0 is mountain, 1- is trees)
Graph *create_graph(int total_v) {
  Graph* graph = malloc(sizeof(Graph));
  graph->total_v = total_v; // total_v = 4

  // malloc space for the array to allow total_v number of linked lists
  graph->array = malloc((total_v+1) * sizeof(Deque));

  // initialise top of each linked list to NULL
  for (int i=0; i<(total_v+1); i++) {
    graph->array[i] = *new_deque();
  }
  return graph;
}

// function to add an edge to given graph
void add_edge(Graph* graph, int from, int to) {
  deque_insert(&graph->array[from], to);
}

// function to print graph (represented by adjacency lists)
void print_graph(Graph* graph) {
  for (int i=0; i<(graph->total_v+1); i++) {
    printf("%d :", i);
    print_deque(&graph->array[i]);

  // another way to print the graph (more clearly with arrows)
  //   Node* curr = graph->array[i].top;
  //   printf("%d :", i);

  //   while (curr) {
  //     printf(" -> %d", curr->next);
  //     curr = curr->next;
  //   }
  //   printf("\n");

  }
  printf("\n");
}

// starter function for topological sort 
Deque* top_sort(Graph* graph, int total_v) {
  // initialise stack
  Deque* stack = new_deque();

  // dynamically initialise array 
  int* visited;
  visited = (int*) malloc((total_v+1) * sizeof(int));
  assert(visited);
  // mark all nodes in visited to false
  for (int i=0; i<(total_v+1); i++) {
    visited[i] = 0;
  }

  for (int i=0; i<(total_v+1); i++) {
    if (visited[i] == 0) {
      top_sort_recursive(i, stack, visited, graph);
    }
  }
  return stack;
}

// recursive helper function for topological sort 
void top_sort_recursive(int node_id, Deque* stack, int* visited, Graph* graph) {
  // mark current node as visited
  visited[node_id] = 1;

  // case 1: empty adjacency list (no adjacent nodes)
  if (graph->array[node_id].top == NULL) {
    // push it to the stack
    deque_insert(stack, node_id);
  }

  // case 2: there are adjacent nodes
  else {
    Node* curr = graph->array[node_id].top;
    // check if all adjacent nodes are in stack, if so, push current node
    while (curr != NULL) {
      if (check_stack(curr->data, stack) == 0) {
        top_sort_recursive(curr->data, stack, visited, graph);
      }
      curr = curr->next;
    }
    // all adjacent nodes are in stack
    deque_insert(stack, node_id);
  }
}

// function to check whether given node is in given deque
int check_stack(int node, Deque* stack) {
  if (stack->top == NULL) {
    return 0;
  }
  Node* curr = stack->top; 
  while (curr != NULL) {
    if (curr->data == node) {
      // yes in stack
      return 1;
    }
    curr = curr->next;
  }
  return 0;
}