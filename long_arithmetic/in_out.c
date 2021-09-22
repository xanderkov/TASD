#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defines.h"
#include "long_number.h"


int read_line(char *str, int max_length)
{
    int check = OK;
    char ch = 0;
    int i = 0;
    scanf("%c", &ch);
    while (check == OK && ch != '\n' && ch != '\r')
        if (i < max_length - 1)
        {
            str[i++] = ch;
            scanf("%c", &ch);
        }
        else
            check = ERR_LENGTH;
    if (ch == '\r')
        scanf("%c", &ch);
    str[i] = '\0';
    if (i <= 0)
        check = ERR_LENGTH;
    return check;
}

int is_long_integer(char *str)
{
    int result = 1, i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (str[i] == '0' && str[i + 1] != '\0')
        result = 0;
    else
    {
        while (str[i] != 0 && isdigit(str[i]))
            i++;
        if (str[i] == 0 && i < 30)
            result = 1;
        else
            result = 0;
    }
    return result;
}


int how_many(char ch, char *str)
{
    int count = 0, i = 0;
    while (str[i] != 0)
    {
        if (str[i] == ch)
            count++;
        i++;
    }
    return count;
}

int is_long_float(char *str)
{
    int result = 1, i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    int dots_amount = how_many('.', str);
    int e_amount = how_many('e', str) + how_many('E', str);
    int significand_digits_amount = 0;
    int digits = 0;
    if (dots_amount > 1 || e_amount != 1)
        result = 0;
    else
    {
        if (dots_amount == 1)
        {
            if (str[i] == '0' && str[i + 1] == '0')
            {
                printf("Ведущие нули\n");
                result = 0;
            }
            while (str[i] != '.' && isdigit(str[i]))
            {
                i++;
                significand_digits_amount++;
            }
            if (str[i] != '.')
                result = 0;
            else
                i++;
        }
        if (result)
        {
            while (str[i] != 'e' && str[i] != 'E' && isdigit(str[i]))
            {
                i++;
                significand_digits_amount++;
            }
            if (str[i] != 'e' && str[i] != 'E')
                result = 0;
            else
                i++;
        }
        if (result)
        {
            if (str[i] == '+' || str[i] == '-')
                i++;
            if (str[i] == '0' && str[i + 1] == '0')
                result = 0;
            while (str[i] != 0 && isdigit(str[i]))
            {
                i++;
                digits++;
            }
            if (str[i] != 0)
                result = 0;
        }
        if (significand_digits_amount > MAX_SIGNIFICAND_LENGTH)
            result = 0;
        if (digits > MAX_DIGIT_AMOUNT || digits <= 0)
            result = 0;
    }
    return result;
}

int turn_str_to_float(char *str, long_float *number)
{
    int check = OK, i = 0;
    if (str[i] == '-')
        number->is_significand_negative = 1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    int j = 0;
    while (isdigit(str[i]))
        number->significand[j++] = str[i++] - '0';
    if (str[i] == '.')
    {
        number->dot_index = j;
        i++;
        while(isdigit(str[i]))
            number->significand[j++] = str[i++] - '0';
    }
    if (str[i] == 'e' || str[i] == 'E')
        number->significand_length = j;
    i++;
    if (str[i] == '-')
        number->is_base_negative = 1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (isdigit(str[i]))
        number->base = number->base * 10 + (str[i++] - '0');
    if (number->is_base_negative)
        number->base *= -1;
    if (str[i] != 0)
        check = ERR_READ;
    int is_zeroes = 1;
    for (i = 0; i < number->significand_length; i++)
        if (number->significand[i] != 0)
            is_zeroes = 0;
    if (is_zeroes)
        check = ERR_ZERO;
    return check;
}

int get_long_float(long_float *number)
{
    int check = OK;
    char str[MAX_FLOAT_LENGTH + 1] = { 0 };
    printf("Введите действительное число:\n");
    printf("1       10         20        30\n");
    printf("|--------|---------|---------|\n");
    check = read_line(str, MAX_FLOAT_LENGTH + 1);
    if (check == OK)
    {
        if (is_long_float(str))
            check = turn_str_to_float(str, number);
        else
            check = ERR_READ;
    }
    return check;
}

int print_long_float(long_float number)
{
    int i;
    if (number.is_significand_negative)
        printf("-");
    for (i = 0; i < number.dot_index; i++)
        printf("%d", number.significand[i]);
    if (number.dot_index != 0)
        printf(".");
    while(i < number.significand_length)
        printf("%d", number.significand[i++]);
    printf("e");
    printf("%d\n", number.base);
    return OK;
}