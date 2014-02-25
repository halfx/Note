#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int  pad = 0xbabe;
    char buf[1024];
    strncpy(buf, argv[1], sizeof(buf) - 1); 

    printf(buf);
    
    return 0;
}



(gdb) disass main
Dump of assembler code for function main:
   0x080483a4 <+0>:     push   %ebp
   0x080483a5 <+1>:     mov    %esp,%ebp
   0x080483a7 <+3>:     sub    $0x428,%esp
   0x080483ad <+9>:     and    $0xfffffff0,%esp
   0x080483b0 <+12>:    mov    $0x0,%eax
   0x080483b5 <+17>:    sub    %eax,%esp
   0x080483b7 <+19>:    movl   $0xbabe,-0xc(%ebp)
   0x080483be <+26>:    movl   $0x3ff,0x8(%esp)
   0x080483c6 <+34>:    mov    0xc(%ebp),%eax
   0x080483c9 <+37>:    add    $0x4,%eax
   0x080483cc <+40>:    mov    (%eax),%eax
   0x080483ce <+42>:    mov    %eax,0x4(%esp)
   0x080483d2 <+46>:    lea    -0x418(%ebp),%eax
   0x080483d8 <+52>:    mov    %eax,(%esp)
   0x080483db <+55>:    call   0x80482cc <strncpy@plt>
   0x080483e0 <+60>:    lea    -0x418(%ebp),%eax
   0x080483e6 <+66>:    mov    %eax,(%esp)
   0x080483e9 <+69>:    call   0x80482ec <printf@plt>
   0x080483ee <+74>:    mov    $0x0,%eax
   0x080483f3 <+79>:    leave  
   0x080483f4 <+80>:    ret    
End of assembler dump.
(gdb) 