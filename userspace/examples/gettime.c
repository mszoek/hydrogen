#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    time_t now = time(0);
    printf("time is %d\n\n", now);
    return 0;
}

