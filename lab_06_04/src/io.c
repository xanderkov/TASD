#include "defines.h"


void read_file(FILE **f)
{
    char name[STR_LEN] = { 0 };
    int rc = ERR;
    while (rc)
    {
        printf("Введите название файла: ");
        if (scanf("%s", name) && (*f = fopen(name, "r")) && *f)
            rc = OK;    
    }
}

int is_permited(char sym)
{
    switch (sym)
    {
        case ' ':
            return 1;
        case '\n':
            return 1;
        case '\t':
            return 1;
        default:
            return 0;
    }
}

void bst_to_dot(FILE *fout, BST *root)
{
    if (fout && root)
    {
        if (root->left)
            fprintf(fout, "%d -> %d;\n", root->value, root->left->value);
        if (root->right)
            fprintf(fout, "%d -> %d;\n", root->value, root->right->value);
        bst_to_dot(fout, root->left);
        bst_to_dot(fout, root->right);
    }
}

int bst_export(char *tree_name, BST *tree)
{
    int rc = OK;
    char *filename = BSTFILE;
    if (filename && tree_name)
    {
        FILE *fout = fopen(filename, "w");
        if (fout)
        {
            fprintf(fout, "digraph %s {\n", tree_name);
            bst_to_dot(fout, tree);
            fprintf(fout, "}\n");
            fclose(fout);
            rc = OK;
        }
        else
            rc = ERR;
    }
    else
        rc = ERR;
    return rc;
}


void avl_to_dot(FILE *fout, AVL *root)
{
    if (fout && root)
    {
        if (root->left)
            fprintf(fout, "%d -> %d;\n", root->value, root->left->value);
        if (root->right)
            fprintf(fout, "%d -> %d;\n", root->value, root->right->value);
        avl_to_dot(fout, root->left);
        avl_to_dot(fout, root->right);
    }
}

int avl_export(char *tree_name, AVL *tree)
{
    int rc = OK;
    if (tree_name)
    {
        FILE *fout = fopen(AVLFILE, "w");
        if (fout)
        {
            fprintf(fout, "digraph %s {\n", tree_name);
            avl_to_dot(fout, tree);
            fprintf(fout, "}\n");
            fclose(fout);
        }
        else
            rc = ERR_IO;
    }
    else
        rc = ERR;
    return rc;
}

int search_file(FILE *f, int search)
{
    rewind(f);
    int cmp = 0;
    int num;
    char dummy;
    int got = 0;
    do
    {
        got = fscanf(f, "%d%c", &num, &dummy);
        cmp += 1;
        if (got && num == search)
        {
            return cmp;
        }
    } while (got > 0 && !feof(f));
    return ERR;
}


void input_del(FILE *f, int *search, int *maxcmp)
{
    rewind(f);
    int rc = ERR;
    while (rc)
    {
        printf("Введите чилсо, которое нужно удалить: ");
        scanf("%d", search);
        if (search_file(f, *search) > 0)
            rc = OK;
    }
    rc = ERR;
    while (rc)
    {
        printf("Введите максимальное количество сравнений: ");
        scanf("%d", maxcmp);
        if (*maxcmp > 0)
            rc = OK;
    }
}


