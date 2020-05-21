#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
typedef struct Graph Graph;

struct node *createNode(int v);
struct Graph *createGraph(int vertices, int edges);
void addEdge(struct Graph *graph, int src, int dest);
void printGraph(struct Graph *graph);
int isBridge(struct Graph* graph, int u);

void fleury(struct Graph *graph, int u);

#endif