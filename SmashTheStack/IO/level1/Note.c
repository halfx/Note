/* 用gdb调试程序，跟踪字符串比较函数:wcscmp
 * 获取密码：271
 * 本程序用strings命令无法获取字符串密码
 * (gdb) disass main
Dump of assembler code for function main:
   0x08048080 <+0>:     push   $0x8049128
   0x08048085 <+5>:     call   0x804810f <puts>
   0x0804808a <+10>:    call   0x804809f <fscanf>
   0x0804808f <+15>:    cmp    $0x10f,%eax
   0x08048094 <+20>:    je     0x80480dc <YouWin>
   0x0804809a <+26>:    call   0x8048103 <exit>
End of assembler dump.
level1@io:/levels$ ./level01
Enter the 3 digit passcode to enter: 271
Congrats you found it, now read the password for level2 from /home/level2/.pass
sh-4.2$ cat /home/level2/.pass
hgvbmkQIHavkGg5wyk

 */
