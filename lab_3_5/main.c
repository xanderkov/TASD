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
    printf("ЛР №3. Вариант номер 5\n");
    printf("Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:\n");
    printf("- вектор A содержит значения ненулевых элементов;\n");
    printf("- вектор JA содержит номера столбцов для элементов вектора A;\n");
    printf("- связный список IA, в элементе Nk которого находится номер компонент\n");
    printf("в A и JA, с которых начинается описание строки Nk матрицы A.\n");
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
                    auto_input_matrix(n, m, 10, matrix);
                    auto_input_vector(n, 10, vector);
                    get_time(n, m, matrix, vector_len, vector);
                    printf("Обычная: %lu\n", n * m * sizeof(int));
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