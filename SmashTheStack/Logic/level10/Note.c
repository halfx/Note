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
 8048677:       c1 e0 04                shl    $0x4,%eax
 804867a:       29 c4                   sub    %eax,%esp
 804867c:       83 7d 08 01             cmpl   $0x1,0x8(%ebp)
 8048680:       7f 24                   jg     80486a6 <main+0x4a>
 8048682:       83 ec 08                sub    $0x8,%esp
 8048685:       68 88 89 04 08          push   $0x8048988
 804868a:       68 8e 89 04 08          push   $0x804898e
 804868f:       e8 ec fe ff ff          call   8048580 <printf@plt>
 8048694:       83 c4 10                add    $0x10,%esp
 8048697:       c7 85 9c fb ff ff 01    movl   $0x1,0xfffffb9c(%ebp)
 804869e:       00 00 00
 80486a1:       e9 0d 02 00 00          jmp    80488b3 <main+0x257>
 80486a6:       83 ec 04                sub    $0x4,%esp
 80486a9:       68 00 04 00 00          push   $0x400
 80486ae:       8b 45 0c                mov    0xc(%ebp),%eax
 80486b1:       83 c0 04                add    $0x4,%eax
 80486b4:       ff 30                   pushl  (%eax)
 80486b6:       8d 85 f8 fb ff ff       lea    0xfffffbf8(%ebp),%eax
 80486bc:       50                      push   %eax
 80486bd:       e8 4e fe ff ff          call   8048510 <strncpy@plt>
 80486c2:       83 c4 10                add    $0x10,%esp
 80486c5:       6a 00                   push   $0x0
 80486c7:       6a 01                   push   $0x1
 80486c9:       6a 00                   push   $0x0
 80486cb:       6a 00                   push   $0x0
 80486cd:       e8 2e fe ff ff          call   8048500 <ptrace@plt>
 80486d2:       83 c4 10                add    $0x10,%esp
 80486d5:       85 c0                   test   %eax,%eax
 80486d7:       0f 89 94 00 00 00       jns    8048771 <main+0x115>
 80486dd:       a1 92 89 04 08          mov    0x8048992,%eax
 80486e2:       8b 15 96 89 04 08       mov    0x8048996,%edx
 80486e8:       89 85 f0 fb ff ff       mov    %eax,0xfffffbf0(%ebp)
 80486ee:       89 95 f4 fb ff ff       mov    %edx,0xfffffbf4(%ebp)
 80486f4:       a1 9a 89 04 08          mov    0x804899a,%eax
 80486f9:       8b 15 9e 89 04 08       mov    0x804899e,%edx
 80486ff:       89 85 e8 fb ff ff       mov    %eax,0xfffffbe8(%ebp)
 8048705:       89 95 ec fb ff ff       mov    %edx,0xfffffbec(%ebp)
 804870b:       80 bd f0 fb ff ff 00    cmpb   $0x0,0xfffffbf0(%ebp)
 8048712:       75 0e                   jne    8048722 <main+0xc6>
 8048714:       80 bd e8 fb ff ff 00    cmpb   $0x0,0xfffffbe8(%ebp)
 804871b:       75 05                   jne    8048722 <main+0xc6>
 804871d:       e9 91 01 00 00          jmp    80488b3 <main+0x257>
 8048722:       83 ec 08                sub    $0x8,%esp
  8048725:       68 a4 89 04 08          push   $0x80489a4
 804872a:       68 c4 89 04 08          push   $0x80489c4
 804872f:       e8 4c fe ff ff          call   8048580 <printf@plt>
 8048734:       83 c4 10                add    $0x10,%esp
 8048737:       83 ec 04                sub    $0x4,%esp
 804873a:       68 00 04 00 00          push   $0x400
 804873f:       8d 85 f8 fb ff ff       lea    0xfffffbf8(%ebp),%eax
 8048745:       50                      push   %eax
 8048746:       8d 85 a8 fb ff ff       lea    0xfffffba8(%ebp),%eax
 804874c:       50                      push   %eax
 804874d:       e8 be fd ff ff          call   8048510 <strncpy@plt>
 8048752:       83 c4 10                add    $0x10,%esp
 8048755:       83 ec 08                sub    $0x8,%esp
 8048758:       8d 85 a8 fb ff ff       lea    0xfffffba8(%ebp),%eax
 804875e:       50                      push   %eax
 804875f:       68 c4 89 04 08          push   $0x80489c4
 8048764:       e8 17 fe ff ff          call   8048580 <printf@plt>
 8048769:       83 c4 10                add    $0x10,%esp
 804876c:       e9 42 01 00 00          jmp    80488b3 <main+0x257>
 8048771:       a1 9a 89 04 08          mov    0x804899a,%eax
 8048776:       8b 15 9e 89 04 08       mov    0x804899e,%edx
 804877c:       89 85 e8 fb ff ff       mov    %eax,0xfffffbe8(%ebp)
 8048782:       89 95 ec fb ff ff       mov    %edx,0xfffffbec(%ebp)
 8048788:       a1 92 89 04 08          mov    0x8048992,%eax
 804878d:       8b 15 96 89 04 08       mov    0x8048996,%edx
 8048793:       89 85 f0 fb ff ff       mov    %eax,0xfffffbf0(%ebp)
 8048799:       89 95 f4 fb ff ff       mov    %edx,0xfffffbf4(%ebp)
 804879f:       8d 85 e8 fb ff ff       lea    0xfffffbe8(%ebp),%eax
 80487a5:       83 ec 0c                sub    $0xc,%esp
 80487a8:       50                      push   %eax
 80487a9:       e8 b2 fd ff ff          call   8048560 <strlen@plt>
 80487ae:       83 c4 10                add    $0x10,%esp
 80487b1:       89 c3                   mov    %eax,%ebx
 80487b3:       8d 85 f0 fb ff ff       lea    0xfffffbf0(%ebp),%eax
 80487b9:       83 ec 0c                sub    $0xc,%esp
 80487bc:       50                      push   %eax
 80487bd:       e8 9e fd ff ff          call   8048560 <strlen@plt>
 80487c2:       83 c4 10                add    $0x10,%esp
 80487c5:       39 c3                   cmp    %eax,%ebx
 80487c7:       0f 85 bf 00 00 00       jne    804888c <main+0x230>
 80487cd:       c7 85 a4 fb ff ff 00    movl   $0x0,0xfffffba4(%ebp)
 80487d4:       00 00 00
 80487d7:       a0 c7 89 04 08          mov    0x80489c7,%al
 80487dc:       88 85 a3 fb ff ff       mov    %al,0xfffffba3(%ebp)
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
 804881e:       e8 4d fd ff ff          call   8048570 <fopen@plt>
 8048823:       83 c4 10                add    $0x10,%esp
 8048826:       89 85 a4 fb ff ff       mov    %eax,0xfffffba4(%ebp)
 804882c:       ff b5 a4 fb ff ff       pushl  0xfffffba4(%ebp)
 8048832:       6a 08                   push   $0x8
 8048834:       6a 01                   push   $0x1
 8048836:       8d 85 a3 fb ff ff       lea    0xfffffba3(%ebp),%eax
 804883c:       50                      push   %eax
 804883d:       e8 4e fd ff ff          call   8048590 <fread@plt>
 8048842:       83 c4 10                add    $0x10,%esp
 8048845:       c6 84 05 a3 fb ff ff    movb   $0x0,0xfffffba3(%ebp,%eax,1)
 804884c:       00
 804884d:       83 ec 08                sub    $0x8,%esp
 8048850:       68 e0 89 04 08          push   $0x80489e0
 8048855:       68 8e 89 04 08          push   $0x804898e
 804885a:       e8 21 fd ff ff          call   8048580 <printf@plt>
 804885f:       83 c4 10                add    $0x10,%esp
 8048862:       83 ec 08                sub    $0x8,%esp
 8048865:       8d 85 a3 fb ff ff       lea    0xfffffba3(%ebp),%eax
 804886b:       50                      push   %eax
 804886c:       68 8e 89 04 08          push   $0x804898e
 8048871:       e8 0a fd ff ff          call   8048580 <printf@plt>
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
 80488b3:       8b 85 9c fb ff ff       mov    0xfffffb9c(%ebp),%eax
 80488b9:       8b 5d fc                mov    0xfffffffc(%ebp),%ebx
 80488bc:       c9                      leave
 80488bd:       c3                      ret
 80488be:       90                      nop
 80488bf:       90                      nop