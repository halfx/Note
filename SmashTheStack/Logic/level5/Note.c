/* 将level5.cpp copy下来修改后运行 */
#include <stdio.h>
#include <stdlib.h>
void
decrypt
   (char *c, size_t l, unsigned int k)
{
   unsigned int kc;
   int i;

   for (i=0; i<l; ++i)
   {
      kc = k;
      while (kc > 0)
      {
         c[i] ^= kc & 0xFF;
         kc >>= 8;
      }
   }
}

int main()
{
   unsigned int key = 0xDEADBABE;
   volatile unsigned int manipulator;
   unsigned int bit;
   char c;
   char msg[] = "\x1b\x13\x13\x18\x5c\x16\x13\x1e\x5c\x10"
                "\x15\x10\x5b\x5c\x1e\x09\x18\x18\x05\x52"
                "\x5c\x0c\x1d\x0f\x0f\x0b\x13\x0e\x18\x46"
                "\x5c\x27\x0c\x1d\x0f\x0f\x0b\x13\x0e\x18"
                "\x5c\x1b\x13\x19\x0f\x5c\x14\x19\x0e\x19"
                "\x21";


   bit = (unsigned int)1;
   manipulator = (bit << 25) | (bit << 9) | (bit << 1) | (bit << 22) |
                 (bit << 14) | (bit << 23) | (bit << 7) |
                 (bit << 27) | bit;
   key ^= manipulator;
    decrypt(msg, 51, key);
   printf("%s",msg);
   scanf("%c",&c);
   return 0;
}

/* 
运行结果：good job lil’ buddy. password: [password goes here]
猜想我们要的密码字符串也是按照“good job lil’ buddy. password:”开头，所以在
level5.exe中搜索这个字符串
$ objdump -s level5.exe | grep 1b131318
定位地址后获得：
409260 63744e6f 76446563 00000000 1b131318  ctNovDec........
409270 5c16131e 5c101510 5b5c1e09 18180552  \...\...[\.....R
409280 5c0c1d0f 0f0b130e 18465c32 1d493d19  \........F\2.I=.
409290 0c14155c 5c5c5c5c 5c000000 7065656b  ...\\\\\\...peek
4092a0 61626f6f 21000000 49207365 6520796f  aboo!...I see yo
4092b0 75210000 00000000 48000000 00000000  u!......H.......
将“1b131318 
5c16131e 5c101510 5b5c1e09 18180552  
5c0c1d0f 0f0b130e 18465c32 1d493d19  
0c14155c 5c5c5c5c 5c” 放到程序中解密

char msg[] = "\x1b\x13\x13\x18"
             "\x5c\x16\x13\x1e"
         "\x5c\x10\x15\x10"
             "\x5b\x5c\x1e\x09"
         "\x18\x18\x05\x52"
             "\x5c\x0c\x1d\x0f"
             "\x0f\x0b\x13\x0e"                
             "\x18\x46\x5c\x32"
         "\x1d\x49\x3d\x19"
         "\x0c\x14\x15\x5c"
         "\x5c\x5c\x5c\x5c"
         "\x5c";
再重新运行输出： good job lil' buddy. password: Na5Aephi 
*/