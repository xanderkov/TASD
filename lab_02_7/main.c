#include "defines.h"
#include "struct.h"
#include "io.h"
#include "sort.h"
#include "line_operations.h"


int main()
{
    int rc = OK, n = 0, action = 0;
    people p[N];
    key keys[N];
    setbuf(stdout, NULL); 
    n = read_file(p);
    time_table(p, keys, n);
    printf("ЛР №2. Вариант 7\n");
    printf("Список абонентов содержащие: Фамилию, имя, телефон, адрес\n день рождения, должность, организация\n");
    printf("Выбирете нужный вам пункт, напишите соотвествующую цифру (от 1 до 9)\n");
    do
    {
        printf("\n\n-------------------------------\n");
        if ((rc = input_key(&action)) == OK)
        {
            switch (action)
            {
            case 1:
                rc = add_line(p, n);
                n++;
                break;
            case 2:
                delete_line(p, &n);
                break;
            case 3:
                print_table(p, n);
                break;
            case 4:
                read_keys(keys, p, n);
                bubble_keys(keys, n);
                print_keys(keys, n);
                break;
            case 5:
                bubble_sort_table(p, n);
                read_keys(keys, p, n);
                print_table(p, n);
                break;
            case 6:
                read_keys(keys, p, n);
                bubble_keys(keys, n);
                print_table_by_keys(p, keys, n);
                break;
            case 7:
                time_table(p, keys, n);
                break;
            case 8:
                time_table_and_key(p, keys, n);
                break;
            case 9:
                find_friends_birthday(p, n);
                break;
            case 10:
                printf("Выход");
                break;
            default :
                printf("incorrect input\n");
                break;
            }
            if (rc != OK)
            {
                printf("Your input is not right. Try again\n");
            }
        }
        else
        {
            printf("incorrect input\n");
        }
    }
    while (action != 10);
    return rc;
}