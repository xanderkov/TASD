#include "defines.h"


void multiply_matrix_and_vector(int *JA, int *IA, int *A, int n, int *arr, int result[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = IA[i]; j < IA[i + 1]; j++)
        {
            result[i] += A[j] * arr[JA[j]];
        }
    }
}

void transpoit(int n, int m, int (*a)[M])
{
    int b[N][M];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            b[j][i] = a[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            a[i][j] = b[i][j];
}


void multiply_matrix(int res[], int n, int m, int (*matrix1)[M], int *matrix2)
{
    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < m; j++)
            res[i] += matrix1[i][j] * matrix2[j];
    }
}

int number_of_non_zeros_elements(int n, int m, int (*matrix)[M])
{
    int number = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (matrix[i][j] != 0)
                number++;
    return number;
}

int number_of_none_zeros_elements_array(int n, int *arr)
{
    int number = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] != 0)
            number++;
    return number;
}


int number_of_non_zeros_string(int n, int m, int (*matrix)[M])
{
    int number = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            if (matrix[i][j] != 0)
            {
                number++;
                break;
            }
    }
    return number;
}

void create_vector_of_matrix(int A[], int JA[], int IA[], int n, int m, int (*matrix)[M])
{
    int allocated_number = 0;
    int IA_number = 0;
    for (int i = 0; i < n; i++)
    {
        int flag_IA = 0;
        for (int j = 0; j < m; j++)
        {
            if (flag_IA == 0)
            {
                IA[IA_number++] = allocated_number;
                flag_IA = 1;
            }
            if (matrix[i][j] != 0)
            {
                A[allocated_number] = matrix[i][j];
                JA[allocated_number] = j;
                
                allocated_number++;
            }
            
        }
    }
}

void create_vector_of_vector(int *A, int *JA, int *IA, int n, int *vector)
{
    int allocated_number = 0;
    int IA_number = 0;
    for (int i = 0; i < n; i++)
    {
        int flag_IA = 0;
        if (vector[i] != 0)
        {
            A[allocated_number] = vector[i];
            JA[allocated_number] = i;
            if (flag_IA == 0)
            {
                IA[IA_number] = allocated_number;
                flag_IA = 1;
                IA_number++;
            }
            allocated_number++;
        }
    }
}

int none_zeros_string_of_vector(int n, int *vector)
{
    int number = 0;
    for (int i = 0; i < n; i++)
    {
        if (vector[i] != 0)
        {
            number++;
            break;
        }
    }
    return number;
}

void make_zero_matrix(int n, int m, int (*matrix)[M])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = 0;
}