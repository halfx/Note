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
   数据库元数据：
   1. MySQL5.0+：INFORMATION_SCHEMA(虚拟数据库)，可使用SHOW DATABASE和SHOW TABLES访问。每一个
      MySQL用户都可以访问，但是只能看到拥有相应权限的对象。
   2. SQL Server: INFORMATION_SCHEMA或系统表(sysobjects,sysindexkeys,syscolumns,systypes等等)
      或者通过系统存储过程(system stored procedures)。SQL Server 2005引入了一些叫"sys.*"的目录
      视图，限制用户只能访问拥有权限的对象。所有的SQL Server用户均有权访问数据库中的表并可以查
      看表中的所有行，而不管用户是否对表或所查阅的数据拥有相应的访问权限。
   3. Oracle提供了很多全局内置视图来访问Oracle的元数据(ALL_TABLES、ALL_TAB_COLUMNS等)。这些视
      图列出了当前用户可访问的属性和对象。此外，以USER_开头的视图只显示当前用户拥有的对象(例如，
      更加受限的元数据视图)；以DBA_开头的视图显示数据库中的所有对象(例如，用于数据库示例且不受
      约束的全局元数据视图)。DBA_元数据函数需要有数据库管理员(DBA)权限。
      
      隐藏或取消对MySQL数据库中INFORMATION_SCHEMA虚拟数据库的访问是不可能的，也不可能隐藏或取消对
   Oracle数据库中数据字典的访问(因为它是一个视图)。可以通过修改视图来对访问加以约束，但Oracle不提
   倡这么做。可以取消对SQL Server数据库中的INFORMATION_SCHEMA、system和sys.*表的访问，但这样会破
   坏某些功能并导致部分与数据库交互的应用出现问题。更好的解决办法是为应用的数据库访问运行一个最低
   权限模型，并针对程序的功能性需求适当地分离授权角色。
       
