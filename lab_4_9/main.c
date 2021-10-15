#include "defines.h"
#include "matrix_operation.h"
#include "io.h"


int main()
{
    int rc = OK, action, number;
    int n = 0, m = 0, vector_len = 0;
    int matrix[N][M] = { 0 };
    int vector[N] = { 0 };
    int number_of_nonezero;
    setbuf(stdout, NULL); 
    printf("ЛР №4. Вариант номер 9\n");
    printf("Создать программу работы со стеком, выполняющую операции добавление\n");
    printf(", удаления элементов и вывод текущего состояния стека. Реализовать стек:\n");
    printf("а) массивом; б) списком. \n");
    printf("Все стандартные операции со стеком должны быть оформлены подпрограммами.\n");
    printf("При реализации стека списком в вывод текущего \n");
    printf("состояния стека добавить просмотр адресов элементов стека и\n");
    printf("создать свой список или массив свободных областей \n");
    printf("(адресов освобождаемых элементов) с выводом его на экран.\n");
    rc = input_matrix_and_vector_length(&n, &m, &vector_len);
    make_zero_matrix(n, m, matrix);
    if (!rc)
    {
        do
        {
            printf(" 1) Заполнить матрицу вручную\n 2) Заполнить матрицу автоматически\n 3) Замерить время\n 4) Выйти \n");
            printf("Выбирете нужный вам пункт, напишите соотвествующую цифру (от 1 до 4)\n");
            printf("\n\n-------------------------------------------------------------------------------------------\n");
            if ((rc = input_key(&action)) == OK)
            {
                switch (action)
                {
                case 1:
                    
                    read_vector(&vector_len, vector);
                    read_matrix(&n, &m, matrix, &number_of_nonezero);
                    print_matrix(n, m, matrix);
                    print_array(vector, vector_len);
                    print_results_of_input(n, m, matrix, vector_len, vector);
                    break;
                case 2:
                    printf("Введите процент заполнения матрицы нулями (от 0 до 100): ");
                    if ((scanf("%d", &number)) == 1 && number > 0 && number <= 100)
                    {
                        auto_input_matrix(n, m, number, matrix);
                        auto_input_vector(n, number, vector);
                        print_matrix(n, m, matrix);
                        print_array(vector, n);
                        print_results_of_input(n, m, matrix, vector_len, vector);
                    }
                    else
                        printf("Неправильные проценты\n");
                    break;
                case 3:
                    auto_input_matrix(n, m, 60, matrix);
                    auto_input_vector(n, 60, vector);
                    get_time(n, m, matrix, vector_len, vector);
                    printf("Обычная: %llu\n", n * m * sizeof(int));
                    break;
                case 4:
                    printf("Выход");
                    break;
                default :
                    printf("incorrect input\n");
                    break;
                }
            }
            else
            {
                printf("Неверный ввод\n");
            }
        }
        while (action != 4 && rc == OK);
    }
    return rc;
}