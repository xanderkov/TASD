#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <windows.h>

#include "struct.h"

#define OK 0
#define NULL_LENGTH 1
#define ERR_LENGTH -1
#define ERR_READ -2
#define N 1000
#define N_TIME 100
#define STR_LEN 100
#define ERR_NULL -4
#define EPS 1e-5
#define ERR -1
#define ERR_IO -2
#define ERR_MEMORY -6