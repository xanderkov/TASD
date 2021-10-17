// Operator supported: +,-,*,/,%,^,(,)
// Operands supported: all single character operands
 
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
 
#define MAX 50
 
typedef struct list_stack
{
    int data[MAX];
    int top;
}list_stack;
 
int precedence_list(char);
void init(list_stack *);
int empty_list(list_stack *);
int full_list(list_stack *);
int pop_list(list_stack *);
void push(list_stack *,int);
int top_list(list_stack *);   //value of the top element
void infix_to_postfix_list(char infix[],char postfix[]);
 
void main()
{
    char infix[30],postfix[30];
    printf("Enter an infix expression(eg: 5+2*4): ");
    gets(infix);
    infix_to_postfix_list(infix,postfix);
    printf("\nPostfix expression: %s",postfix);
}
 
void infix_to_postfix_list(char infix[], char postfix[])
{
    list_stack s;
    char x,token;
    int i,j;    //i-index of infix,j-index of postfix
    init(&s);
    j=0;
 
    for(i=0;infix[i]!='\0';i++)
    {
        token=infix[i];
        if(isalnum(token))
            postfix[j++]=token;
        else
            if(token=='(')
               push(&s,'(');
        else
            if(token==')')
                while((x=pop_list(&s))!='(')
                      postfix[j++]=x;
                else
                {
                    while(precedence_list(token)<=precedence_list(top_list(&s))&&!empty_list(&s))
                    {
                        x=pop_list(&s);
                        postfix[j++]=x;
                    }
                    push(&s,token);
                }
    }
 
    while(!empty_list(&s))
    {
        x=pop_list(&s);
        postfix[j++]=x;
    }
 
    postfix[j]='\0';
}
 
int precedence_list(char x)
{
    if(x=='(')
        return(0);
    if(x=='+'||x=='-')
        return(1);
    if(x=='*'||x=='/'||x=='%')
        return(2);
 
    return(3);
}
 
void init(list_stack *s)
{
    s->top=-1;
}
 
int empty_list(list_stack *s)
{
    if(s->top==-1)
        return(1);
 
    return(0);
}
 
int full_list(list_stack *s)
{
    if(s->top==MAX-1)
        return(1);
 
    return(0);
}
 
void push(list_stack *s,int x)
{
    s->top=s->top+1;
    s->data[s->top]=x;
}
 
int pop_list(list_stack *s)
{
    int x;
    x=s->data[s->top];
    s->top=s->top-1;
    return(x);
}
 
int top_list(list_stack *p)
{
    return (p->data[p->top]);
}