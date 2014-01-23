#include <stdio.h>
#include <string.h>
void test_1(char *pass)
{
  char *var_c = "U[[ZRcWfcXVM$l\"#";
  printf("var_c length: %d\n", strlen(var_c));
  int index = 0;
  char s[100] = {0};
  char passwd[30] = {0};
  strcpy(passwd, pass);

  for(index = 0; index < strlen(passwd) - 1 && index <= 0x3fb; index++)
  {
    s[index] = passwd[index + 1] - passwd[index] + 0x5a;
  }

  s[index] = (passwd[index] >> 4) & 0xf + 0x21; /* index = strlen(passwd) - 1*/
  s[index + 1] = passwd[index] & 0xf + 0x21;    /* s[strlen(passwd)] = ... */
  s[index + 2] = 0;

  for(index = 0; index < strlen(s) - 1; index +=2 )
  {
    s[index] = s[index] ^ s[index + 1];
    s[index + 1] = s[index] ^ s[index + 1];
    s[index] = s[index] ^ s[index + 1];
  }

  if (strcmp(s, var_c) == 0)
    printf("SUCCESS\n");
  else
  {
    printf("Fail : source : %s\n,tmp : %s\n", var_c, s);
  }

}

int main(void)
{
  char *var_c = "U[[ZRcWfcXVM$l\"#";
  printf("var_c length: %d\n", strlen(var_c));
  int index = 0;
  char passwd[20] ={0};
  char s[100] = {0};
  for(index = 0; index < strlen(passwd) - 1 && index <= 0x3fb; index++)
  {
    s[index] = passwd[index + 1] - passwd[index] + 0x5a;
  }

  s[index] = (passwd[index] >> 4) & 0xf + 0x21; /* index = strlen(passwd) - 1*/
  s[index + 1] = passwd[index] & 0xf + 0x21;    /* s[strlen(passwd)] = ... */
  s[index + 2] = 0;
/*
  for(index = 0; index < strlen(s) - 1; index += 2)
  {
    s[index] = s[index] ^ s[index + 1];
    s[index + 1] = s[index] ^ s[index + 1];
    s[index] = s[index] ^ s[index + 1];
  }
  if (strcmp(s,var_c) == 0)
    printf("SUCCESS\n");
 */

  char s_tmp[100] = {0};
  for(index = strlen(var_c) -2; index >= 0 ; index -=2)
  {
    //printf("index = %d, var_c[index] = %c, var_c[index+1] = %c", index, var_c[index], var_c[index+1]);
    s_tmp[index] = var_c[index] ^ var_c[index + 1];
    s_tmp[index + 1] = s_tmp[index] ^ var_c[index + 1];
    s_tmp[index] = s_tmp[index] ^ s_tmp[index + 1];
  //  printf(", s_tmp:%s, char:%x\n", &s_tmp[index], s_tmp[index]);
  }
  //test_1(s_tmp, var_c);
  index = strlen(s_tmp);
  char tmp_1 = s_tmp[index-1] - 0x21; /* tmp_1 = 0x1 */
  char tmp_2 = s_tmp[index-2] - 0x21; /* tmp_2 = 0x2 ,则passwd[index] = 0010 0001 */
  printf("tmp_1 : 0x%x, tmp_2: 0x%x\n", tmp_1, tmp_2);

  passwd[index - 2] = 0x21;
  for(index = strlen(s_tmp)-3; index >= 0; index--)
  {
    passwd[index] = passwd[index + 1] - s_tmp[index] + 0x5a;
  }
  printf("passwd:%s, length:%d\n",passwd,strlen(passwd));
  test_1(passwd);
  return 0;
}
/*
sniper@sniper-Aspire-4752:/tmp$ ./level8_core 
var_c length: 16
tmp_1 : 0x1, tmp_2: 0x2
passwd:HIDDENFROMVIEW!, length:15
var_c length: 16
*/



