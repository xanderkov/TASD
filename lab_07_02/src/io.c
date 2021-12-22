#include "defines.h"
#include "graph_oper.h"

void read_file(FILE **f)
{
    char name[STR_LEN] = { 0 };
    int rc = ERR;
    while (rc)
    {
        printf("Введите название файла: ");
        if (scanf("%s", name) && (*f = fopen(name, "r")) && *f)
            rc = OK;    
    }
}

void menu(void)
{
    printf("\n\n                                 МЕНЮ \n\n");
    printf("1  - Заполнить данные из файла\n");
    printf("2  - Определить, является ли связным заданный граф. \n");
    printf("3  - Вывести время и объем памяти, затраченные на определение\n");
    printf("4  - Выйти\n");
    printf("\nВведите номер действия, которое ходите произвести: ");
}

int matrix_fill(graph_t *graph, FILE *f)
{    
    if (!f)
        return -1;
    if (fscanf(f, "%d", &graph->size) != 1)
        return MATRIX_FILL_PARAMETR_ERROR;

    if (graph->size < 1)
        return MATRIX_FILL_PARAMETR_ERROR;

    if (allocate_graph(graph) != OK)
        return MEMORY_ALLOCATION_ERROR;

    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            if (fscanf(f, "%d", &graph->matrix[i][j]) != 1)
                return MATRIX_FILL_ELEMENT_ERROR;

            if (graph->matrix[i][j] < 0)
                return MATRIX_FILL_ELEMENT_ERROR;
        }
    }

    return OK;
}

void matrix_print(graph_t graph)
{
    for (int i = 0; i < graph.size; i++)
    {
        for (int j = 0; j < graph.size; j++)
            printf("%10d ", graph.matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}


