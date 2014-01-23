/*
 *
 */
Quoting the abs() man page:

Trying to take the absolute value of the most negative integer is not
defined.
As this is not defined, the compiler does as it pleases. With GCC, the value returned will be the most negative integer itself, causing abs() to do nothing.

level2@io:/levels$ ./level02 -2147483648 -1
source code is available in level02.c

WIN!
sh-4.1$
There we go! Level 2 is complete.

$more .pass
G2K2EP1luDpdNQ
