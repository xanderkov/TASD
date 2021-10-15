#include "defines.h"

void print_matrix(int n, int m, int (*matrix)[M]);
void print_array(const int *arr, int n);
int input_matrix_and_vector_length(int *n, int *m, int *vector_len);
int read_vector(int *vector_len, int vector[N]);
int read_matrix(int *n, int *m, int (*matrix)[M], int *number_of_nonezero);
int input_key(int *action);
void print_results_of_input(int n, int m, int (*matrix)[M], int vector_len, int *vector);
void auto_input_matrix(int n, int m, int number, int matrix[][M]);
void auto_input_vector(int n, int number, int *vector);
void get_time(int n, int m, int (*matrix)[M], int vector_len, int *vector);