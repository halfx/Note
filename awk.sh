
1. awk 'BEGIN{while(getline<"'$file1'")dict[$1]=1} (dict[$2]!=1){print $1"\t"$2"\t3"}' $file2 >> tmp_type
   awk首先读取file1并创建词典dict[],然后读取file2，测试fil2中的$2在dict是否存在，若不
存在，则将$2,$3输出到tmp_type(这样去除了file1和file2中的重复行)，若读取一行，则getline返回1，若到达文件
结尾，则返回0，若出错，返回-1
   每一个print结束后都会换行，printf不换行

2. awk '{print $1"\t"$2"\t4"}' $file1 | sed "s/'//g">> file2
   读取file1的$1和$2，并将其中的单引号（'）替换为空输出到file2中

3. awk中的函数： 
   length(s):对字符串s求长度，中文每个汉字长度为2
   split(s,a,sep): 使用sep将字符串s分隔开，结果作为一个awk列表保存在a中
   match(string, regular expression) : match函数返回在字符串中正则表达式
         位置的索引，如果找不到指定的正则表达式则返回0。match函数会设置
         内建变量RSTART为字符串中子字符串的开始位置，RLENGTH为到子字符串末尾的字符个数

3. sed '/^[a-z]\t[a-z]\t3$/d' |LC_ALL=C
   删除匹配模式/^[a-z]\t[a-z]\t3$的行，以小写字母开头，以3结尾，中间用\t隔开，只有一个小写字母
   LC_ALL=C 是为了去除所有本地化的设置，让命令能正确执行

   awk '{if ($1~/^([0-9])+$/) print $0}'  "~"在awk中表示匹配操作符,该正则表达式
   的意思是：以数字开头，并且以数字结尾，中间全部为数字的行，即一整行只有数字 

4. awk中的数字变量:$0,$1...。$0代表读取的那整行，$1代表整行的第一个域，以此类推，
   域之间的分隔符为tab或空格，NF表示目前的记录被分割的字段的数目，NF可以理解为Number of Field
   NR表示从awk开始执行后，按照记录分隔符读取的数据次数，默认的记录分隔符为换行符，因此默认的就
   是读取的数据行数，NR可以理解为Number of Record的缩写。

5. @awk '{if(length($$1)>2) print $$2 "\t" $$1}' $(PREFIX).all | uniq -f1 -D > term.py.all.dyz
   在makefile中，$$1与脚本中的$1意思一样，代表第一个域

6. cut命令默认使用tab(\t)作为分隔符，可以用-d指定分隔符，例如： cut -d' ' -f1-2 data ，使用空格作为
   分隔符取出data中每行的第一和第二部分

7. uniq -f1 -D：过滤重复行，忽略第一部分(-f1)，并且输出所有的重复行(-D)

8. sed 's/\([nl]\)ue/\1ve/g' ：查找文本中的nue或lue，将其替换为nve或lve
   其中的"\(" 和 "\)"不能省略
   $ echo 'abcabcabc' | sed 's/\(ab\)\(c\)/\1d\2/g'
   abdcabdcabdc
   \1和\2分别指代()中的内容，\1指代第一个()中的内容，\2指代第二个()中的内容，
   上面的语句将ab替换为abd，c直接输出

9. tr "|" "'" tr命令将字符|替换为'