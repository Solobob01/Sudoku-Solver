//Craciun Alexandru-Andrei
//Grupa 313CD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/cJSON.c"
#include "src/cJSON.h"

#include "./src/task_123.c"
#include "./src/task_4.c"
#include "./src/task_bonus.c"

int main(int argc, char *argv[])
{
    if (strcmp(argv[2], "123") == 0)
        task123(argv[1]);
    if (strcmp(argv[2], "4") == 0)
        task4(argv[1]);
    if (strcmp(argv[2], "bonus") == 0)
        task_bonus(argv[1]);

    return 0;
}
