#include "defines.h"


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

int is_permited(char sym)
{
    switch (sym)
    {
        case ' ':
            return 1;
        case '\n':
            return 1;
        case '\t':
            return 1;
        default:
            return 0;
    }
}

void menu(void)
{
    printf("\n\n                                 МЕНЮ \n\n");
    printf("1  - Заполнить данные из файла\n");
    printf("2  - Определить, является ли связным заданный граф. \n");
    printf("3  - Вывести время и объем памяти, затраченные на определение\n");
    printf("0  - Выйти\n");
    printf("\nВведите номер действия, которое ходите произвести: ");
}


int search_file(FILE *f, int search)
{
    rewind(f);
    int cmp = 0;
    int num;
    char dummy;
    int got = 0;
    do
    {
        got = fscanf(f, "%d%c", &num, &dummy);
        cmp += 1;
        if (got && num == search)
        {
            return cmp;
        }
    } while (got > 0 && !feof(f));
    return ERR;
}

int matrix_fill(graph_t *graph, FILE *file)
{        
    if (fscanf(file, "%d", &graph->size) != 1)
        return MATRIX_FILL_PARAMETR_ERROR;

    if (graph->size < 1)
        return MATRIX_FILL_PARAMETR_ERROR;

    if (allocate_graph(graph) != OK)
        return MEMORY_ALLOCATION_ERROR;

    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            if (fscanf(file, "%d", &graph->matrix[i][j]) != 1)
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

int graph_vis(graph_t graph)
{


    return OK;
}

