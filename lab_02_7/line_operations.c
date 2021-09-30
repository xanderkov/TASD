#include "struct.h"
#include "io.h"
#include "defines.h"

int is_birthday(int day1, int mopunt1, int year1, int day2, int mounth2, int year2)
{
    int rc = NOT_OK;
    if (year1 == year2 && mopunt1 == mounth2 && day2 - day1 < 8)
        rc = OK;
    if (year1 == year2 && mounth2 - mopunt1 == 1 && day2 + 30 - day1 < 8)
        rc = OK;
    if (year2 - year1 == 1 && mounth2 == 12 && mopunt1 == 1 && day2 + 30 - day1 < 8)
        rc = OK;
    return rc;
}

int find_friends_birthday(people *p, int n)
{
    
    int day, month, year, rc = OK; 
    while (true)
    {
        printf("Введите сегодняшнюю дату каждое чилсо через пробел (01 01 2000)\n");
        if (scanf("%d%d%d", day, month, year) && day > 0 && day < 31 && month > 0 && month < 13 && year > 0)
            break;
        printf("ERR_INPUT");
    }
    for (int i = 0; i < n; i++)
    {
        if (p[i].status == 1)
        {
            if (!is_birthday(p[i].info.bd.day, p[i].info.bd.month, p[i].info.bd.year, day, month, year))
                print_string(&p[i], p[i].status);
        }
    }
    return OK;
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
    printf("What kind of phone number? (1) - personal, (2) - service\n Input 1 or 2: ");
    if ((rc = read_int(&kind_phone, 1)) != OK)
    {
        return ERR_READ;
    }
    if (kind_phone != 1 && kind_phone != 2)
    {
        return ERR_READ;
    }
    printf("Структура таблицы имеет следующий формат:\n");

    while (true)
    {
        printf("Введите имя пользователя (до %i символов):\n ", STR_LEN - 1);
        buff = read_line(p[n].name, STR_LEN - 1);
        if (buff > 0)
            break;
        printf("ERR_INPUT");
    }

    while (true)
    {
        printf("Введите фамилию пользователя (до %i символов):\n ", STR_LEN - 1);
        buff = read_line(p[n].surname, STR_LEN - 1);
        if (buff > 0)
            break;
        printf("ERR_INPUT");
    }
    while (true)
    {
        printf("Введите адресс проживания пользователя (до %i символов):\n ", STR_LEN - 1);
        buff = read_line(p[n].adr, STR_LEN - 1);
        if (buff > 0)
            break;
        printf("ERR_INPUT");
    }
    while (true)
    {
        printf("Введите номер пользователя (до %i символов):\n ", STR_LEN - 1);
        buff = read_line(p[n].phone, STR_LEN - 1);
        if (buff > 0)
            break;
        printf("ERR_INPUT");
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
        while (true)
        {
            printf("Введите должность (до %i символов):\n ", STR_LEN - 1);
            buff = read_line(p[n].info.serv.post, STR_LEN - 1);
            if (buff > 0)
                break;
            printf("ERR_INPUT");
        }

        while (true)
        {
            printf("Введите название организации (до %i символов):\n ", STR_LEN - 1);
            buff = read_line(p[n].info.serv.organ, STR_LEN - 1);
            if (buff > 0)
                break;
            printf("ERR_INPUT");
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
            printf("запись номер %d удалена\n", *n, i);
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