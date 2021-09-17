#ifndef _TEST_H_
#define _TEST_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int start_operation(char *number_1, char *order_1, char *number_2, char *order_2);
int check_number(char *str);
int check_order(char *str);

#ifdef  __cplusplus
}
#endif

#endif  