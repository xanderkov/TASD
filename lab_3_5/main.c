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
    printf("ЛР №3. Вариант номер 5\n");
    printf("Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:\n");
    printf("- вектор A содержит значения ненулевых элементов;\n");
    printf("- вектор JA содержит номера столбцов для элементов вектора A;\n");
    printf("- связный список IA, в элементе Nk которого находится номер компонент\n");
    printf("в A и JA, с которых начинается описание строки Nk матрицы A.\n");
    printf("Выбирете нужный вам пункт, напишите соотвествующую цифру (от 1 до 5)\n");
    do
    {
        printf("\n\n-----------------------------------------\n");
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