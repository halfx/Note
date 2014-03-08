//written by andersonc0d3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
        FILE *fp = fopen("/levels/level10_alt.pass", "r");
        struct {char pass[20], msg_err[20]} pwfile = {{0}};
        char ptr[0];

        if(!fp || argc != 2)
                return -1;

        fread(pwfile.pass, 1, 20, fp);
        pwfile.pass[19] = 0;
        ptr[atoi(argv[1])] = 0;
        fread(pwfile.msg_err, 1, 19, fp);
        fclose(fp);

        if(!strcmp(pwfile.pass, argv[1]))
                execl("/bin/sh", "sh", 0);
        else
                puts(pwfile.msg_err);


        return 0;
}


(gdb) disass main
Dump of assembler code for function main:
   0x080484c4 <+0>:     push   %ebp
   0x080484c5 <+1>:     mov    %esp,%ebp
   0x080484c7 <+3>:     push   %edi
   0x080484c8 <+4>:     sub    $0x74,%esp
   0x080484cb <+7>:     and    $0xfffffff0,%esp
   0x080484ce <+10>:    mov    $0x0,%eax
   0x080484d3 <+15>:    sub    %eax,%esp
   0x080484d5 <+17>:    movl   $0x80486a4,0x4(%esp)
   0x080484dd <+25>:    movl   $0x80486a6,(%esp)
   0x080484e4 <+32>:    call   0x80483c8 <fopen@plt> /* fp = fopen() */
   0x080484e9 <+37>:    mov    %eax,-0xc(%ebp)
   0x080484ec <+40>:    lea    -0x48(%ebp),%edi
   0x080484ef <+43>:    cld    
   0x080484f0 <+44>:    mov    $0x0,%edx
   0x080484f5 <+49>:    mov    $0xa,%eax
   0x080484fa <+54>:    mov    %eax,%ecx
   0x080484fc <+56>:    mov    %edx,%eax
   0x080484fe <+58>:    rep stos %eax,%es:(%edi) /* pwfile = {{0}}; 初始化结构体 */
   0x08048500 <+60>:    cmpl   $0x0,-0xc(%ebp)   /* fp == 0 则退出 */
   0x08048504 <+64>:    je     0x804850e <main+74>

   0x08048506 <+66>:    cmpl   $0x2,0x8(%ebp)    /* argc != 2 则退出 */
   0x0804850a <+70>:    jne    0x804850e <main+74>
   0x0804850c <+72>:    jmp    0x804851a <main+86>
   0x0804850e <+74>:    movl   $0xffffffff,-0x5c(%ebp)
   0x08048515 <+81>:    jmp    0x80485d3 <main+271>  /* 退出 */

   0x0804851a <+86>:    mov    -0xc(%ebp),%eax  /* 正式开始 */
   0x0804851d <+89>:    mov    %eax,0xc(%esp)
   0x08048521 <+93>:    movl   $0x14,0x8(%esp)
   0x08048529 <+101>:   movl   $0x1,0x4(%esp)
   0x08048531 <+109>:   lea    -0x48(%ebp),%eax
   0x08048534 <+112>:   mov    %eax,(%esp)
   0x08048537 <+115>:   call   0x80483f8 <fread@plt> /* fread(var_48, 1, 0x14, fp) */
   0x0804853c <+120>:   movb   $0x0,-0x35(%ebp)
   0x08048540 <+124>:   mov    0xc(%ebp),%eax
   0x08048543 <+127>:   add    $0x4,%eax
   0x08048546 <+130>:   mov    (%eax),%eax
   0x08048548 <+132>:   mov    %eax,(%esp)
   0x0804854b <+135>:   call   0x80483d8 <atoi@plt>
   0x08048550 <+140>:   movb   $0x0,-0x58(%eax,%ebp,1) /* var_(58+eax) = 0 */
   0x08048555 <+145>:   mov    -0xc(%ebp),%eax
   0x08048558 <+148>:   mov    %eax,0xc(%esp)
   0x0804855c <+152>:   movl   $0x13,0x8(%esp)
   0x08048564 <+160>:   movl   $0x1,0x4(%esp)
   0x0804856c <+168>:   lea    -0x48(%ebp),%eax
   0x0804856f <+171>:   add    $0x14,%eax
   0x08048572 <+174>:   mov    %eax,(%esp)
   0x08048575 <+177>:   call   0x80483f8 <fread@plt>
   0x0804857a <+182>:   mov    -0xc(%ebp),%eax
   0x0804857d <+185>:   mov    %eax,(%esp)
   0x08048580 <+188>:   call   0x80483b8 <fclose@plt>
   0x08048585 <+193>:   mov    0xc(%ebp),%eax
   0x08048588 <+196>:   add    $0x4,%eax
   0x0804858b <+199>:   lea    -0x48(%ebp),%edx
   0x0804858e <+202>:   mov    (%eax),%eax
   0x08048590 <+204>:   mov    %eax,0x4(%esp)
   0x08048594 <+208>:   mov    %edx,(%esp)
   0x08048597 <+211>:   call   0x8048408 <strcmp@plt>
   0x0804859c <+216>:   test   %eax,%eax
   0x0804859e <+218>:   jne    0x80485be <main+250>
   0x080485a0 <+220>:   movl   $0x0,0x8(%esp)
   0x080485a8 <+228>:   movl   $0x80486bf,0x4(%esp)
   0x080485b0 <+236>:   movl   $0x80486c2,(%esp)
   0x080485b7 <+243>:   call   0x80483a8 <execl@plt>
   0x080485bc <+248>:   jmp    0x80485cc <main+264>
   0x080485be <+250>:   lea    -0x48(%ebp),%eax
   0x080485c1 <+253>:   add    $0x14,%eax
   0x080485c4 <+256>:   mov    %eax,(%esp)
   0x080485c7 <+259>:   call   0x80483e8 <puts@plt>
   0x080485cc <+264>:   movl   $0x0,-0x5c(%ebp)
   0x080485d3 <+271>:   mov    -0x5c(%ebp),%eax
   0x080485d6 <+274>:   mov    -0x4(%ebp),%edi
   0x080485d9 <+277>:   leave  
   0x080485da <+278>:   ret    
End of assembler dump.
(gdb) 