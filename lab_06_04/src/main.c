#include "defines.h"
#include "io.h"
#include "time.h"
#include "bst.h"
#include "avl.h"

int main()
{
    int rc = OK;
    setbuf(stdout, NULL); 
    BST *bstroot = NULL;
    //AVL *avlroot = NULL;
    //table_t *table = NULL;
    printf("ЛР №6. Вариант номер 4\n");
    printf("Удаления из дерево и т.д. состоящего из чисел\n");
    FILE *f = NULL;
    read_file(&f);
    input_bst(f, &bstroot);
    rc = bst_export("BST", bstroot);
    
    if (!rc)
    {
        system(DOT " -Tpng " BSTFILE " -o " BSTIMGNAME);
        system("start " IMG_VIEWER " " BSTIMGNAME);
    }
    
    /*
    if (!rc)
    {
        bst_to_avl(bstroot, &avlroot);
        if (!rc)
            rc = avl_export(APPFOLDER "\\" AVLDOTNAME, "AVL", avlroot);
        if (!rc)
        {
            system(DOT " -Tpng " APPFOLDER "\\" AVLDOTNAME " -o" APPFOLDER "\\" AVLIMGNAME);
            system("start " IMG_VIEWER " " APPFOLDER "\\" AVLIMGNAME);
        }
    }
*/
    /*
    do
    {
        printf("   1) Построить всё\n   2) Удалеить введенное число\n   3) Выход\n");
        printf("Выбирете нужный вам пункт, введите соотвествующую цифру (от 1 до 3): ");
        
        
        if (!(rc = input_key(&action)))
        {
            switch (action)
            {
            case 1:
                
                break;
            case 2:

                break;
            case 3:
                printf("Выход");
                break;
            default :
                printf("Неверный ввод\n");
                break;
            }
        }
        
        else
            printf("Неверный ввод\n");
    }
    while (action != 3 && rc == OK);
    */
    return rc;
}