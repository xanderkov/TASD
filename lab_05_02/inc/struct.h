#ifndef _MY_STRUCT_

#define _MY_STRUCT_


typedef struct list list;

struct list
{
    list *next;
};


typedef struct
{
    double min;
    double max;
}interval;

typedef struct
{
    int entry;
    double time;
}queue;


#endif