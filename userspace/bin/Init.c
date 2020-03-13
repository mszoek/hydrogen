#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <syscall.h>

int main(void)
{
    char input[1024];
    int inpos = 0;
    int running = 1;
    char *foo;
    FILE *fp;
    int bytes;


    printf("H2 Init Started - %d\n", time(0));

    foo = malloc(64*1024); // alloc 64K
    printf("malloc'd 64K at %x\n", (unsigned long long)foo);
    fp = fopen("foo.txt", "r");
    bytes = fread(foo, 1, 64*1024, fp);
    if(bytes > 0)
    {
        foo[bytes] = 0;
        printf("%s\n",foo);
    }
    else
        perror("fread");
    fclose(fp);

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
            else
            {
                int rc = _syscall(SYSCALL_EXEC, (UInt64)input, 0, 0, 0, 0);
                if(rc < 0)
                {
                    perror("exec");
                }
            }
            
            inpos = 0;
        }
    } while(running);
    printf("Init done\n");
    exit(0);
}
