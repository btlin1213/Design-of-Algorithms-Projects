/* * * * * * *
 * Park Ranger module for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Dian Lin
 */

#ifndef PARKRANGER_H
#define PARKRANGER_H
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
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
//   0 1                         /  1
//   0 2                        / /
//   1 2                        2
//   2 3                          \
//                                 3
//
// In this example your program should return `true` as there is a way to trim
// all trees in a single run. This run is (0, 1, 2, 3).
//
// Your function should must:
//  - Read in this data from stdin
//  - Store this data in an appropriate data structure
//  - Run the algorithm you have designed to solve this problem
//  - Do any clean up required (e.g., free allocated memory)
//  - Return `true` or `false` (included in the stdbool.h library)
//
// For full marks your algorithm must run in O(n + m) time.
bool is_single_run_possible();

// TODO: Add any additional functions or types required to solve this problem.


// the graph represented by arrays of linked lists 
typedef struct graph Graph;


struct graph {
    int total_v;
    Deque* array;
};

Graph *create_graph(int total_v);
void add_edge(Graph* graph, int from, int to);
void print_graph(Graph* graph);
Deque* top_sort(Graph* graph, int total_v);
void top_sort_recursive(int node_id, Deque* stack, int* visited, Graph* graph);
int check_stack(int node, Deque* stack);
void free_graph(Graph* graph, int total_v);
#endif
