
1. awk 'BEGIN{while(getline<"'$file1'")dict[$1]=1} (dict[$2]!=1){print $1"\t"$2"\t3"}' $file2 >> tmp_type
   awk首先读取file1并创建词典dict[],然后读取file2，测试fil2中的$2在dict是否存在，若不
存在，则将$2,$3输出到tmp_type(这样去除了file1和file2中的重复行)，若读取一行，则getline返回1，若到达文件
结尾，则返回0，若出错，返回-1
   每一个print结束后都会换行，printf不换行

2. awk '{print $1"\t"$2"\t4"}' $file1 | sed "s/'//g">> file2
   读取file1的$1和$2，并将其中的单引号（'）替换为空输出到file2中

3. sed '/^[a-z]\t[a-z]\t3$/d' |LC_ALL=C
   删除匹配模式/^[a-z]\t[a-z]\t3$的行，以小写字母开头，以3结尾，中间用\t隔开，只有一个小写字母
   LC_ALL=C 是为了去除所有本地化的设置，让命令能正确执行

4. awk中的数字变量:$0,$1...。$0代表读取的那整行，$1代表整行的第一个域，以此类推，
   域之间的分隔符为tab或空格，NF表示目前的记录被分割的字段的数目，NF可以理解为Number of Field
   NR表示从awk开始执行后，按照记录分隔符读取的数据次数，默认的记录分隔符为换行符，因此默认的就
   是读取的数据行数，NR可以理解为Number of Record的缩写。

5. cut命令默认使用tab(\t)作为分隔符，可以用-d指定分隔符，例如： cut -d' ' -f1-2 data ，使用空格作为
   分隔符取出data中每行的第一和第二部分

6. uniq -f1 -D：过滤重复行，忽略第一部分(-f1)，并且输出所有的重复行(-D)
