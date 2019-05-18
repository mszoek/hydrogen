#include <stdio.h>

int _start(void)
{
    return main();
}

int main(void)
{
    printf("Hello dumbass\n");
    exit(0);
}