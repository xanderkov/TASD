#include "defines.h"

int allocate_graph(graph_t *graph)
{
    graph->matrix = (int **) calloc(graph->size, sizeof(int*));
    if (!graph->matrix)
        return ERR_MEMORY;

    graph->paths = (int **) calloc(graph->size, sizeof(int*));
    if (!graph->paths)
        return ERR_MEMORY;

    for (int i = 0; i < graph->size; i++)
    {
        graph->matrix[i] = (int *) calloc(graph->size, sizeof(int));
        if (!graph->matrix[i])
            return ERR_MEMORY;

        graph->paths[i] = (int *) calloc(graph->size, sizeof(int));
        if (!graph->paths[i])
            return ERR_MEMORY;
    }

    return OK;
}

void free_graph(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
        free(graph->matrix[i]);

    for (int i = 0; i < graph->size; i++)
        free(graph->paths[i]);

    free(graph->matrix);
    free(graph->paths);
}


