#include "struct.h"

int bubble_keys(key *keys, int n);
int bubble_sort_table(people *p, int n);

unsigned long long tick(void);

void time_table(people *table, key *keys, int n);
void print_table_by_keys(people *base, key *keys, int n);
void time_keys(people *table, key *keys, int n);
void time_table_and_key(people *table, key *keys, int n);