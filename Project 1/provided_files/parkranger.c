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
  // printf("\nfrom is %d and to is %d\n", from, to);

  // print the graph
  print_graph(graph);

  // topo-sort 
  Deque* topo_deque = top_sort(graph, v);

  // print stack as is
  print_deque(topo_deque);
  // print topo-sorted order (reversed stack)
  iterative_reverse(topo_deque);
  print_deque(topo_deque);
  
  // exit_with_error("is_single_run_possible not implemented");
  return false;
}

// TODO: Add any additional functions or types required to solve this problem.

// create graph of total_v number of vertices (0 is mountain, 1- is trees)
Graph *create_graph(int total_v) {
  Graph* graph = malloc(sizeof(Graph));
  graph->total_v = total_v; // total_v = 4

  // malloc space for the array to allow total_v number of linked lists
  graph->array = malloc((total_v+1) * sizeof(Deque));

  // initialise head of each linked list to NULL
  for (int i=0; i<(total_v+1); i++) {
    graph->array[i].head = NULL;
  }
  return graph;
}

// add edge to graph
void add_edge(Graph* graph, int from, int to) {
  ParkNode* new_node = malloc(sizeof(ParkNode));
  new_node->dest = to;
  new_node->next = NULL;
  

  // if empty list
  if (graph->array[from].head == NULL) {
    graph->array[from].head = new_node;
  } else {
    // add the ParkNode at end to ensure it's sorted in ascending 
    ParkNode* curr = malloc(sizeof(ParkNode));
    curr = graph->array[from].head;
    while (curr->next) {
      // curr is at last ParkNode by the end of while-loop
      curr = curr->next;
    }
    // insert new ParkNode after curr
    curr->next = new_node;
    new_node->next = NULL;
  }
}

// print graph (represented by adjacency lists)
void print_graph(Graph* graph) {
  for (int i=0; i<(graph->total_v+1); i++) {
    ParkNode* curr = graph->array[i].head;
    printf("%d :", i);

    while (curr) {
      printf(" -> %d", curr->dest);
      curr = curr->next;
    }
    printf("\n");
  }
}

// topological sort 
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
      top_sort_recursive(i, i, stack, visited, graph);
    }
  }
  return stack;
}

void top_sort_recursive(int node_id, int prev_node, Deque* stack, int* visited, Graph* graph) {
  visited[node_id] = 1;
  
  if (graph->array[node_id].head != NULL) {
    // iterate through adjacent list of current node
    ParkNode* curr = graph->array[node_id].head; 
    while (curr->next != NULL) {
      if (visited[curr->dest] == 0) {
        top_sort_recursive(curr->dest, node_id, stack, visited, graph);
      }
      curr = curr->next;
    }
  }
  // empty adjacent list
  deque_insert(stack, node_id);
   
}

