#include "defines.h"

void input_interval(interval *t)
{
    printf("Введите наименьшее время заявки (>= 0 ): ");
    while (scanf("%lf", &t->min) != 1 || t->min < 0)
    {
        printf("Неверный ввод");
        printf("Введите наименьшее время заявки (> 0 ): ");
    }
    printf("Введите наибольшое время заявки (> %lf ): ", t->min);
    while (scanf("%lf", &t->max) != 1 || t->max < t->min)
    {
        printf("Неверный ввод");
        printf("Введите наибольшое время заявки (> %lf ): ", t->min);
    }
}


void start_edit_menu(interval *t1, interval *t2, interval *t3, interval *t4)
{
    printf("Интервал первой очереди\n");
    input_interval(t1);
    printf("Интервал второй очереди\n");
    input_interval(t2);
    printf("Интервал аппарата для первой очереди\n");
    input_interval(t3);
    printf("Интервал аппарата для второй очереди\n");
    input_interval(t4);
}

int input_key(int *key)
{
    if (scanf("%d", key) == 1)
        return OK;
    return ERR_READ;
}