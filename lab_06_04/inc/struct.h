#ifndef _MY_STRUCT_

#define _MY_STRUCT_

typedef struct AVL AVL;
typedef struct BST BST;
typedef struct TABLE table_t;

struct TABLE
{
    int n; // Ключ
    int sign; // Значение
};

struct BST
{
    BST *left, *right; // Левая и правая ветвь
    int value; // Значение
};

struct AVL
{
    int value; // Значение
    unsigned char height; // Высота 
    AVL *left, *right; // Левая и правая ветвь
};


#endif