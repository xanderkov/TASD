#include "defines.h"

int allocate_graph(graph_t *graph)
{
    graph->matrix = (int **) calloc(graph->size, sizeof(int*));
    if (!graph->matrix)
        return ERR_MEMORY;

    for (int i = 0; i < graph->size; i++)
    {
        graph->matrix[i] = (int *) calloc(graph->size, sizeof(int));
        if (!graph->matrix[i])
            return ERR_MEMORY;
    }

    return OK;
}

void free_graph(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
        free(graph->matrix[i]);

    free(graph->matrix);
}

void pop_front(int *arr, int *n)
{
    if (*n > 0)
        *n -= 1;
}

int find(int *arr, int n, int x)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == x) 
            return i;
    return -1;
}

bool bfs(graph_t graph) 
{
    bool used[N];
    int dst[N];
    int q[N], n = 1;
    q[0] = 0;
    used[0] = true;
    for (int i = 0; i < graph.size; i++)
        dst[i] = -1;   
    dst[0] = 0; 
    int rc = OK;
           
    while (n > 0) 
    {
        int cur = q[n - 1];
        n--;

        for (int i = 0; i < graph.size; i++) 
        {
            if (!used[i] && graph.matrix[cur][i] != 0) 
            {
                q[n] = i;
                n++;
                used[i] = true;
                dst[i] = dst[cur] + 1;
            }
        }
    }
    for (int i = 0; i < graph.size; i++)
        if (dst[i] == -1)
            rc = IS_NOT;
    /*
    for(int a = 0; a< graph.size; a++)
        for(int b = 0; b < graph.size / 2; b++)
            if(graph.matrix[a][b] != graph.matrix[a][graph.size - b - 1])
                rc = IS_NOT;
                */
    return rc;
}


int graph_viz(graph_t graph)
{

    FILE *filemain;
    int min_row = bfs(graph);

    filemain = fopen("graph.dot", "w");

    fprintf(filemain, "graph {\n");
    char cityname = 'A';


    for (int i = 0; i < graph.size; i++)
    {
        for (int j = 0; j < graph.size; j++)
        {
            if (graph.matrix[i][j] != 0 && i >= j) 
                fprintf(filemain, "%c -- %c;\n", cityname + i, cityname + j);
        }
    }

    fprintf(filemain, "}\n");

    fclose(filemain);

    system("dot -Tpng graph.dot -o main_graph.png");
    
    if (!min_row)
        printf("Связанный");
    else
        printf("Не связанный");

    return OK;
}
