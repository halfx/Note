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

%0对应"=g"(c)，%1对应"=g"(d)，%2对应"0"(a)，%3对应"1"(b)，c和d为输出操作数
a和b为输入操作数，%2使用与%0相同的寄存器，%3使用与%1相同的寄存器

执行过程：
1. 首先选取寄存器存放%0和%1(例如%0选取eax，%1选取edx，由于输出操作数复用了输入操作数的
    寄存器，所以用a初始化了eax，b初始化了edx)
2. 执行"addl %0, %3"。由于%3使用与%1相同的寄存器，因此该语句相当于"addl %0, %1"
   也就是"addl %eax, %edx"(执行后eax=1，edx=3)
3. 执行后将结果返回，由于%0使用的寄存器eax在执行前使用a初始化，因此"=g(c)"将eax的值赋给
   c，即c=1，%1使用的edx执行后变为edx=3，则"=g"(d)将edx赋给d，d=3

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


    int a = 1, b = 2, c = 0,d = 0;
    asm(
        "addl %0, %3"
        :"=g"(c),"=g"(d)
        :"0"(a),"r"(b)   /* 注意这里在上一个程序中是"1"(b) */
        :"memory");
    printf("A = %d B = %d C = %d D = %d\n", a,b,c,d);

A = 1 B = 2 C = 1 D = 0

main:
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





    int a = 1, b = 2, c = 0,d = 0;
    asm(    
        "addl %0, %1"
        :"=g"(c),"=g"(d)
        :"0"(a),"r"(b)
        :"memory");
    printf("A = %d B = %d C = %d D = %d\n", a,b,c,d);
    return 0;

A = 1 B = 2 C = 1 D = 1


main:
.LCFI2:
    movl    $1, -4(%rbp)    ; a=1
    movl    $2, -8(%rbp)    ; b=2
    movl    $0, -12(%rbp)   ; c=0
    movl    $0, -16(%rbp)   ; d=0
    movl    -8(%rbp), %eax  ; eax = b = 2
    movl    -4(%rbp), %edx  ; edx = a = 1
#APP
    addl %edx, -16(%rbp)    ; d = d + edx = 1
#NO_APP
    movl    %edx, -12(%rbp) ; c = edx = 1
    movl    -16(%rbp), %eax  



    int a = 1, b = 2, c = 0,d = 0;
    asm(    
        "addl %0, %1"
        :"=g"(c),"=g"(d)
        :"0"(a),"1"(b)
        :"memory");
    printf("A = %d B = %d C = %d;D = %d\n", a,b,c,d);
    return 0;

A = 1 B = 2 C = 1;D = 3


main:
.LCFI2:
    movl    $1, -4(%rbp)
    movl    $2, -8(%rbp)
    movl    $0, -12(%rbp)
    movl    $0, -16(%rbp)
    movl    -4(%rbp), %eax   ; eax = a = 1
    movl    -8(%rbp), %edx   ; edx = b = 2
#APP
    addl %eax, %edx     ; edx = edx + eax = 3
#NO_APP
    movl    %edx, -16(%rbp)  ; d = edx = 3
    movl    %eax, -12(%rbp)  ; c = eax = 1
    movl    -16(%rbp), %eax





    int a = 1, b = 2, c = 0,d = 0;
    asm(
        "addl %2, %3"
        :"=g"(c),"=g"(d)
        :"0"(a),"1"(b)
        :"memory");
    printf("A = %d B = %d C = %d;D = %d\n", a,b,c,d);
    return 0;

A = 1 B = 2 C = 1;D = 3

main:
.LCFI2:
    movl    $1, -4(%rbp)
    movl    $2, -8(%rbp)
    movl    $0, -12(%rbp)
    movl    $0, -16(%rbp)
    movl    -4(%rbp), %eax   ; eax = a = 1
    movl    -8(%rbp), %edx   ; edx = b = 2
#APP
    addl %eax, %edx         ; edx = edx + eax = 3
#NO_APP
    movl    %edx, -16(%rbp) ; d = edx = 3
    movl    %eax, -12(%rbp) ; c = eax = 1
    movl    -16(%rbp), %eax
