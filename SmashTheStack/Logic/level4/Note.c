;
; Written by mh
;
section .data
        Deadbeef     db 'DeadbeefCafe',13,10
        dbl    equ      $ - Deadbeef   # Deadbeef长度
        ups     dw      '255'

section .bss
        up:     resb    255

section .text
    global _start

_start:
        mov     ebx, [esp + 8]

        call    That
        /* 测试That中文件打开是否成功 */
        test    eax,eax
        js      What

        call    Other
        test    eax,eax
        js      What

        call    This
        jne     What

        call    More

More:
        /* 49: geteuid */
        push    byte 49
        pop      eax
        int      0x80

        mov      ebx, eax 
        mov      ecx, eax 
        push     byte 70
        pop      eax 
        int      0x80
 
    
        xor      eax,eax
        push     eax 
        push     0x68732f2f
        push     0x6e69622f
        push     esp 
        pop      ebx 
        push     eax 
        push     ebx 
        mov      ecx, esp 
        xor      edx, edx 
        mov      byte al,11
        int      0x80
    

This:

        mov     esi,up  
        mov     edi,Deadbeef    
        mov     ecx,dbl 
        /* repe: 重复执行串操作指令的条件
           是(cx)!=0 AND ZF=1 
        CMPS指令只能用于比较ESI指向的内存和EDI
        指向的内存值，两个字符相等，ZF=1
        */
        repe    cmpsb    
        ret

Other:
/* ssize_t read(int fd, void *buf, size_t count); */
/* open返回文件描述傅，Other read该文件 */
        mov     ebx,eax    
        mov     eax,3    /* 3表示read */
        /* buf: up */
        /* count: ups */
        mov     ecx,up  
        mov     edx,ups

        int     80h  
        /* 测试返回值，若返回负数，则说明read失败，
           退出程序*/  
        test    eax,eax
        js      What

        ret

/* open(const char* pathname, int flags) */
/* #define __NR_open                       (__NR_SYSCALL_BASE+  5)*/
/* ebx: pathname: 用户可控制，argv[1]
   ecx: flags */
That:  
        mov     eax,5
        /* 以只读方式打开文件 */
        xor     ecx,ecx
        int     80h
        ret

/* 退出程序*/
What:
        mov     ebx,eax
        xor     eax,eax
        add     eax,1
        int     80h
 

/*
  程序比较用户提供的文件内容和字符串Deadbeef是否相同，
  相同则完全pass, Deadbeef由14个字符组成(DeadbeefCafe,13,10)
  13和10表示换行符和回车符
  在/tmp下创建一个文件DeadbeefCafe,写入DeadbeefCafe这12个
  字符，然后用"vim -b DeadbeefCafe"二进制打开，使用命令
   :%!xxd用16进制的方式打开文件:
    在结尾加上0d0a表示13和10
 最后读取文件
[level4@logic level4]$ ./level4 /tmp/level4/DeadbeefCafe 
sh-3.2$ whomi
sh: whomi: command not found
sh-3.2$ whoami
level5
sh-3.2$ cd /home/level5
sh-3.2$ ls -al
total 20
drwxr-xr-x  2 level5 level5 4096 Jun  2  2010 .
drwx--x--x 23 root   root   4096 Aug 17 20:20 ..
-rwxr-x---  1 root   level5 1708 Feb  5  2010 .bash_profile
-r--------  1 level5 level5    9 Apr 26  2010 .pass
-rw-r--r--  1 level5 level5 1469 Nov 15 19:45 tags
sh-3.2$ cat .pass
eing3Oip
sh-3.2$ 

  
*/
