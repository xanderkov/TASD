#include <stdio.h>
#include "long_number.h"
#include "defines.h"

void shift(long_float *number)
{
    for (int i = 0; i < number->significand_length - 1; i++)
        number->significand[i] = number->significand[i + 1];
    number->significand[number->significand_length - 1] = 0;
}

void make_number_without_dot(long_float *number)
{
    number->base -= (number->significand_length - number->dot_index);
    int i = 0;
    while (number->significand[i] == 0)
    {
        shift(number);
        number->significand_length -= 1;
    }
    number->dot_index = 0;
}

int compare_long(long_float *dividend, long_float *divider)
{
    int check = 0;
    if ((dividend->end_index - dividend->start_index) == (divider->end_index - divider->start_index))
    {
        int i = dividend->start_index, j = divider->start_index;
        while (i < dividend->end_index - 1 && j < divider->end_index - 1 && dividend->significand[i] == divider->significand[j])
        {
            i++;
            j++;
        }
        if (dividend->significand[i] > divider->significand[j])
            check = 1;
        else if (dividend->significand[i] < divider->significand[j])
            check = -1;
    }
    else if ((dividend->end_index - dividend->start_index) > (divider->end_index - divider->start_index))
        check = 1;
    else if ((dividend->end_index - dividend->start_index) < (divider->end_index - divider->start_index))
        check = -1;
    return check;
}

void subract(long_float *dividend, long_float *divider)
{
    if ((dividend->end_index - dividend->start_index) >= (divider->end_index - divider->end_index))
    {
        int i = dividend->end_index - 1, j = divider->end_index - 1;
        int debt = 0, current_digit = divider->significand[j];
        while (i >= 0 && j >= 0 && i >= dividend->start_index && j >= divider->start_index)
        {
            if (debt < 0)
            {
                if (dividend->significand[i] > 0)
                {
                    dividend->significand[i]--;
                    debt++;
                }
                else
                    dividend->significand[i] = 9;
            }
            if (dividend->significand[i] >= current_digit)
                dividend->significand[i] -= current_digit;
            else 
            {
                dividend->significand[i] = 10 + dividend->significand[i] - current_digit;
                debt -= 1;
            }
            i -= 1;
            if ((j - 1) < divider->start_index)
                current_digit = 0;
            else
            {
                j -= 1;
                current_digit =divider->significand[j];
            }
        }
    }
    while(dividend->significand[dividend->start_index] == 0 && dividend->start_index <= MAX_INT_LENGTH)
        dividend->start_index++;
}

void prepare_for_division(long_float *a, long_float *b, int *final_base)
{
    if (b->dot_index != -1)
        make_number_without_dot(b);
    if (a->dot_index != -1)
        make_number_without_dot(a);
    a->start_index = 0;
    a->end_index = a->significand_length;
    b->start_index = 0;
    b->end_index = b->significand_length;
    while(a->significand[a->significand_length - 1] == 0)
    {
        a->significand_length--;
        a->end_index--;
        (*final_base) += 1;
    }
    while (compare_long(a, b) < 0)
    {
        (*final_base) -= 1;
        a->end_index += 1;
        a->significand_length++;
    }
    while (compare_long(a, b) >= 0)
        a->end_index -= 1;
    a->end_index += 1;
}

int is_zero(long_float *dividend)
{
    int check = 1;
    for (int i = 0; i < dividend->significand_length; i++)
        if (dividend->significand[i] != 0)
            check = 0;
    return check;
}


int round_long_float(long_float *c, int final_base)
{
    int i = MAX_SIGNIFICAND_LENGTH - 1;
    if (c->significand[i] >= 5)
    {
        i--;
        c->significand[i]++;
        while (c->significand[i] == 10 && i > 0)
        {
            c->significand[i] = 0;
            i--;
            c->significand[i]++;
        }
        if (i == 0 && c->significand[i] == 10)
        {
            c->significand[i] = 1;
            final_base++;
        }
    }
    return i;
}


void make_float_normal(long_float a, long_float b, long_float *c, int final_base, int i)
{
    c->significand_length--;
    c->is_significand_negative = (a.is_significand_negative + b.is_significand_negative) % 2;
    c->base = final_base - (b.base) + a.base;
    if (c->base < 0)
        c->is_base_negative = 1;
    else
        c->is_base_negative = 0;
    c->end_index = c->significand_length;
    i = c->end_index - 1;
    while(c->significand[i--] == 0)
    {
        c->end_index--;
        c->base++;
    }
}

int divide(long_float a, long_float b, long_float *c)
{
    if (is_zero(&a))
    {
        c->significand_length = 1;
        c->end_index = 1;
        c->base = 0;
    } 
    else
    {
        int final_base = 0;
        prepare_for_division(&a, &b, &final_base);
        int i = 0, current_digit = 0;
        c->significand_length = 0;
        while(c->significand_length != MAX_SIGNIFICAND_LENGTH)
        {
            while (compare_long(&a, &b) >= 0)   
            {
                subract(&a, &b);
                current_digit++;
            }
            while(a.significand[a.start_index] == 0 && a.start_index <= MAX_INT_LENGTH)
                a.start_index++;
            if (i < MAX_SIGNIFICAND_LENGTH - 2 && a.end_index >= a.significand_length)
                final_base--;
            if (a.end_index != MAX_INT_LENGTH)
                a.end_index++;
            else
            {
                shift(&a);
                a.start_index--;
            }
            if (current_digit > 10)
                current_digit /= 10;
            c->significand[i] = current_digit;
            c->significand_length++;
            current_digit = 0;
            i++;
        }
        i = round_long_float(c, final_base);
        make_float_normal(a, b, c, final_base, i);
    }
    return OK;
}

int print_answer(long_float c)
{
    printf("Результат:\n");
    printf("  1       10         20        30\n");
    printf("  |--------|---------|---------|\n");
    c.base += c.end_index;
    if (c.base < -99999)
        printf("Very small number\n");
    else if (c.base > 99999)
        printf("Very big number\n");
    else
    {
        if (c.is_significand_negative)
            printf("-");
        printf("0.");
        for (int i = 0; i < c.end_index && i < MAX_INT_LENGTH - 1; i++)
            printf("%d", c.significand[i]);
        printf("E");
        printf("%d\n", c.base);
    }
    return OK;
}