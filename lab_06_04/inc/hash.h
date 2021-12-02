#include "defines.h"

void delete_from_table(table_t *table, int search, int n);
int create_table(FILE *f, table_t **table, int *len);
void print_hash_table(table_t *table, int max);
int search_table(table_t *table, int size, int search);
int restruct(table_t *table, int n, int search, table_t **new_table, int *new_size, int max);