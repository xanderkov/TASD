#include "defines.h"
#include "io.h"

typedef struct list_stack list_stack; 

struct list_stack
{
    int data;
    list_stack *next;
};

int empty_list(list_stack *s)
{
    if (!s)
        return ERR_LENGTH;
    return OK;
}


int full_list(list_stack *s)
{
    list_stack *p = s;
    int i = 0;
    for (; p->next; p = p->next)
        i++;
    if (i == MAXSIZE - 1)
        return ERR_LENGTH;
    return OK;
}
 
list_stack *create_list(int x)
{
    list_stack *p = malloc(sizeof(list_stack));
    if (p)
    {
        p->data = x;
        p->next = NULL;
    }
    return p;   
}

list_stack *push_list(list_stack *head, list_stack *s, int *n)
{
    list_stack *p = head;
    if (!head)
        return s;
    for (; p->next; p = p->next);
    p->next = s;
    *n += 1;
    return head;
}

int top_list(list_stack *s)
{
    list_stack *p = s;
    if (!p)
        return ERR_LENGTH;
    for (; p->next; p = p->next);
    return p->data;
}

int number_list(list_stack *s)
{
    list_stack *p = s;
    int i = 0;
    if (!p)
        return ERR_LENGTH;
    for (; p->next; p = p->next)
        i++;
    return i;
}
 
int pop_list(list_stack **s, int *n)
{   
    list_stack *p = *s, *prev = *s;
    int x;
    if (*n > 1)
    {
        for (; p->next; p = p->next)
            prev = p;
        x = p->data;
        prev->next = NULL;
        free(p);
        p = NULL;
        *n -= 1;
    }
    else if (*n == 1)
    {
        *n -= 1;
        x = p->data;
        *s = NULL;
    }
    else 
        return ERR_READ;
    return x;
}


int precedence_list(char x)
{
    if(x == '(')
        return 0;
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x== '/' || x=='%')
        return 2;
    return 3;
}

void infix_to_postfix_list(char infix[], char postfix[])
{
    list_stack *s = NULL, *p;
    char x, token;
    int i, j, n = 0;
    j = 0;
    for (i = 0; infix[i] != '\0'; i++)
    {
        token = infix[i];
        if (isalnum(token))
            postfix[j++] = token;
        else
            if (token=='(')
            {
                p = create_list('(');
                s = push_list(s, p, &n);
            }
        else
            if (token == ')')
                while ((x = pop_list(&s, &n)) != '(' )
                      postfix[j++] = x;
            else
            {
                while (precedence_list(token) <= precedence_list(top_list(s)) && !empty_list(s) && n > 0)
                {
                    x = pop_list(&s, &n);
                    postfix[j++]=x;
                }
                p = create_list(token);
                s = push_list(s, p, &n);
            }
    }
 
    while (n > 0)
    {
        x = pop_list(&s, &n);
        if (x > 0)
            postfix[j++] = x;
        else
            break;
    }
    postfix[j] = '\0';
}


void create_infix_form_list(list_stack *arr, char *infix)
{
    int i = 0;
    list_stack *p = arr;
    for (; p->next; p = p->next)
        infix[i++] = p->data;
    infix[i++] = p->data;
    infix[i] = '\0';
}

void print_stack(list_stack *list)
{
    list_stack *p = list;
    for (; p->next; p = p->next)
    {
        printf("%c\n", p->data);
        printf("%p\n", (void*)p->next);
    }
    printf("%c\n", p->data);
    printf("%p\n", (void*)p->next);
}

void start_list_menu()
{
    int rc = OK, action = 0, n = 1;
    list_stack *list = NULL, *cur;
    char infix[MAXSIZE], postfix[MAXSIZE], s[MAXSIZE];
    char c;
    do
    {
        printf("1) Добавить элемент в стек\n");
        printf("2) Удалить элемент\n");
        printf("3) Перевести в постфиксное\n");
        printf("4) Вывести текущий стек, вметсе с адрессами элементов\n");
        printf("5) Выйти из подпрогаммы\n");
        if ((rc = input_key(&action)) == OK)
        {
            switch (action)
            {
            case 1:
                printf("Введите цифру или арифмитическую операцию (+-*.)\n");
                if (scanf("%s", s) == 1 && strlen(s) == 1)
                {
                    c = s[0];
                    cur = create_list(c);
                    list = push_list(list, cur, &n);
                }
                else
                    rc = ERR_READ;
                if (rc)
                    printf("В стек ничего не добавлено\n");
                if (!rc)
                    printf("Успшено добавлен элемент в стек!\n");
                break;
            case 2:
                rc = pop_list(&list, &n);
                if (rc > 0)
                    printf("Элемент успешно удален\n");
                else
                    printf("Стек пуст\n");
                break;
            case 3:
                if (n > 0)
                {
                    create_infix_form_list(list, infix);
                    infix_to_postfix_list(infix, postfix);
                    printf("%s\n", postfix);
                }
                else
                    printf("Мало элементов\n");
                break;
            case 4:
                if (n >= 1)
                {
                    print_stack(list);
                }
                else
                    printf("Стек пуст\n");
            case 5:
                printf("Выход\n");
                break;
            default :
                printf("incorrect input\n");
                break;
            }
        }
        else
        {
            printf("Неверный ввод\n");
        }   
    }while (action != 5);
    
}