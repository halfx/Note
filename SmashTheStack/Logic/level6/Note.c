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
   (gdb) 
*/

   