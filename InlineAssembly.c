1.

#include <stdio.h> 
int main(int argc, char const *argv[])
{
	/* code */
	int a = 1, b = 2, c = 0, d = 0;
	asm(
		"addl %0, %3"
		:"=g"(c), "=g"(d)
		:"0"(a), "1"(b)
		:"memory");
	printf("A=%d, B=%d, C=%d, D=%d\n",a,b,c,d);
	return 0;
}
A = 1 B = 2 C = 1 D = 3

%0对应"=g"(c)，%1对应"=g"(d)，%2对应"0"(a)，%3对应"1"(b)，c和d为输出变量，
但是输入变量%2共享输出变量%0，%3共享输出变量%1，执行过程如下：

1. 首先选取寄存器存放%0和%3

$ gcc -s gcc_add.s gcc_add.c
$ cat gcc_add.s

main:
.LFB2:
    pushq   %rbp
.LCFI0:
    movq    %rsp, %rbp
.LCFI1:
    subq    $16, %rsp
.LCFI2:
    movl    $1, -4(%rbp)   ; a=1
    movl    $2, -8(%rbp)   ; b=2
    movl    $0, -12(%rbp)  ; c=0
    movl    $0, -16(%rbp)  ; d=0
    movl    -4(%rbp), %eax ; eax = a = 1
    movl    -8(%rbp), %edx ; edx = b = 2
#APP
    addl %eax, %edx        ; edx = edx + eax = 3
#NO_APP
    movl    %edx, -16(%rbp) ; d = edx = 3
    movl    %eax, -12(%rbp) ; c = eax = 1
    movl    -16(%rbp), %eax ; eax = d = 3
    movl    -12(%rbp), %ecx ; ecx = c = 0
    movl    -8(%rbp), %edx  ; edx = b = 2
    movl    -4(%rbp), %esi  ; esi = a = 1
    movl    %eax, %r8d      ; 
    movl    $.LC0, %edi
    movl    $0, %eax
    call    printf  
    movl    $0, %eax
    leave   
    ret


#include <stdio.h>
int main()
{
    int a = 1, b = 2, c = 0,d = 0;
    asm(
        "addl %0, %3"
        :"=g"(c),"=g"(d)
        :"0"(a),"r"(b)   /* 注意这里在上一个程序中是"1"(b) */
        :"memory");
    printf("A = %d B = %d C = %d D = %d\n", a,b,c,d);
    return 0;
}

A = 1 B = 2 C = 1 D = 0

main:
.LFB2:
    pushq   %rbp
.LCFI0:
    movq    %rsp, %rbp
.LCFI1:
    subq    $16, %rsp
.LCFI2:
    movl    $1, -4(%rbp)     ; a=1
    movl    $2, -8(%rbp)     ; b=2
    movl    $0, -12(%rbp)    ; c=0
    movl    $0, -16(%rbp)    ; d=0
    movl    -8(%rbp), %eax   ; eax = b = 2
    movl    -4(%rbp), %edx   ; edx = a = 1
#APP
    addl %edx, %eax          ; eax = eax + edx = 3
#NO_APP
    movl    %edx, -12(%rbp)  ; c = edx = 1
    movl    -16(%rbp), %eax  ; eax = d = 0
    movl    -12(%rbp), %ecx  ; ecx = c = 0
    movl    -8(%rbp), %edx   ; edx = b = 2
    movl    -4(%rbp), %esi  
    movl    %eax, %r8d
    movl    $.LC0, %edi
    movl    $0, %eax
    call    printf  
    movl    $0, %eax
    leave   
    ret