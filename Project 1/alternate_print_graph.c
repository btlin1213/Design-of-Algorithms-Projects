void print_graph(Graph* graph) {
  Node* mountain = graph->array[0].head;
    printf("\nadjacency list of mountain \n");
    while (mountain) {
      printf("%d -> ", mountain->dest);
      mountain = mountain->next;
    }
    printf("\n");

  for (int i=1; i<(graph->total_v+1); i++) {
    Node* curr = graph->array[i].head;
    printf("adjacency list of tree %d \n", i);
    while (curr) {
      printf("%d -> ", curr->dest);
      curr = curr->next;
    }
    printf("\n");
  }
}
