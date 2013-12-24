level8@blackbox:~$ ls -l secrets 
-rws--x--x 1 level9 level9 12254 Dec 29  2007 secrets

/* Use  hexedit to edit binary file */
sniper@sniper-Aspire-4752:/media/D/github/Note/SmashTheStack/BlackBox$ hexedit level8.bin
/* ndisasm: 
   -b 32  :bitsize = 32 
   -o 0x8048464 : start address = 0x8048464
 */
sniper@sniper-Aspire-4752:/media/D/github/Note/SmashTheStack/BlackBox$ ndisasm -b 32 -o 0x8048464 level8.bin > level8.
/*
  decode string from hex to ascii character
*/
level8@blackbox:/tmp$ python -c "print '%r' % '555b5b5a526357666358564d246c\
2223'.decode('hex')"
'U[[ZRcWfcXVM$l"#'
