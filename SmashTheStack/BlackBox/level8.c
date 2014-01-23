level8@blackbox:~$ ls -l secrets 
-rws--x--x 1 level9 level9 12254 Dec 29  2007 secrets

/* Use  hexedit to edit binary file */
sniper@sniper-Aspire-4752:/media/D/github/Note/SmashTheStack/BlackBox$ hexedit level8.bin
/* ndisasm: 
   -b 32  :bitsize = 32 
   -o 0x8048464 : start address = 0x8048464
 */
sniper@sniper-Aspire-4752:/media/D/github/Note/SmashTheStack/BlackBox$ ndisasm -b 32 -o 0x8048464 level8.bin > level8.asm
/*
  decode string from hex to ascii character
*/
level8@blackbox:/tmp$ python -c "print '%r' % '555b5b5a526357666358564d246c\
2223'.decode('hex')"
'U[[ZRcWfcXVM$l"#'

level8.asm : 由level8.bin生成
level8_source.c:反汇编对应的C伪代码
level8_core.c : 逆向程序

具体过程见level8.asm, level8_source.c, level8_core.c







#include <sys/ptrace.h>
#include <sys/fcntl.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


const int long_size = sizeof(long);
void getdata(pid_t child, long addr,
             char *str, int len)
{
    char *laddr;
    int i, j;
    union u
    {
        long val;
        char chars[long_size];
    }data;

    i = 0;
    j = len / long_size;
    laddr = str;

    while(i < j)
    {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * 4, NULL);
        memcpy(laddr, data.chars, long_size);
        ++i;
        laddr += long_size;
    }
    j = len % long_size;
    if(j != 0)
    {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * 4, NULL);
        memcpy(laddr, data.chars, j);
    }
    str[len] = '\0';
}

void putdata(pid_t child, long addr, char *str, int len)
{
    char *laddr;
    int i, j;
    union u
    {
        long val;
        char chars[long_size];
    }data;

    i = 0;
    j = len / long_size;
    laddr = str;
    while(i < j)
    {
        memcpy(data.chars, laddr, long_size);
        ptrace(PTRACE_POKEDATA, child, addr + i * 4, data.val);
        ++i;
        laddr += long_size;
    }
    j = len % long_size;
    if(j != 0)
    {
        memcpy(data.chars, laddr, j);
        ptrace(PTRACE_POKEDATA, child, addr + i * 4, data.val);
    }
}


int main(int argc, char **argv, char **environ) {
  int f;
  int addr = (int)strtoul(argv[1], NULL, 0);
  int len = atoi(argv[2]);
  f = fork();
  if (f == 0) {
    char *X[3] = { "/home/level8/secrets", NULL, NULL };
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    int ret = execve(X[0], X, environ);
    if(ret == -1)
        perror("execve");
    return 255;
  }
  else if (f > 0)
  {
     int pid = 0;
     int status;
     printf("Father process: child process pid = %d\n", f);
     int mark = 0;
     while (pid == 0 || errno != ECHILD) {
         pid = wait(&status);
         if(WIFEXITED(status))
         {
         }
        printf("SYSCALL=%d\nEIP=%p; EBP=%p;ESP=%p;ESI=%d;EDI=%d;EAX=%d;EBX=%d;ECX=%d;EDX=%d\n",U.orig_eax, U.eip, U.ebp, U.esp, U.esi, U.edi, U.eax, U.ebx,U.ecx,U.edx);
       if ( U.orig_eax == 5)
       {
          char code[4000]={0};
          getdata(f, addr, code, len);
          int i=0;
          for(i=0;i<len;i++)
          {
              printf("%02x",*(code+i) & 0xFF);
          }
          printf("\n\n");
          for(i=0;i<len;i++)
          {
             int val = ptrace(PTRACE_PEEKTEXT, pid, addr + 4 * i, NULL);
             printf("%02x", val & 0xFF);
             printf("%02x", (val >> 8) & 0xFF);
             printf("%02x", (val >> 16) & 0xFF);
             printf("%02x", (val >> 24) & 0xFF);
          }
          printf("\n\n");
          return 0;
       }
       ptrace(PTRACE_SYSCALL, f, NULL, NULL);
        //printf("***********************************\n");
     }
       }
  return 0;
}
}
