#include "defines.h"
#include "struct.h"


int is_digit(char ch)
{
    return (ch >= '0' && ch <= '9');
}


int read_file(people *p)
{

    FILE *filename;
    filename = fopen("test_2.txt", "r");
    int i = 0;
    while (fscanf(filename, "%s", p[i].name) != EOF)
    {
        fscanf (filename, "%s", p[i].surname);
        fscanf (filename, "%s", p[i].adr);
        fscanf (filename, "%s", p[i].phone);
        fscanf(filename, "%d", &p[i].status);
        if (p[i].status == 1)
        {
            fscanf (filename, "%s", p[i].info.serv.post);
            fscanf (filename, "%s", p[i].info.serv.organ);
        }
        else
        {
            fscanf (filename, "%d", &p[i].info.bd.day);
            fscanf (filename, "%d", &p[i].info.bd.month);
            fscanf (filename, "%d", &p[i].info.bd.year);
        }
        i++;
    }
    fclose(filename);
    return i;
}

void print_string(people *p, int status)
{
    printf("%-15s ", p->name);
    printf("%-20s ", p->surname);
    printf("%-20s ", p->adr);
    printf("%-18s ", p->phone);
    if (status == 0)
    {
        printf("%-5d ", p->info.bd.day);
        printf("%-5d ", p->info.bd.month);
        printf("%-8d ", p->info.bd.year);
        printf("     -        ");
        printf("     -         ");
    }
    else
    {
        printf("   - ");
        printf("   - ");
        printf("   -      ");
        printf("%-15s", p->info.serv.post);
        printf("%-15s", p->info.serv.organ);
    }
    printf("|");
    printf("\n");
}


void print_table(people *p, int n)
{
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|Номер   Имя            Фамилия               Адрес                 Номер            день  месяц  год     должность         организация|\n");
    printf("|--------------------------------------------------------------------------------------------------------------------------------------|\n");

    for (int i = 0; i < n; i++)
    {
        printf("| ");
        printf("%-5d ", i + 1);
        print_string(&p[i], p[i].status);
    }
    printf("\n");
}

void menu()
{
    printf("Введите действие\n");
    printf("1 - Добавить строку в базу\n");
    printf("2 - Удалить строку из базы по имени\n");
    printf("3 - Вывести таблицу\n");
    printf("4 - Отсортировать ключи по именам и вывести их\n");
    printf("5 - Отсортировать таблицу по именам и вывести ее\n");
    printf("6 - Отсортировать ключи по именам и вывести базу \n");
    printf("7 - Сравнить сортировку по ключам и сортировку базу \n");
    printf("8 - Сравнить быструю сортировку и сортировку пузырьком\n");
    printf("9 - Вывести друзей у которых день рождения на этой недели\n");
    printf("10 - Выйти\n");
    printf("\nВведите действие: ");
}

int input_key(int *key)
{
    menu();
    if (scanf("%d", key) == 1)
    {
        if (*key > 0 && *key < 11)
            return OK;
    }
    return ERR_READ;
}

int read_line(char *str, int size)
{
    scanf("%s", str);
    if (strlen(str) > size)
        return ERR_READ;
    return strlen(str);
}

int read_int(int *a, int n)
{
    *a = -1;
    char chars[STR_LEN];
    if (chars == NULL)
        return ERR_READ;
    int num = read_line(chars, n);
    if (num < 1)
    {
        return ERR_READ;
    }
    char *ptr;
    *a = strtol(chars, &ptr, 0);
    if (*a == -1)
        return ERR_READ;
    return OK;
}

int read_keys(key *keys, people *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        keys[i].index = i + 1;
        strcpy(keys[i].name, p[i].name);
    }
    return OK;
}

void print_keys(key *keys, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\nИндекс %d\n", keys[i].index);
        printf("Имя: %s\n", keys[i].name);
    }
}


void print_table_by_keys(people *p, key *keys, int n)
{
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("|Номер   Имя     Фамилия      Адрес              Номер          день  месяц  год   должность организация|\n");
    printf("|-------------------------------------------------------------------------------------------------------|\n");
    for (int i = 0; i < n; i++)
    {
        printf("| ");
        print_string(&p[keys[i].index - 1], p[keys[i].index - 1].status);
    }
    printf("\n");
}