1.  makefile中的函数:
      wildcard : 扩展通配符  
      notdir ：  去除路径
      $(subst <from>,<to>,<text>) : 把字串<text>中的<from>字符串替换成<to>

      $(patsubst <pattern>,<replacement>,<text>):查找<text>中的单词（单词以“空格”、
      “Tab”或“回车”“换行”分隔）是否符合模式<pattern>，如果匹配的话，则以<replacement>
      替换。这里，<pattern>可以包括通配符“%”，表示任意长度的字串。如果<replacement>中
      也包含“%”，那么，<replacement>中的这个“%”将是<pattern>中的那个“%”所代表的字串。
      （可以用“/”来转义，以“/%”来表示真实含义的“%”字符）

      $(strip <string>): 去掉<string>字串中开头和结尾的空字符

      $(findstring <find>,<in>): 在字串<in>中查找<find>字串,如果找到，那么返回<find>，
      否则返回空字符串。

      $(filter <pattern...>,<text>): 以<pattern>模式过滤<text>字符串中的单词，保留
      符合模式<pattern>的单词。可以有多个模式。返回符合模式<pattern>的字串。
      
      $(filter-out <pattern...>,<text>): 以<pattern>模式过滤<text>字符串中的单词，
      去除符合模式<pattern>的单词。可以有多个模式。返回不符合模式<pattern>的字串。

例子：
建立一个测试目录，在测试目录下建立一个名为sub的子目录
$ mkdir test
$ cd test
$ mkdir sub

在test下，建立a.c和b.c2个文件，在sub目录下，建立sa.c和sb.c2 个文件

建立一个简单的Makefile
src=$(wildcard *.c ./sub/*.c)
dir=$(notdir $(src))
obj=$(patsubst %.c,%.o,$(dir) )

all:
@echo $(src)
@echo $(dir)
@echo $(obj)
@echo "end"

执行结果分析：
第一行输出：
a.c b.c ./sub/sa.c ./sub/sb.c

wildcard把 指定目录 ./ 和 ./sub/ 下的所有后缀是c的文件全部展开。

第二行输出：
a.c b.c sa.c sb.c
notdir把展开的文件去除掉路径信息

第三行输出：
a.o b.o sa.o sb.o

在$(patsubst %.c,%.o,$(dir) )中，patsubst把$(dir)中的变量符合后缀是.c的全部替换成.o，
任何输出。
或者可以使用
obj=$(dir:%.c=%.o)
效果也是一样的。

这里用到makefile里的替换引用规则，即用您指定的变量替换另一个变量。
它的标准格式是
$(var:a=b) 或 ${var:a=b}
它的含义是把变量var中的每一个值结尾用b替换掉a


2. makefile中的变量: $@ ,"$@"表示目标的集合，就像一个数组,"$@"依次取出目标，并
   用于执行命令

   make命令的参数 -C <dir>;
                  --directory=<dir>
                  指定用来读取makefile的目录
                  -s
                  --silent
                  --quiet
                  在命令运行时不输出命令的输出