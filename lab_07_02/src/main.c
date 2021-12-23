#include "io.h"
#include "defines.h"
#include "graph_oper.h"
 
int main()
{
    int rc = OK, action;
    graph_t graph;
    FILE *f = NULL;
    char str[STR_LEN];
    int name = -1;
    int64_t time_table = 0;
    struct timeval tv_start, tv_stop;
    setbuf(stdout, NULL);
    do
    {
        menu();
        printf("\n\n----------------------------------------------------------------\n");
        if (scanf("%d", &action) == 1)
        {
            switch (action)
            {
            case 1:
                do
                {
                    printf("Введите название файла: ");
                    if (scanf("%s", str) == 1 && (f = fopen(str, "r")) && f)
                        name = OK;
                }
                while (name != OK);
                rc = matrix_fill(&graph, f);
                break;
            case 2:
                rc = graph_viz(graph);
                break;
            case 3:
                gettimeofday(&tv_start, NULL);
                for (int i = 0; i < N; i++)
                    rc = bfs(graph);
                gettimeofday(&tv_stop, NULL);
                time_table = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
                printf("Время выполнения: %lld нс\n", time_table);
                printf("Память: %d байты\n", graph.size * graph.size * 4);
                break;
            case 4:
                printf("Выход");
                break;
            default :
                printf("Неверный ввод\n");
                break;
            }
        }
    }
    while (action != 4);
    return rc;
}