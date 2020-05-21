#include "graph.h"

struct node
{
    int vertex;
    int mark;
    int removed;
    struct node *next;
};

struct Graph
{
    int numVertices;
    int edge;
    int *visited;

    struct node **adjLists;
};

struct node *createNode(int v)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->mark = 0;
    newNode->removed = 0;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int vertices, int edges)
{
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->edge = edges;

    graph->adjLists = malloc(vertices * sizeof(struct node *));

    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(struct Graph *graph, int src, int dest)
{
    struct node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void markUtil(struct Graph *graph, int u, int v)
{
    struct node *temp1 = (graph->adjLists[u]);
    while (temp1 && temp1->vertex != v)
        temp1 = temp1->next;
    temp1->mark = 1;

    struct node *temp2 = (graph->adjLists[v]);
    while (temp2 && temp2->vertex != u)
        temp2 = temp2->next;
    temp2->mark = 1;
}

int isMarked(struct Graph *graph, int u, int v)
{
    struct node *temp1 = (graph->adjLists[u]);
    while (temp1 && temp1->vertex != v)
        temp1 = temp1->next;

    struct node *temp2 = (graph->adjLists[v]);
    while (temp2 && temp2->vertex != u)
        temp2 = temp2->next;

    if (temp1->mark == 1 && temp2->mark == 1)
        return 1;
    return 0;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void bridgeUtil(struct Graph *graph, int u, int disc[], int low[], int parent[], int ap[])
{
    {
        static int time = 0;

        int children = 0;

        graph->visited[u] = 1;

        disc[u] = low[u] = ++time;

        for (node *i = graph->adjLists[u]; i != NULL; i = i->next)
        {
            int v = i->vertex;
            if (isMarked(graph, u, v))
            {
                continue;
            }

            if (!graph->visited[v])
            {
                children++;
                parent[v] = u;
                bridgeUtil(graph, v, disc, low, parent, ap);

                low[u] = min(low[u], low[v]);

                if (parent[u] == -1 && children > 1)
                    ap[u] = 1;

                if (parent[u] != -1 && low[v] >= disc[u])
                    ap[u] = 1;
            }

            else if (v != parent[u])
                low[u] = min(low[u], disc[v]);
        }
    }
}

int isBridge(struct Graph *graph, int u)
{
    int numV = graph->numVertices;

    int disc[numV], low[numV], parent[numV], ap[numV];

    for (int i = 0; i < numV; i++)
    {
        parent[i] = -1;
        graph->visited[i] = disc[i] = low[i] = ap[i] = 0;
    }

    for (int i = 0; i < numV; i++)
        if (graph->visited[i] == 0)
            bridgeUtil(graph, i, disc, low, parent, ap);

    if (ap[u] == 1)
    {
        return 1;
    }

    return 0;
}

void fleury(struct Graph *graph, int u)
{
    static int marked = 0;
    if (marked >= graph->edge)
    {
        return;
    }

    for (node *i = graph->adjLists[u]; i != NULL; i = i->next)
    {
        int v = i->vertex;

        if (!isMarked(graph, u, v) && (((!isBridge(graph, u) && isBridge(graph, v)) || (isBridge(graph, u) && !isBridge(graph, v))) || (!isBridge(graph, u) && (!isBridge(graph, u)))))
        {
            printf("(%d, %d) ", u, v);
            markUtil(graph, u, v);
            marked++;

            fleury(graph, v);
        }
    }
}