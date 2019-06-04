#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(void)
{
    char input[1024];
    int inpos = 0;
    int running = 1;

    printf("H2 Init Started - %d\n", time(0));
    do {
        int ch = fgetc(stdin);
        fputc(ch, stdout);
        fflush(stdout);

        if(ch != '\n')
        {
            if(inpos < sizeof(input))
                input[inpos++] = ch;
        }
        else
        {
            input[inpos] = 0;
            if(!strcmp(input, "exit"))
                running = 0;
            inpos = 0;
        }
    } while(running);
    printf("Init done\n");
    exit(0);
}
