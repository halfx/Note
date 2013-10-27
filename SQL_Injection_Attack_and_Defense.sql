                   Chapter 1    What is SQL injection?

一. Incorrectly Handled Escape Characters
   SQL数据库使用单引号隔开数据和代码，因此可以使用单引号探测是否有SQL注入漏洞,在不同
的数据库中，使用不同特殊符号。

二. Incorrectly Handled Types
   在数字型的SQL注入中，并不需要输入单引号
   MySQL提供了一个函数LOAD_FILE来读取一个服务器上的文件并返回文件内容：
   UNION ALL SELECT LOAD_FILE('/etc/passwd')--
   MySQL还有一个内置命令可以创建和写入文件，下面这个例子创建了一个web shell:
   UNION SELECT "<? system($_REQUEST['cmd']); ?>" INFO OUTFILE "/var/www/html/victim.com.com/cmd.php"
   LOAD_FILE和SELECT INFO OUTFILE都需要FILE权限，默认情况下root用户拥有FILE权限。

三. Incorrectly Handled Query Assembly
   有些Web应用可以让用户输入要查询的列名和表名，这样可能存在漏洞
   /* build dynamic SQL statement */
   $SQL = "SELECT". $_GET["column1"]. ",". $_GET["column2"]. ",". $_GET["column3"].
   " From". $_GET["table"];
   $result = mysql_query($SQL);
   若程序过滤不严，那么攻击者可能通过设置这些变量获取密码之类的信息。

四. Incorrectly Handled Errors
   输入引起程序出错的代码让它返回与目标相关的信息，例如数据库的版本，服务器OS。

五. Incorrectly Handled Multiple Submissions
   在一个多级验证过程中，由于程序的复杂性可能存在某些步骤验证不严，导致验证被绕过。

六. Insecure Database Configuration
   数据库通常都有一些默认用户，例如SQL Server使用"sa"作为系统管理员帐户,MySQL使用
   "root"和"anonymous"帐户，在Oracle中，SYS,SYSTEM,DBSNMP和OUTLN在数据库安装时就已
   经创建了。
   服务应用通常应该运行在普通特权级别，但在Windows下，Oracle必须运行在SYSTEM特权级。
   
