#ifndef _CONSTANTS_H_

#define _CONSTANTS_H_

#include "defines.h"

typedef struct
{
    int day;
    int month;
    int year;
} birthday;

typedef struct
{
    char post[STR_LEN];
    char organ[STR_LEN];
} service;

typedef struct 
{
    int index;
    char surname[STR_LEN];
    char name[STR_LEN];
    char phone[STR_LEN];
    char adr[STR_LEN];
    int status;
    union
    {
        birthday bd;
        service serv;
    } info;
     
} people;

typedef struct
{
    int index;
    char name[STR_LEN];
} key;

#endif
