#include "defines.h"

#ifndef _LONG_NUMBERS_H_

#define _LONG_NUMBERS_H_

typedef struct 
{
    int is_significand_negative;
    int significand[MAX_SIGNIFICAND_LENGTH + 1];
    int significand_length;
    int dot_index;
    int base;
    int is_base_negative;
    int start_index, end_index;
} long_float;

#endif