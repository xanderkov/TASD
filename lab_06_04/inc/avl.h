#include "defines.h"

void bst_to_avl(BST *tree, AVL **root);
AVL* del(AVL* p, int key);
void avl_free(AVL *root);
AVL *avl_add(AVL *root, int num);
int search_avl(AVL *root, int search);