#include <stdio.h>
#include "defines.h"
#include "in_out.h"
#include "long_number.h"
#include "number_division.h"

int main(void)
{
    int check = OK;
    long_float b = { 0 }, a = { 0 };
    printf("ЛР №1. Вариант 6\n");
    printf("Операция деления действительного на действительное.\n");
    printf("Формат ввода действительного числа: ±m.nЕ±K, \n суммарная длина мантиссы (m+n) < 30 цифр, \n порядок K - от 1 до 5 цифр\n");
    if (get_long_float(&a) == OK && get_long_float(&b) == OK)
    {
        check = OK;
        long_float c = { 0 };
        divide(a, b, &c);
        print_answer(c);
    }
    else
    {
        if (check == ERR_ZERO)
            printf("Zero division!\n");
        else
        {
            check = ERR_READ;
            printf("Incorrect input!\n");
        }
    }
    return check;
}