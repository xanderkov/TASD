#include "defines.h"
#include "io.h"
#include "time.h"
#include "bst.h"
#include "avl.h"
#include "hash.h"

int main()
{
    int rc = OK, table_size = 0;
    setbuf(stdout, NULL); 
    BST *bstroot = NULL;
    AVL *avlroot = NULL;
    table_t *table = NULL;
    BST *bst = NULL;
    AVL *avl = NULL;
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
    if (!rc)
    {
        bst_to_avl(bstroot, &avlroot);
        if (!rc)
            rc = avl_export("AVL", avlroot);
        if (!rc)
        {
            system(DOT " -Tpng " AVLFILE " -o " AVLIMGNAME);
            system("start " IMG_VIEWER " " AVLIMGNAME);
        }
    }
    if (!rc)
    {
        rc = create_table(f, &table, &table_size);
        print_hash_table(table, table_size);
    }
    if (!rc)
    {
        int search = 0, maxcmp = 0;
        input_del(f, &search, &maxcmp);
        int64_t time_bst = 0, time_avl = 0, time_table = 0, time_file = 0;
        int cmp_bst = 0, cmp_avl = 0, cmp_table = 0, cmp_file = 0;
        
        
        //table_t *t = NULL;
        struct timeval tv_start, tv_stop;
        input_bst(f, &bst);
        bst = delete_node(bst, search);
        rc = bst_export("BST", bst);
        if (!rc)
        {
            system(DOT " -Tpng " BSTFILE " -o " BSTIMGNAME);
            system("start " IMG_VIEWER " " BSTIMGNAME);
        }
        if (!rc)
        {
            bst_to_avl(bstroot, &avl);
            avl = del(avl, search);
            if (!rc)
                rc = avl_export("AVL", avl);
            if (!rc)
            {
                system(DOT " -Tpng " AVLFILE " -o " AVLIMGNAME);
                system("start " IMG_VIEWER " " AVLIMGNAME);
            }
        }
        for (int i = 0; i < N; i++)
        {
            cmp_bst = search_bst(bstroot, search);
            input_bst(f, &bst);
            gettimeofday(&tv_start, NULL);
            delete_node(bst, search);
            gettimeofday(&tv_stop, NULL);
            time_bst += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }

        for (int i = 0; i < N; i++)
        {
            
            cmp_avl = search_avl(avlroot, search);
            input_bst(f, &bst);
            bst_to_avl(bstroot, &avl);
            gettimeofday(&tv_start, NULL);
            del(avl, search);
            gettimeofday(&tv_stop, NULL);
            time_avl += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
            
        } 
        
        gettimeofday(&tv_start, NULL);
        for (int i = 0; i < N; i++)
            cmp_table = search_table(table, table_size, search);
        gettimeofday(&tv_stop, NULL);
        time_table = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        rewind(f);
        
        for (int i = 0; i < N; i++)
        {
            rewind(f);
            gettimeofday(&tv_start, NULL);
            cmp_file = search_file(f, search);
            gettimeofday(&tv_stop, NULL);
            time_file += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }
        
        

        int elements_count = count_peaks(bstroot);
        printf("Сруктуры\tПамять (байты)\tнс\tСравнения\n");
        printf("ДДП:% 17d% 14d% 10d\n", elements_count * (int)(sizeof(BST)),(int)(time_bst), cmp_bst);
        printf("АВЛ:% 17d% 14d% 10d\n", elements_count * (int)(sizeof(AVL)), (int)(time_avl), cmp_avl);
        printf("Хеш-Таблица:% 9d% 14d% 10d\n", table_size * (int)(sizeof(table_t)) + elements_count * (int)(sizeof(table)), (int)(time_table), cmp_table);
        printf("ФАЙЛ:% 16d% 14d% 10d\n", (int)(table_size * 4), (int)(time_file), cmp_file);

        if (cmp_table > maxcmp)
        {
            printf("\nРеструктиризируем:\n");
            table_t *res = NULL;
            int new_size = 0;
            cmp_table = restruct(table, table_size, search, &res, &new_size, maxcmp);
            if (res)
            {
                free(table);
                table = res;
                table_size = new_size;
                gettimeofday(&tv_start, NULL);
                for (int i = 0; i < N; i++)
                {
                delete_from_table(table, search, table_size);
                }
                gettimeofday(&tv_stop, NULL);
                time_table = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
                print_hash_table(table, table_size);
                printf("Размер ХЭШ-Таблицы:% 15d\n", table_size *(int)(sizeof(table_t)) + elements_count * (int)(sizeof(table)));
                printf("Количество сравнений: %d\n", cmp_table);
                printf("Время выполнения: %lld\n", time_table);
            }
            else
                rc = ERR;
        }
    }
    /*
    if (bstroot)
        bst_free(bstroot);
    if (avlroot)
        avl_free(avlroot);
    if (table)
        free(avl);
    if (table)
        free(bst);
    if (table)
        free(table);
    */
    return rc;
}