#include "struct.h"
#include "defines.h"
#include "io.h"


void swap_struct(people *p1, people *p2)
{
    people c;
    c = *p1;
    *p1 = *p2;
    *p2 = c;
}

void swap_key_struct(key *a, key *b)
{
    key c;
    c = *a;
    *a = *b;
    *b = c;
}

int bubble_keys(key *keys, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
         for (int j = i + 1; j < n; j++)
         {
             if (strcmp(keys[i].name, keys[j].name) > 0)
             {
                 swap_key_struct(&keys[i], &keys[j]);
             }
         }
    }
    return OK;
}

int bubble_sort_table(people *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
         for (int j = i + 1; j < n; j++)
         {
             if (strcmp(p[i].name, p[j].name) > 0)
             {
                 swap_struct(&p[i], &p[j]);
             }
         }
    }
    return OK;
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

void time_table_and_key(people *table, key *keys, int n)
{
    unsigned long long tb, te, all_k = 0, all_t = 0;
    people table_test[n];
    float result;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < n; j++)
            table_test[j] = table[j];
        read_keys(keys, table, n);
        tb = tick();
        bubble_keys(keys, n);
        te = tick();
        all_k += te - tb;
        tb = tick();
        bubble_sort_table(table_test, n);
        te = tick();
        all_t += te - tb;
    }
    if (all_t >= all_k)
    {
        result = (all_t - all_k)/(float)all_t * 100;
        printf("\nСортировка по ключам быстрее сортировки таблицы на %.3f %%", result);
    }
    else if (all_t < all_k)
    {
        result = (all_k - all_t)/(float)all_k * 100;
        printf("\nСортировка таблицы быстрее сортировки по ключам на %.3f %%", result);
    }
}


int cmp_str(const void *a, const void *b)
{
    const char *li = a;
    const char *ri = b;
    return strcmp(li, ri);
}


void time_keys(people *table, key *keys, int n)
{
    float result;
    unsigned long long tb, te, all_k1 = 0, all_k2 = 0;
    for (int i = 0; i < 10; i++)
    {
        read_keys(keys, table, n);
        tb = tick();
        bubble_keys(keys, n);
        te = tick();
        all_k1 += te - tb;
        read_keys(keys, table, n);
        tb = tick();
        qsort(keys->name, n, STR_LEN - 1, cmp_str);
        te = tick();
        all_k2 += te - tb;
    }
    if (all_k1 >= all_k2)
    {
        result = (all_k1 - all_k2)/(float)all_k1 * 100;
        printf("\nБыстрая сортировка быстрее сортировки пузырьком на %.3f %%", result);
    }
    else if (all_k1 < all_k2)
    {
        result = (all_k2 - all_k1)/(float)all_k2 * 100;
        printf("\nСортировка пузырьком быстрее быстрой сортировки на %.3f %%", result);
    }
}

int cmp_struct(const void *a, const void *b)
{
    const people *li = a;
    const people *ri = b;
    return strcmp(li->name, ri->name);
}


void time_table(people *table, key *keys, int n)
{
    unsigned long long tb, te, all_k = 0, all_t = 0;
    people table_test[n];
    float result;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < n; j++)
            table_test[j] = table[j];
        read_keys(keys, table, n);
        tb = tick();
        qsort(table_test, n, sizeof(table_test[0]), cmp_struct);
        te = tick();
        for (int j = 0; j < n; j++)
            table_test[j] = table[j];
        
        all_k += te - tb;
        printf("%lld\n", all_k);
        tb = tick();
        bubble_sort_table(table_test, n);
        te = tick();
        all_t += te - tb;
    }
    if (all_t >= all_k)
    {
        result = (all_t - all_k)/(float)all_t * 100;
        printf("\nБыстрая сортировка быстрее сортировки пузырьком на %.3f %%\n", result);
    }
    else if (all_t < all_k)
    {
        result = (all_k - all_t)/(float)all_k * 100;
        printf("\nБыстрая сортировка медленнее сортировки пузырьком  на %.3f %%\n", result);
    }
}