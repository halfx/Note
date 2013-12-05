(gdb) disass main
Dump of assembler code for function main:
0x0804827a <main+0>:    lea    0x4(%esp),%ecx
0x0804827e <main+4>:    and    $0xfffffff0,%esp
0x08048281 <main+7>:    pushl  0xfffffffc(%ecx)
0x08048284 <main+10>:   push   %ebp
0x08048285 <main+11>:   mov    %esp,%ebp
0x08048287 <main+13>:   push   %ebx
0x08048288 <main+14>:   push   %ecx
0x08048289 <main+15>:   sub    $0x30,%esp
0x0804828c <main+18>:   lea    0xfffffff4(%ebp),%eax
0x0804828f <main+21>:   mov    %eax,(%esp)
0x08048292 <main+24>:   call   0x8072ec0 <_ZNSsC1Ev>
0x08048297 <main+29>:   lea    0xfffffff0(%ebp),%eax
0x0804829a <main+32>:   mov    %eax,(%esp)
0x0804829d <main+35>:   call   0x8072ec0 <_ZNSsC1Ev>
0x080482a2 <main+40>:   movl   $0x80ffe48,0x4(%esp)
0x080482aa <main+48>:   movl   $0x8130f60,(%esp)
0x080482b1 <main+55>:   call   0x806d8f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc>
0x080482b6 <main+60>:   lea    0xfffffff4(%ebp),%eax
0x080482b9 <main+63>:   mov    %eax,0x4(%esp)
0x080482bd <main+67>:   movl   $0x8130ec0,(%esp)
0x080482c4 <main+74>:   call   0x806b2e0 <_ZSt7getlineIcSt11char_traitsIcESaIcEERSt13basic_istreamIT_T0_ES7_RSbIS4_S5_T1_E>   /* 这个函数内输入Username */
0x080482c9 <main+79>:   movl   $0x80ffe53,0x4(%esp)  /* "Password:" */
0x080482d1 <main+87>:   movl   $0x8130f60,(%esp)
0x080482d8 <main+94>:   call   0x806d8f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc>
0x080482dd <main+99>:   lea    0xfffffff0(%ebp),%eax
0x080482e0 <main+102>:  mov    %eax,0x4(%esp)
0x080482e4 <main+106>:  movl   $0x8130ec0,(%esp)
0x080482eb <main+113>:  call   0x806b2e0 <_ZSt7getlineIcSt11char_traitsIcESaIcEERSt13basic_istreamIT_T0_ES7_RSbIS4_S5_T1_E>   /*这个函数内输入password */
0x080482f0 <main+118>:  movl   $0x80ffe5e,0x4(%esp)
0x080482f8 <main+126>:  lea    0xfffffff4(%ebp),%eax
0x080482fb <main+129>:  mov    %eax,(%esp)
0x080482fe <main+132>:  call   0x80483ee <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_>
0x08048303 <main+137>:  xor    $0x1,%al
0x08048305 <main+139>:  test   %al,%al                   /* 这里有个比较跳转的过程，因此推断上面的0x80483ee函数是执行字符串比较的 */
0x08048307 <main+141>:  jne    0x8048328 <main+174>
0x08048309 <main+143>:  movl   $0x80ffe65,0x4(%esp)
0x08048311 <main+151>:  lea    0xfffffff0(%ebp),%eax
0x08048314 <main+154>:  mov    %eax,(%esp)
0x08048317 <main+157>:  call   0x80483ee <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_>
0x0804831c <main+162>:  xor    $0x1,%al
0x0804831e <main+164>:  test   %al,%al
0x08048320 <main+166>:  jne    0x8048328 <main+174>
0x08048322 <main+168>:  movb   $0x1,0xffffffe7(%ebp)
0x08048326 <main+172>:  jmp    0x804832c <main+178>
0x08048328 <main+174>:  movb   $0x0,0xffffffe7(%ebp)
0x0804832c <main+178>:  movzbl 0xffffffe7(%ebp),%eax
0x08048330 <main+182>:  test   %al,%al
0x08048332 <main+184>:  je     0x8048366 <main+236>
0x08048334 <main+186>:  movl   $0x80ffe6e,0x4(%esp)
0x0804833c <main+194>:  movl   $0x8130f60,(%esp)
0x08048343 <main+201>:  call   0x806d8f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc>
0x08048348 <main+206>:  movl   $0x806e0c0,0x4(%esp)
0x08048350 <main+214>:  mov    %eax,(%esp)
0x08048353 <main+217>:  call   0x806bf10 <_ZNSolsEPFRSoS_E>
0x08048358 <main+222>:  movl   $0x80ffe80,(%esp)
0x0804835f <main+229>:  call   0x80b5ab0 <system>
0x08048364 <main+234>:  jmp    0x804838a <main+272>
0x08048366 <main+236>:  movl   $0x80ffe88,0x4(%esp)
0x0804836e <main+244>:  movl   $0x8130f60,(%esp)
---Type <return> to continue, or q <return> to quit---
0x08048375 <main+251>:  call   0x806d8f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc>
0x0804837a <main+256>:  movl   $0x806e0c0,0x4(%esp)
0x08048382 <main+264>:  mov    %eax,(%esp)
0x08048385 <main+267>:  call   0x806bf10 <_ZNSolsEPFRSoS_E>       /* 输出Invalid username or password */
0x0804838a <main+272>:  lea    0xfffffff0(%ebp),%eax
0x0804838d <main+275>:  mov    %eax,(%esp)
0x08048390 <main+278>:  call   0x8074e40 <_ZNSsD1Ev>
0x08048395 <main+283>:  jmp    0x80483ad <main+307>
0x08048397 <main+285>:  mov    %eax,0xffffffdc(%ebp)
0x0804839a <main+288>:  mov    0xffffffdc(%ebp),%ebx
0x0804839d <main+291>:  lea    0xfffffff0(%ebp),%eax
0x080483a0 <main+294>:  mov    %eax,(%esp)
0x080483a3 <main+297>:  call   0x8074e40 <_ZNSsD1Ev>
0x080483a8 <main+302>:  mov    %ebx,0xffffffdc(%ebp)
0x080483ab <main+305>:  jmp    0x80483c5 <main+331>
0x080483ad <main+307>:  lea    0xfffffff4(%ebp),%eax
0x080483b0 <main+310>:  mov    %eax,(%esp)
0x080483b3 <main+313>:  call   0x8074e40 <_ZNSsD1Ev>
0x080483b8 <main+318>:  mov    $0x0,%eax
0x080483bd <main+323>:  mov    %eax,0xffffffe0(%ebp)
0x080483c0 <main+326>:  jmp    0x80483e1 <main+359>
0x080483c2 <main+328>:  mov    %eax,0xffffffdc(%ebp)
0x080483c5 <main+331>:  mov    0xffffffdc(%ebp),%ebx
0x080483c8 <main+334>:  lea    0xfffffff4(%ebp),%eax
0x080483cb <main+337>:  mov    %eax,(%esp)
0x080483ce <main+340>:  call   0x8074e40 <_ZNSsD1Ev>
0x080483d3 <main+345>:  mov    %ebx,0xffffffdc(%ebp)
0x080483d6 <main+348>:  mov    0xffffffdc(%ebp),%eax
0x080483d9 <main+351>:  mov    %eax,(%esp)
0x080483dc <main+354>:  call   0x80a5180 <_Unwind_Resume>
0x080483e1 <main+359>:  mov    0xffffffe0(%ebp),%eax
0x080483e4 <main+362>:  add    $0x30,%esp
0x080483e7 <main+365>:  pop    %ecx
0x080483e8 <main+366>:  pop    %ebx
0x080483e9 <main+367>:  pop    %ebp
0x080483ea <main+368>:  lea    0xfffffffc(%ecx),%esp
0x080483ed <main+371>:  ret    
End of assembler dump.


(gdb) disass _ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_
Dump of assembler code for function _ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_:
0x080483ee <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+0>:    push   %ebp
0x080483ef <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+1>:    mov    %esp,%ebp
0x080483f1 <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+3>:    sub    $0x8,%esp
0x080483f4 <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+6>:    mov    0xc(%ebp),%eax
0x080483f7 <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+9>:    mov    %eax,0x4(%esp)
0x080483fb <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+13>:   mov    0x8(%ebp),%eax
0x080483fe <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+16>:   mov    %eax,(%esp)
0x08048401 <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+19>:   call   0x8073a20 <_ZNKSs7compareEPKc>
0x08048406 <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+24>:   test   %eax,%eax
0x08048408 <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+26>:   sete   %al
0x0804840b <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+29>:   movzbl %al,%eax
0x0804840e <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+32>:   leave  
0x0804840f <_ZSteqIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_EPKS3_+33>:   ret    
End of assembler dump.
(gdb) 
(gdb) x/8x $esp
0xbfffd8cc:     0x0804831c      0xbfffd8f8      0x080ffe65      0xbfffd8e8
0xbfffd8dc:     0x08048263      0x0811a1d8      0x08130ea4      0xbfffd8f8
(gdb) 
(gdb) x/s 0x080ffe65
0x80ffe65 <_IO_stdin_used+33>:   "PassFor2" (正确的密码)
(gdb) 
(gdb) x/s 0xbfffd8f8
0xbfffd8f8:      "糪222\023\b|\222\023\b"

                                       
(gdb) x/4x 0xbfffd8f8
0xbfffd8f8:     0x081392bc      0x0813927c      0xbfffd920      0x00000000
(gdb) x/s  0x081392bc
0x81392bc:       "asdasd\b\b\b"      (正是我自己输入的密码)
(gdb) 

level1@blackbox:~$ ./login2 
Username: level2
Password: PassFor2
Welcome, level 2!
sh-3.1$ 