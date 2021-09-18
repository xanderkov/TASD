#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define N 60
#define M 5
#define N_NAT 30
#define INPUT_ERR -1
#define ERROR_NUMBERS -2
#define OK 0
#define NULL_STR -3
#define FIRST_NULL -4
#define BIG_ORDER -5


typedef struct
{
    char sign;
    int natural[N];
    int point_i;
    int meaning[N];
    int meaning_n;
    long order;
} real_number;




int check_number(char *str)
{
    int num_pointer = 0, k = 0;
    size_t i = 0;
    if ((str[0] == '-' || str[0] == '+'))
        i++;
    for (; i < strlen(str); i++)
    {
        if (isdigit(str[i]))
            k++;
        else if (num_pointer == 0 && str[i] == '.')
            num_pointer++;
        else
            return INPUT_ERR;
        if (k > N / 2)
            return INPUT_ERR;
    }
    return OK;
}


int check_order(char *str)
{
    int rc = INPUT_ERR;
    size_t i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (str[i] - '0' == 0 && strlen(str) != i + 1)
        return INPUT_ERR;
    for (; i < strlen(str); i++)
    {
        if (isdigit(str[i]))
            rc = OK;
        else
            rc = INPUT_ERR;
        if (i > M)
            return INPUT_ERR;
    }
    if (strlen(str) == 0)
        rc = NULL_STR;
    return rc;
}


void read_order(char *str, long *order)
{
    char *ptr;
    *order = strtol(str, &ptr, 0);
}

void read_mean_number(char *str, int *integer, int *fractional, int *int_n, int *frac_n, char *sign)
{
    int num_pointer = 0;
    size_t i = 0;
    if (str[i] == '-' || str[i] == '+')
        *sign = str[i++];
    for (; i < strlen(str); i++)
    {
        if (str[i] >= 48 && str[i] <= 57 && num_pointer == 0)
            integer[(*int_n)++] = str[i] - '0';
        else if (str[i] >= 48 && str[i] <= 57 && num_pointer == 1)
            fractional[(*frac_n)++] = str[i] - '0';
        else if (num_pointer == 0 && str[i] == '.')
            num_pointer++;
    }
}

int check_second(int *arr, int n)
{
    int rc = OK;
    if (n == 1 && arr[0] == 0)
        rc = INPUT_ERR;
    return rc;
}


void reverse(int *arr, int n)
{
    int arr_2[N];
    for (int i = 0; i < n; i++)
    {
        arr_2[n - i - 1] = arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = arr_2[i];
    }
}


void delete_nulls(real_number *r)
{
    reverse(r->natural, r->point_i);
    while (r->natural[r->point_i] == '0')
    {
        if (r->meaning_n == 0 && r->point_i == 1)
            break;
        r->point_i--;
    }
    reverse(r->natural, r->point_i);
    while (r->meaning[r->meaning_n] == '0')
    {
        if (r->point_i == 0 && r->meaning_n == 1)
            break;
        r->meaning_n--;
    }
}

void make_number_without_pointer(real_number *r)
{
    delete_nulls(r);
    for (int i = 0; i < r->meaning_n; i++)
    {
        r->natural[r->point_i++] = r->meaning[i];
    }
    r->meaning_n = 0;
}

bool all_null(int *arr, int n)
{
    int i = 0;
    while (i < n)
    {
        if (arr[i++] != 0)
            return false;
    }
    return true;
}


int is_first_bigger(int first[], int second[], int n, int second_n)
{
    for (int i = 0; i < second_n; i++)
    {
        if (first[n + i] > second[i])
            return true;
        if (first[n + i] < second[i])
            return false;
    }
    return true;
}

void substract(int first[], int second[], int second_n, int *diff, int null_quanity)
{
    int remain = 0;
    while (is_first_bigger(first, second, null_quanity, second_n))
    {
        for (int i = second_n - 1; i >= 0; i--)
        {
            first[null_quanity + i] = first[null_quanity + i] - second[i] + remain;
            remain = 0;
            if (first[null_quanity + i] < 0)
            {
                first[null_quanity + i] += 10;
                remain = -1;
            }
        }
        (*diff)++;
    }
}


int division(real_number r_1, real_number r_2, real_number *res)
{
    int null_quanity = 0;
    make_number_without_pointer(&r_1);
    make_number_without_pointer(&r_2);
    if (check_second(r_2.natural, r_2.point_i) != OK)
        return INPUT_ERR;
    for (int i = r_1.point_i; i <= r_2.point_i + 1; i++)
    {
        r_1.point_i++;
    }
    while (null_quanity + r_2.point_i < N && null_quanity < N_NAT - 1)
    {
        int diff = 0;
        substract(r_1.natural, r_2.natural, r_2.point_i, &diff, null_quanity);
        res->natural[res->point_i] = diff;
        if (!(is_first_bigger(r_1.natural, r_2.natural, null_quanity, r_2.point_i)))
        {
            if (null_quanity + r_2.point_i == r_1.point_i)
            {
                r_1.point_i++;
                r_1.order--;
            }
            r_1.natural[null_quanity + 1] += r_1.natural[null_quanity] * 10;
            r_1.natural[null_quanity] = 0;
        }
        null_quanity++;
        res->point_i++;
    }
    make_number_without_pointer(&r_1);
    if (r_1.sign == r_2.sign)
        res->sign = '+';
    else
        res->sign = '-';
    res->order = r_1.order - r_2.order;
    return OK;
}


void make_res_normal(real_number *res)
{
    while (res->point_i > 0)
    {
        for (int i = res->meaning_n; i > 0; i--)
            res->meaning[i] = res->meaning[i - 1];
        res->meaning[0] = res->natural[res->point_i-- - 1];
        res->meaning_n++;
        res->order++;
    }
    while (res->meaning[0] == 0)
    {
        for (int i = 0; i < res->meaning_n; i++)
            res->meaning[i] = res->meaning[i + 1];
        res->meaning_n--;
        res->order--;
    }
    while (res->meaning[res->meaning_n - 1] == 0)
    {
        res->meaning_n--;
    }
    
}


void print_results(real_number res, int rc)
{
    FILE* f;
    f = fopen("output.txt", "w");
    make_res_normal(&res);
    if (res.order > 99999 || res.order < -99999)
        rc = BIG_ORDER;
    if (rc == OK)
    {
        if (res.meaning_n > N_NAT)
        {
            if (res.meaning[N_NAT] >= 5)
            {
                if (res.meaning[N_NAT] == 9)
                {
                    int j = N_NAT;
                    while(res.meaning[j--] == 9)
                    {
                        res.meaning_n--;
                    }
                    res.meaning[res.meaning_n - 1] += 1;
                }
                else
                {
                    res.meaning[N_NAT - 1] += 1;
                    res.meaning_n = N_NAT;
                }
            }
        }
        fprintf(f, "%c%d%c", res.sign, 0, '.');
        for (int i = 0; i < res.meaning_n; i++)
            fprintf(f, "%d", res.meaning[i]);
        fprintf(f, "%s", " E ");
        if (res.order > 0)
            fprintf(f, "%s", "+");
        fprintf(f, "%ld", res.order);
    }
    else if (rc == INPUT_ERR)
        fprintf(f, "%s", "INPUT ERROR");
    else if (rc == BIG_ORDER)
        fprintf(f, "%s", "BIG_ORDER");
    fclose(f);
}

void start_operation(char *number_1, char *order_1, char *number_2, char *order_2)
{
    real_number real_1 = { '+', { 0 }, 0, { 0 }, 0, 0},
    real_2  = { '+', { 0 }, 0, { 0 }, 0, 0},
    result = { '+', { 0 }, 0, { 0 }, 0, 0};
    int rc = OK;
    if (check_number(number_1) == OK && check_number(number_2) == OK && check_order(order_2) == OK && check_order(order_2) == OK)
    {
        read_mean_number(number_1, real_1.natural, real_1.meaning, &real_1.point_i, &real_1.meaning_n, &real_1.sign);
        read_mean_number(number_2, real_2.natural, real_2.meaning, &real_2.point_i, &real_2.meaning_n, &real_2.sign);
        read_order(order_1, &real_1.order);
        read_order(order_2, &real_2.order);
    }
    else
        rc = INPUT_ERR;
    if (rc == OK)
    {
        rc = division(real_1, real_2, &result);
    }
     print_results(result, rc);
}


int main()
{
    start_operation("12", "0", "2", "0");
    return OK;
}
