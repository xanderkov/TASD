#include "defines.h"

int input_bst(FILE *f, BST **tree);
BST *bst_add(BST *tree, int num);
int count_peaks(BST *tree);
void bst_free(BST *tree);
int search_bst(BST *root, int search);
int count_peaks(BST *tree);
BST* delete_node(BST* node, int val);
