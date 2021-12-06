#include "defines.h"
#include "io.h"

BST *bst_add(BST *tree, int num)
{
    if (tree)
    {
        if (num > tree->value)
            tree->right = bst_add(tree->right, num);
        else if (num < tree->value)
            tree->left = bst_add(tree->left, num);
        return tree;
    }
    else
    {
        BST *newel = malloc(sizeof(BST));
        newel->value = num;
        newel->left = newel->right = NULL;
        return newel;
    }
}

void bst_free(BST *tree)
{
    if (tree)
    {
        bst_free(tree->right);
        bst_free(tree->left);
        free(tree);
    }
}

int count_peaks(BST *tree)
{
    if (tree)
    {
        int count = 1;
        if (tree->left)
            count += count_peaks(tree->left);
        if (tree->right)
            count += count_peaks(tree->right);
        return count;
    }
    return 0;
}


int input_bst(FILE *f, BST **tree)
{
    rewind(f);
    *tree = NULL;
    int num, rc = OK;
    char dummy;
    int input;
    do
    {
        input = fscanf(f, "%d%c", &num, &dummy);
        if (input == 1 || (input == 2 && is_permited(dummy)))
            *tree = bst_add(*tree, num);
    } while (input == 1 || (input == 2 && is_permited(dummy)));
    if (!feof(f))
        rc = ERR_IO;
    return rc;
}

int search_bst(BST *root, int search)
{
    int cmp = 0;
    while (root)
    {
        ++cmp;
        if (root->value == search)
            return cmp;
        else
        {
            ++cmp;
            if (search > root->value)
                root = root->right;
            else
                root = root->left;
        }
    }
    return cmp;
}



BST* delete_node(BST* node, int val)
{
    if(node == NULL)
        return node;
 
    if(val == node->value)
    {
 
        BST* tmp;
        if(node->right == NULL)
            tmp = node->left;
        else
        {
 
            BST* ptr = node->right;
            if(ptr->left == NULL)
            {
                ptr->left = node->left;
                tmp = ptr;
            } 
            else 
            {
                BST* pmin = ptr->left;
                while(pmin->left != NULL)
                {
                    ptr  = pmin;
                    pmin = ptr->left;
                }
                ptr->left   = pmin->right;
                pmin->left  = node->left;
                pmin->right = node->right;
                tmp = pmin;
            }
        }
 
        free(node);
        node = NULL;
        return tmp;
    } 
    else if(val < node->value)
        node->left  = delete_node(node->left, val);
    else
        node->right = delete_node(node->right, val);
    return node;
}