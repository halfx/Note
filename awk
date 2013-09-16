
1. awk 'BEGIN{while(getline<"'$file1'")dict[$1]=1} (dict[$2]!=1){print $1"\t"$2"\t3"}' $file2 >> tmp_type
   awk首先读取file1并创建词典dict[],然后读取file2，测试fil2中的$2在dict是否存在，若不
存在，则将$2,$3输出到tmp_type(这样去除了file1和file2中的重复行)

2. awk '{print $1"\t"$2"\t4"}' $file1 | sed "s/'//g">> file2
   读取file1的$1和$2，并将其中的单引号（'）替换为空输出到file2中
