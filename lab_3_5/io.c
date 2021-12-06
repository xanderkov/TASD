#include "defines.h"
#include "matrix_operation.h"


void print_matrix(int n, int m, int (*matrix)[M])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%5d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

void print_array(const int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%5d ", arr[i]);
    printf("\n");
}


int input_matrix_and_vector_length(int *n, int *m, int *vector_len)
{
    int rc = OK;
    printf("Введите количество строк и столбцов матрицы (до 500 элементов на строках или столбцов): \n");
    if (scanf("%d%d", n, m) != 2)
    {
        printf("Неверный ввод");
        rc = ERR_READ;
    }
    else if (*n > 0 && *m > 0 && *m < 501 && *n < 501)
    {
        printf("Введите количество элементов в векторе столбце:\n");
        if (scanf("%d", vector_len) != 1)
        {
            printf("Неверный ввод");
            rc = ERR_READ;
        }
        else if (*vector_len > 0)
        {
            if (*m != *vector_len)
            {
                printf("Размерности матрицы и вектора столбца не совпадают\n");
                rc = ERR_LENGTH;
            }
        }
        else
        {
            printf("Неверный ввод");
            rc = ERR_READ;
        }
    }
    else
    {
        printf("Неверный ввод");
        rc = ERR_READ;
    }
    return rc;
}

int input_key(int *action)
{
    if (scanf("%d", action) != 1)
    {
        printf("Неверный ввод!\n");
        return ERR_READ;
    }
    return OK;
}

int read_vector(int *vector_len, int vector[N])
{
    int rc = OK;
    int vector_index = 0, not_zero_elem = 0;
    printf("Введите кол-во ненулевых элементов вектора столбца:\n");
    if (scanf("%d", &not_zero_elem) == 1 && not_zero_elem <= *vector_len)
        for (int i = 0; i < not_zero_elem; i++)
        {
            printf("Введите индекс строки, затем ненулевое значение:\n");
            while (scanf("%d ", &vector_index) != 1 || vector_index >= *vector_len || vector_index < 0)
                printf("Ошибка ввода, попробуйте ввести еще раз\n");
            while (scanf("%d", &vector[vector_index]) != 1 || vector[vector_index] == 0)
                printf("Введите ненулевой элемент:\n");
        }
    else
    {
        printf("Ошибка ввода!");
        rc = ERR_READ;
    }
    return rc;
}

void print(int *A, int *JA, int *IA, int number_of_nonezero, int none_zero_str)
{
    printf("A is: ");
    print_array(A, number_of_nonezero);
    printf("JA is: ");
    print_array(JA, number_of_nonezero);
    printf("IA is: ");
    print_array(IA, none_zero_str + 1);
    printf("\n");
}

void print_results_of_input(int n, int m, int (*matrix)[M], int vector_len, int *vector)
{
    int number_of_nonezero = number_of_non_zeros_elements(n, m, matrix);
    int none_zero_str = number_of_non_zeros_string(n, m, matrix);
    int JA[number_of_nonezero];
    int A[number_of_nonezero];
    int IA[vector_len + 1];
    int result[N] = { 0 };
    transpoit(n, m, matrix);
    create_vector_of_matrix(A, JA, IA, n, m, matrix);
    IA[vector_len] = number_of_nonezero;
    print(A, JA, IA, number_of_nonezero, vector_len);
    multiply_matrix_and_vector(JA, IA, A, vector_len, vector, result);
    printf("result is: ");
    print_array(result, vector_len);
    number_of_nonezero = number_of_none_zeros_elements_array(vector_len, result);
    int JA1[number_of_nonezero], A1[number_of_nonezero], IA1[vector_len];
    create_vector_of_vector(A1, JA1, IA1, vector_len, result);
    int non_zeros_strings_res = 0;
    non_zeros_strings_res = none_zeros_string_of_vector(vector_len, result);
    for (int i = 0; i < vector_len; i++)
        IA1[i] = 0;
    IA1[none_zero_str] = non_zeros_strings_res;
    
    print(A1, JA1, IA1, number_of_nonezero, none_zero_str - 1);
}


int read_matrix(int *n, int *m, int (*matrix)[M], int *number_of_nonezero)
{
    int index_i, index_j = 0, non_zero = 0;
    printf("Введите количество не нулевых элементов матрицы меньше %i:\n", *n * *m);
    if (scanf("%d", number_of_nonezero) == 1 && *number_of_nonezero <= *n * *m)
    {
        for (int i = 0; i < *number_of_nonezero; i++)
        {
            printf("Введите индексы строки (меньше %i) и столбца (меньше %i) , а затем ненулевое значение\n", *n, *m);
            while (scanf("%d %d", &index_i, &index_j) != 2 || index_i < 0 || index_j < 0 || index_i >= *n || index_j >= *m)
                printf("Ошибка ввода. Введите индексры строки с столбцов еще раз\n");
            printf("Введите ненулевой элемент: \n");
            while (scanf("%d", &non_zero) != 1 || non_zero == 0)
            {
                printf("Введите ненулевой элемент!:\n");
            }
            matrix[index_i][index_j] = non_zero;
        }
    }
    return OK;
}

void zero_fill(int n, int m, int matrix[][M], int zero_number)
{
    while (zero_number > 0)
    {
        int i = rand() % n, j = rand() % m;
        if (matrix[i][j] != 0)
        {
            matrix[i][j] = 0;
            zero_number--;
        }
    }
}

void auto_input_matrix(int n, int m, int number, int matrix[][M])
{
    int zero_number = (n * m) * number / 100;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = (rand() % (2*RANDOM_NUMBER) - RANDOM_NUMBER);
    zero_fill(n, m, matrix, zero_number);
}

void zero_fill_vector(int n, int *vector, int zero_number)
{
    while (zero_number > 0)
    {
        int i = rand() % n;
        if (vector[i] != 0)
        {
            vector[i] = 0;
            zero_number--;
        }
    }
}

void auto_input_vector(int n, int number, int *vector)
{
    int zero_number = n * number / 100;
    for (int i = 0; i < n; i++)
            vector[i] = (rand() % (2*RANDOM_NUMBER) - RANDOM_NUMBER);
    zero_fill_vector(n, vector, zero_number);
}


void get_time(int n, int m, int (*matrix)[M], int vector_len, int *vector)
{
    int64_t time;
    struct timeval tv_start, tv_stop;
    int number_of_nonezero = number_of_non_zeros_elements(n, m, matrix);
    int JA[number_of_nonezero], A[number_of_nonezero];
    int IA[vector_len + 1];
    int result[N] = { 0 };
    transpoit(n, m, matrix);
    create_vector_of_matrix(A, JA, IA, n, m, matrix);
    time = 0;
    for (int i = 0; i < N_TIME; i++)
    {
        gettimeofday(&tv_start, NULL);
        multiply_matrix_and_vector(JA, IA, A, vector_len, vector, result);
        gettimeofday(&tv_stop, NULL);
        time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }
    
    printf("Время перемножения разреженных матриц = %lf mcs\n", (float)time / N_TIME);
    time = 0;
    for (int i = 0; i < N_TIME; i++)
    {
        gettimeofday(&tv_start, NULL);
        multiply_matrix(result, n, m, matrix, vector);
        gettimeofday(&tv_stop, NULL);
        time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }
    printf("Время перемножения обычных матриц = %lf mcs\n", (float)time / N_TIME);
    printf("Занимаемая память:\n");
    printf("В разреженном формате: %lu\n", sizeof(A) + sizeof(JA));
}