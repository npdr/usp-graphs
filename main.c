#include "graph.h"

int main()
{
    int n = 5, e = 6;
    struct Graph *graph = createGraph(n, e);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 3, 4);

    printf("Path => ");
    fleury(graph, 0);
    printf("\n");

    return 0;
}