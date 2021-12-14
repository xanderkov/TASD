#include "defines.h"
#ifndef _IO_H_
#define _IO_H_
int is_permited(char sym);
void read_file(FILE **f);
int bst_export(char *tree_name, BST *tree);
int avl_export(char *tree_name, AVL *tree);
int fwrite_array(char *filename, int n, int *arr);
void input_del(FILE *f, int *search, int *maxcmp);
int search_file(FILE *fsearch, int search);
#endif