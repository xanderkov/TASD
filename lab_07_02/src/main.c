#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>

 
int main() 
{
 
 
    int n, m, x, y, a[80][80];
    printf("Введите количество вершин: ");
    scanf("%i", &n);
    printf("Введите количество рёбер: ");
    scanf("%i", &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            a[i][j] = 0;
        }
    printf("\n");
    printf("Введите рёбра: ");
    printf("\n");
    for (int i = 1; i <= m; i++)
    {
        scanf("%i", &x);
        scanf("%i", &y);
        a[x][y] = 1;
        a[y][x] = 1;
    }
    printf("\n");
    printf("Матрица смежности: ");
    printf("\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}