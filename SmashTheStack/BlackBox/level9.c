080484b4 <main>:
 80484b4:       8d 4c 24 04             lea    0x4(%esp),%ecx    /* ecx = argc 地址 */
 80484b8:       83 e4 f0                and    $0xfffffff0,%esp  /* */
 80484bb:       ff 71 fc                pushl  0xfffffffc(%ecx)  /* */
 80484be:       55                      push   %ebp
 80484bf:       89 e5                   mov    %esp,%ebp
 80484c1:       57                      push   %edi
 80484c2:       51                      push   %ecx              /* ecx = &argc */
 80484c3:       81 ec 90 02 00 00       sub    $0x290,%esp
 80484c9:       89 8d 84 fd ff ff       mov    %ecx,0xfffffd84(%ebp) /* */
 80484cf:       c7 45 f4 00 00 00 00    movl   $0x0,0xfffffff4(%ebp)
 80484d6:       8b 85 84 fd ff ff       mov    0xfffffd84(%ebp),%eax
 80484dc:       83 38 02                cmpl   $0x2,(%eax)
 80484df:       74 27                   je     8048508 <main+0x54> /* if argc == 2 goto 8048508 */
 80484e1:       8b 95 84 fd ff ff       mov    0xfffffd84(%ebp),%edx /* 输出usage并退出 */
 80484e7:       8b 42 04                mov    0x4(%edx),%eax
 80484ea:       8b 00                   mov    (%eax),%eax
 80484ec:       89 44 24 04             mov    %eax,0x4(%esp)
 80484f0:       c7 04 24 c8 87 04 08    movl   $0x80487c8,(%esp)
 80484f7:       e8 c0 fe ff ff          call   80483bc <printf@plt>
 80484fc:       c7 04 24 ff ff ff ff    movl   $0xffffffff,(%esp)
 8048503:       e8 c4 fe ff ff          call   80483cc <exit@plt>


 8048508:       e8 7f fe ff ff          call   804838c <getppid@plt>
 804850d:       c7 44 24 0c 00 00 00    movl   $0x0,0xc(%esp) 
 8048514:       00
 8048515:       c7 44 24 08 00 00 00    movl   $0x0,0x8(%esp)
 804851c:       00
 804851d:       89 44 24 04             mov    %eax,0x4(%esp)
 8048521:       c7 04 24 10 00 00 00    movl   $0x10,(%esp)
 8048528:       e8 6f fe ff ff          call   804839c <ptrace@plt>  /* ptrace(PTRACE_ATTACH, getppid(), 0, 0); 调试绕过这里，只用将PTRACE_ATTACH修改为PTRACE_DETACH，则ptrace会失败返回 set *((int *)$esp) = 0x11 */
 804852d:       e8 5a fe ff ff          call   804838c <getppid@plt>
 8048532:       c7 44 24 0c 00 00 00    movl   $0x0,0xc(%esp)
 8048539:       00
 804853a:       c7 44 24 08 00 00 00    movl   $0x0,0x8(%esp)
 8048541:       00
 8048542:       89 44 24 04             mov    %eax,0x4(%esp)
 8048546:       c7 04 24 11 00 00 00    movl   $0x11,(%esp)
 804854d:       e8 4a fe ff ff          call   804839c <ptrace@plt>  /* ptrace(PTRACE_DETACH, getppid(), 0, 0);*/
 8048552:       8b 8d 84 fd ff ff       mov    0xfffffd84(%ebp),%ecx /* ecx = &argc */
 8048558:       8b 41 04                mov    0x4(%ecx),%eax        /* eax = &argv[] */
 804855b:       83 c0 04                add    $0x4,%eax
 804855e:       8b 00                   mov    (%eax),%eax           /* eax = &argv[1] */
 8048560:       b9 ff ff ff ff          mov    $0xffffffff,%ecx
 8048565:       89 85 80 fd ff ff       mov    %eax,0xfffffd80(%ebp)
 804856b:       b0 00                   mov    $0x0,%al
 804856d:       fc                      cld
 804856e:       8b bd 80 fd ff ff       mov    0xfffffd80(%ebp),%edi
 8048574:       f2 ae                   repnz scas %es:(%edi),%al
 8048576:       89 c8                   mov    %ecx,%eax
 8048578:       f7 d0                   not    %eax
 804857a:       48                      dec    %eax                  /* 经典的求字符串长度代码, 求出argv[1]的长度 */
 804857b:       3d 20 03 00 00          cmp    $0x320,%eax           /* if ( 0x320 <= strlen(argv[1])) goto 804859a  else exit*/
 8048580:       76 18                   jbe    804859a <main+0xe6>   /* */
 8048582:       c7 04 24 d8 87 04 08    movl   $0x80487d8,(%esp)     /* exit()*/
 8048589:       e8 2e fe ff ff          call   80483bc <printf@plt>
 804858e:       c7 04 24 ff ff ff ff    movl   $0xffffffff,(%esp)
 8048595:       e8 32 fe ff ff          call   80483cc <exit@plt>

 804859a:       8b 95 84 fd ff ff       mov    0xfffffd84(%ebp),%edx
 80485a0:       8b 42 04                mov    0x4(%edx),%eax
 80485a3:       83 c0 04                add    $0x4,%eax
 80485a6:       8b 00                   mov    (%eax),%eax
 80485a8:       b9 ff ff ff ff          mov    $0xffffffff,%ecx
 80485ad:       89 85 7c fd ff ff       mov    %eax,0xfffffd7c(%ebp)
 80485b3:       b0 00                   mov    $0x0,%al
 80485b5:       fc                      cld
 80485b6:       8b bd 7c fd ff ff       mov    0xfffffd7c(%ebp),%edi
 80485bc:       f2 ae                   repnz scas %es:(%edi),%al
 80485be:       89 c8                   mov    %ecx,%eax
 80485c0:       f7 d0                   not    %eax
 80485c2:       48                      dec    %eax                  /* 这里再次求strlen(argv[1]) */
 80485c3:       89 c2                   mov    %eax,%edx
 80485c5:       8b 8d 84 fd ff ff       mov    0xfffffd84(%ebp),%ecx
 80485cb:       8b 41 04                mov    0x4(%ecx),%eax
 80485ce:       83 c0 04                add    $0x4,%eax
 80485d1:       8b 00                   mov    (%eax),%eax
 80485d3:       89 54 24 04             mov    %edx,0x4(%esp)
 80485d7:       89 04 24                mov    %eax,(%esp)
 80485da:       e8 2a 00 00 00          call   8048609 <filterchars> /* filter(argv[1], strlen(argv[1])) */
 80485df:       89 45 f4                mov    %eax,0xfffffff4(%ebp)
 80485e2:       8b 45 f4                mov    0xfffffff4(%ebp),%eax
 80485e5:       89 44 24 04             mov    %eax,0x4(%esp)
 80485e9:       8d 85 90 fd ff ff       lea    0xfffffd90(%ebp),%eax
 80485ef:       89 04 24                mov    %eax,(%esp)
 80485f2:       e8 05 fe ff ff          call   80483fc <strcpy@plt>
 80485f7:       b8 00 00 00 00          mov    $0x0,%eax
 80485fc:       81 c4 90 02 00 00       add    $0x290,%esp
 8048602:       59                      pop    %ecx
 8048603:       5f                      pop    %edi
 8048604:       5d                      pop    %ebp
 8048605:       8d 61 fc                lea    0xfffffffc(%ecx),%esp
 8048608:       c3                      ret

08048609 <filterchars>:
 8048609:       55                      push   %ebp
 804860a:       89 e5                   mov    %esp,%ebp
 804860c:       83 ec 18                sub    $0x18,%esp
 804860f:       c7 45 ec 00 00 00 00    movl   $0x0,0xffffffec(%ebp)
 8048616:       8b 45 0c                mov    0xc(%ebp),%eax  /* strlen(argv[1]) */
 8048619:       40                      inc    %eax
 804861a:       89 04 24                mov    %eax,(%esp)
 804861d:       e8 5a fd ff ff          call   804837c <malloc@plt> /* malloc(strlen(argv[1]) + 1) */
 8048622:       89 45 f8                mov    %eax,0xfffffff8(%ebp)
 8048625:       83 7d f8 00             cmpl   $0x0,0xfffffff8(%ebp) /*若malloc不成功，则退出 */
 8048629:       75 18                   jne    8048643 <filterchars+0x3a> /* if(malloc(strlen(argv[1]) + 1) == 0) exit else goto 8048643 */
 804862b:       c7 04 24 e8 87 04 08    movl   $0x80487e8,(%esp)
 8048632:       e8 85 fd ff ff          call   80483bc <printf@plt>
 8048637:       c7 04 24 ff ff ff ff    movl   $0xffffffff,(%esp)
 804863e:       e8 89 fd ff ff          call   80483cc <exit@plt>


 8048643:       8b 45 f8                mov    0xfffffff8(%ebp),%eax /* malloc分配的空间*/
 8048646:       89 45 fc                mov    %eax,0xfffffffc(%ebp)
 8048649:       eb 5a                   jmp    80486a5 <filterchars+0x9c>

 804864b:       e8 8c fd ff ff          call   80483dc <__ctype_b_loc@plt>
 8048650:       8b 10                   mov    (%eax),%edx  /* $edx = 0x3ed720 */
 8048652:       8b 45 ec                mov    0xffffffec(%ebp),%eax /* var_ec */
 8048655:       03 45 08                add    0x8(%ebp),%eax        /* $eax = &argv[1][var_ec] */
 8048658:       0f b6 00                movzbl (%eax),%eax           /* movzbl: 拷贝一个字节,用0填充其他的，$eax = argv[1][0]  */
 804865b:       0f be c0                movsbl %al,%eax              /* movsbl: 拷贝一个字节,用1填充高位 */
 804865e:       01 c0                   add    %eax,%eax             /* eax = eax * 2 */
 8048660:       8d 04 02                lea    (%edx,%eax,1),%eax /* $eax = $edx + $eax + 1 */
 8048663:       0f b7 00                movzwl (%eax),%eax /* 将word(2字节)扩展为long(4字节)保存*/
 8048666:       83 e0 08                and    $0x8,%eax   /* isalnum */
 8048669:       85 c0                   test   %eax,%eax   
 804866b:       75 24                   jne    8048691 <filterchars+0x88> /* if $eax != 0 goto 8048691 */
 804866d:       e8 6a fd ff ff          call   80483dc <__ctype_b_loc@plt>
 8048672:       8b 10                   mov    (%eax),%edx
 8048674:       8b 45 ec                mov    0xffffffec(%ebp),%eax
 8048677:       03 45 08                add    0x8(%ebp),%eax
 804867a:       0f b6 00                movzbl (%eax),%eax
 804867d:       0f be c0                movsbl %al,%eax
 8048680:       01 c0                   add    %eax,%eax
 8048682:       8d 04 02                lea    (%edx,%eax,1),%eax
 8048685:       0f b7 00                movzwl (%eax),%eax
 8048688:       25 00 04 00 00          and    $0x400,%eax      /* isalpha*/
 804868d:       85 c0                   test   %eax,%eax
 804868f:       74 11                   je     80486a2 <filterchars+0x99>


 8048691:       8b 45 ec                mov    0xffffffec(%ebp),%eax  /* var_ec*/
 8048694:       03 45 08                add    0x8(%ebp),%eax   /* eax = &argv[1][var_ec] */
 8048697:       0f b6 10                movzbl (%eax),%edx
 804869a:       8b 45 fc                mov    0xfffffffc(%ebp),%eax
 804869d:       88 10                   mov    %dl,(%eax)
 804869f:       ff 45 fc                incl   0xfffffffc(%ebp)

 80486a2:       ff 45 ec                incl   0xffffffec(%ebp)      /* var_ec ++ */

 80486a5:       8b 45 ec                mov    0xffffffec(%ebp),%eax /* var_ec = 0*/
 80486a8:       3b 45 0c                cmp    0xc(%ebp),%eax        /* if (strlen(argv[1]) > = var_ec) goto 804864b */
 80486ab:       7e 9e                   jle    804864b <filterchars+0x42>
 80486ad:       8b 45 f8                mov    0xfffffff8(%ebp),%eax
 80486b0:       c9                      leave
 80486b1:       c3                      ret
 80486b2:       90                      nop
 80486b3:       90                      nop


filterchars()
{
	char *m = malloc(strlen(argv[1]) + 1);
	if (m == 0)
		exit();

}
int main(int argc, char **argv)
{
	if (argc != 2)
		exit();
	ptrace(PTRACE_ATTACH, getppid(), 0, 0);
	ptrace(PTRACE_DETACH, getppid(), 0, 0);

	if (strlen(argv[1]) >= 0x320)
		exit();
	filterchars(argv[1], strlen(argv[1]));
}
