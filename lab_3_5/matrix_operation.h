#include "defines.h"

void multiply_matrix_and_vector(int *JA, int *IA, int *A, int n, int *arr, int result[]);
void multiply_matrix(int res[], int n, int m, int (*matrix1)[M], int *matrix2);
int number_of_non_zeros_elements(int n, int m, int (*matrix)[M]);
int number_of_none_zeros_elements_array(int n, int *arr);
int number_of_non_zeros_string(int n, int m, int (*matrix)[M]);
void create_vector_of_matrix(int *A, int *JA, int *IA, int n, int m, int (*matrix)[M]);
void create_vector_of_vector(int *A, int *JA, int *IA, int n, int *vector);
int none_zeros_string_of_vector(int n, int *vector);
void make_zero_matrix(int n, int m, int (*matrix)[M]);
void transpoit(int n, int m, int (*a)[M]);