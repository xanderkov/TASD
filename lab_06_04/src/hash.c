#include "defines.h"

int hash_func(int num, int prime)
{
    return num % prime;
}

int select_prime(int max)
{
    int prime_nums[20] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
    for (int i = 19; i >= 0; i--)
    {
        if (prime_nums[i] < max)
            return prime_nums[i];
    }
    return max - 1;
}

int create_table(FILE *f, table_t **table, int *len)
{
    *table = NULL;
    int max = 0;
    int n;
    int count_nums_in_file = 0;
    rewind(f);
    if (fscanf(f, "%d", &n) == 1)
    {
        count_nums_in_file++;
        max = n;
    }
    while (fscanf(f, "%d", &n) == 1)
    {
        if (n > max)
            max = n;
        count_nums_in_file++;
    }
    if (count_nums_in_file != 0)
    {
        rewind(f);
        int index = 0;
        int prime = select_prime(count_nums_in_file);
        table_t *tmp_table = malloc(count_nums_in_file * sizeof(table_t));
        if (tmp_table != NULL)
        {
            for (int i = 0; i < count_nums_in_file; i++)
                tmp_table[i].sign = 0;
            while (fscanf(f, "%d", &n) == 1 || !feof(f))
            {
                index = hash_func(n, prime);
                if ((tmp_table[index]).sign != 0)
                {
                    while ((tmp_table[index].sign) != 0)
                    {
                        if (index == n)
                        {
                            index = 0;
                            continue;
                        }
                        index++;
                    }
                    tmp_table[index].n = n;
                    tmp_table[index].sign = 1;
                }
                else
                {
                    tmp_table[index].n = n;
                    tmp_table[index].sign = 1;
                }
            }
            *table = tmp_table;
        }
        else
            return ERR;
    }
    *len = count_nums_in_file;
    return OK;
}


int search_table(table_t *table, int size, int search)
{
    int cmp = 1;
    int prime = select_prime(size);
    int index = hash_func(search, prime);
    if (table[index].sign != 0 && table[index].n == search)
        return cmp;
    else if (table[index].sign != 0 && table[index].n != search)
    {
        while (table[index].sign != 0 && table[index].n != search)
        {
            cmp++;
            index++;
            if (index == size)
                index = 0;
        }
    }
    return cmp;
}


void print_hash_table(table_t *table, int max)
{
    printf("Хэш таблица:\n");
    for (int i = 0; i < max; i++)
        printf("%4d ", i);
    printf("\n");
    for (int i = 0; i < max; i++)
    {
        if (table[i].sign != 0)
            printf("%4d ", (table[i]).n);
        else
            printf("     ");
    }
    printf("\n");
}

int restruct(table_t *table, int n, int search, table_t **new_table, int *new_size, int max)
{
    *new_table = NULL;
    int cmp;
    int prime;
    int index;
    *new_size = n;
    table_t *new_tmp = NULL;
    do
    {
        *new_size += SHIFT;
        new_tmp = calloc(*new_size, sizeof(table_t));
        if (new_tmp)
        {
            for (int i = 0; i < *new_size; i++)
                new_tmp[i].sign = 0;

            prime = select_prime(*new_size);
            for (int i = 0; i < n; ++i)
            {
                if (table[i].sign != 0)
                {
                    index = hash_func(table[i].n, prime);
                    if (new_tmp[index].sign != 0)
                    {
                        while ((new_tmp[index].sign) != 0)
                        {
                            if (index == *new_size)
                            {
                                index = 0;
                                continue;
                            }
                            index++;
                        }
                        new_tmp[index].n = table[i].n;
                        new_tmp[index].sign = 1;
                    }
                    else
                    {
                        new_tmp[index].n = table[i].n;
                        new_tmp[index].sign = 1;
                    }

                }

            }
            *new_table = new_tmp;
        }
        else
            return -1;
        cmp = search_table(*new_table, *new_size, search);
    } while (cmp > max);
    return cmp;
}

void delete_from_table(table_t *table, int search, int n)
{
    int prime = select_prime(n);
    int index = hash_func(search, prime);
    if (table[index].sign != 0)
    {
        if (table[index].n == search)
            table[index].sign = 0;
        else
        {
            while (table[index].n != search)
            {
                index++;
                if (index == n)
                    index = 0;
            }
            table[index].sign = 0;
        }
    }
}
