#include "struct.h"
#include "io.h"
#include "defines.h"

int is_birthday(int day1, int month1, int day2, int month2)
{
    int rc = NOT_OK;
    if (month1 == month2 && day1 - day2 < 8 && day1 - day2 > 0)
        rc = OK;
    else if (month1 - month2 == 1 && day1 + 30 - day2 < 8 && day1 + 30 - day2 > 0)
        rc = OK;
    return rc;
}

int find_friends_birthday(people *p, int n)
{
    
    int day, month, year, rc = OK; 
    while (true)
    {
        printf("Введите сегодняшнюю дату каждое чилсо через пробел (1 1 2000)\n");
        if (scanf("%d%d%d", &day, &month, &year) && day > 0 && day < 31 && month > 0 && month < 13 && year > 0)
            break;
        printf("ERR_INPUT");
    }
    int number = 0;
    for (int i = 0; i < n; i++)
    {
        if (p[i].status == 0)
        {
            if (!is_birthday(p[i].info.bd.day, p[i].info.bd.month, day, month))
            {
                fprintf(stdout,"%s %s %s %s %d %d %d %d\n", p[i].name, p[i].surname,\
                       p[i].adr, p[i].phone, p[i].status, p[i].info.bd.day,\
                       p[i].info.bd.month, p[i].info.bd.year);
                number++;
            }
        }
    }
    if (number == 0)
        printf("Вам не кого поздравить в ближайшую неделю");
    else
        printf("Вам нужно поздрвать %i друзей", number);
    return rc;
}

int add_line(people *p, int n)
{
    FILE *f;
    f = fopen("test_2.txt", "a+");
    int rc = OK;
    int buff;
    if (f == NULL)
    {
        return ERR_READ;
    }
    int kind_phone;
    printf("Какого аббонента добавить? (1) - знакомый, (2) - коллега\n 1 or 2: ");
    rc = read_int(&kind_phone, 1);
    if (rc != OK)
    {
        return ERR_READ;
    }
    if (kind_phone != 1 && kind_phone != 2)
    {
        return ERR_READ;
    }
    printf("Структура таблицы имеет следующий формат:\n");

    printf("Введите имя аббонента (до %i символов):\n ", STR_LEN - 1);
    while (read_line(p[n].name, STR_LEN - 1) <= 0)
    {
        printf("ERR_INPUT\n");
        printf("Введите имя аббонента (до %i символов):\n ", STR_LEN - 1);
    }
    printf("Введите фамилию аббонента (до %i символов):\n ", STR_LEN - 1);
    while (read_line(p[n].surname, STR_LEN - 1) <= 0)
    {
        printf("ERR_INPUT\n");
        printf("Введите фамилию аббонента (до %i символов):\n ", STR_LEN - 1);
    }
    printf("Введите адресс аббонента (до %i символов):\n ", STR_LEN - 1);
    while (read_line(p[n].adr, STR_LEN - 1) <= 0)
    {
        printf("ERR_INPUT\n");
        printf("Введите адресс аббонента (до %i символов):\n ", STR_LEN - 1);
    }
    printf("Введите номер аббонента (до %i символов):\n ", STR_LEN - 1);
    while (read_line(p[n].phone, STR_LEN - 1) <= 0)
    {
        printf("ERR_INPUT\n");
        printf("Введите номер аббонента (до %i символов):\n ", STR_LEN - 1);
    }
    if (kind_phone == 1)
    {
        p[n].status = 0;
        while (true)
        {
            printf("Введите день рождения (до %i символов):\n ", 2);
            int rc = read_int(&buff, 2);
            if (rc == OK)
            {
                if (buff > 0)
                {
                    p[n].info.bd.day = (int)buff;
                    break;
                }

                printf("ERR_INPUT");
            }
            else
                {
                    printf("ERR_rc");
                }
        }

        while (true)
        {
            printf("Введите месяц рождения (до %i символов):\n ", 2);
            int rc = read_int(&buff, 2);
            if (rc == OK)
            {
                if (buff > 0)
                {
                    p[n].info.bd.month = (int)buff;
                    break;
                }

                printf("ERR_INPUT");
            }
            else
                {
                    printf("ERR_rc");
                }
        }

        while (true)
        {
            printf("Введите год рождения (до %i символов):\n ", 4);
            int rc = read_int(&buff, 5);
            if (rc == OK)
            {
                if (buff > 0)
                {
                    p[n].info.bd.year = (int)buff;
                    break;
                }

                printf("ERR_INPUT");
            }
            else
                {
                    printf("ERR_rc");
                }
        }
        fprintf(f,"%s %s %s %s %d %d %d %d\n", p[n].name, p[n].surname,\
               p[n].adr, p[n].phone, p[n].status, p[n].info.bd.day,\
               p[n].info.bd.month, p[n].info.bd.year);
    }
    else
    {
        p[n].status = 1;
        printf("Введите должность пользователя (до %i символов):\n ", STR_LEN - 1);
        while (read_line(p[n].info.serv.post, STR_LEN - 1) <= 0)
        {
            printf("ERR_INPUT\n");
            printf("Введите должность пользователя (до %i символов):\n ", STR_LEN - 1);
        }
        printf("Введите организацию пользователя (до %i символов):\n ", STR_LEN - 1);
        while (read_line(p[n].info.serv.organ, STR_LEN - 1) <= 0)
        {
            printf("ERR_INPUT\n");
            printf("Введите организацию пользователя (до %i символов):\n ", STR_LEN - 1);
        }

        fprintf(f, "%s %s %s %s %d %s %s\n", p[n].name, p[n].surname,\
               p[n].adr, p[n].phone, p[n].status, p[n].info.serv.post, \
               p[n].info.serv.organ);
    }
    fclose(f);
    return OK;
}

int delete_line(people *p, int *n)
{
    FILE *f;
    f = fopen("test_2.txt", "w");
    char name[STR_LEN];
    int count1 = 0;
    printf("Введите Имя пользователя, которого хотите удалить из базы:\n");
    int buf = read_line(name, STR_LEN - 1);
    if (buf < 1)
    {
        printf("ERR_INPUT");
    }
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(p[i].name, name) != 0)
        {
            if (p[i].status == 0)
            {
                fprintf(f,"%s %s %s %s %d %d %d %d\n", p[i].name, p[i].surname,\
                       p[i].adr, p[i].phone, p[i].status, p[i].info.bd.day,\
                       p[i].info.bd.month, p[i].info.bd.year);
            }
            else
            {
                fprintf(f, "%s %s %s %s %d %s %s\n", p[i].name, p[i].surname,\
                       p[i].adr, p[i].phone, p[i].status, p[i].info.serv.post, \
                       p[i].info.serv.organ);
            }
        }
        else
        {
            printf("запись номер %d удалена\n", *n);
            for (int j = i; j < *n - 1; j++)
            {
                p[j] = p[j + 1];
            }
            count1 += 1;
        }
    }
    *n -= count1;
    printf("количество записей %d\n", *n);
    fclose(f);
    return OK;
}