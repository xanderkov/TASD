#include "struct.h"

int read_file(people *p);
int input_key(int *key);
void print_table(people *p, int n);
int read_int(int *a, int n);
int read_line(char *str, int size);
int read_keys(key *keys, people *p, int n);
void print_keys(key *keys, int n);
void print_string(people *p, int status);
void print_table_by_keys(people *base, key *keys, int n);