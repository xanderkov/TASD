#ifndef _MY_STRUCT_

#define _MY_STRUCT_

typedef struct AVL AVL;
typedef struct BST BST;
typedef struct TABLE table_t;

struct TABLE
{
    int n;
    int sign;
};

struct BST
{
    BST *left, *right;
    int value;
};

struct AVL
{
    int value;
    unsigned char height;
    AVL *left, *right;
};


#endif