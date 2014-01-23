                             一. boost::scoped_ptr
  boost::scoped_ptr与std::auto_ptr非常类似,但是scoped_ptr不能拷贝,这意味着scoped_ptr不能转换
所有权。
  1. 不能转换所有权。这表明scoped_ptr管理的对象的生命周期仅仅局限于一个区间中(该指针所在的{}之间),
  无法传到区间之外,因此scoped_ptr对象不能作为函数的返回值。
  2. 不能共享所有权。因此scoped_ptr对象不能用在stl容器中。
  3. 不能用来管理数组对象。scoped_ptr通过delete来删除所管理的对象,而数组对象必须通过delete[]来删
  除,因此若要管理数组对象,需要使用scoped_array。


  scoped_ptr与shared_ptr相比,无法共享所有权,shared_ptr使用引用计数来管理对象,对shared_ptr和
  scoped_ptr的使用建议是：若需要共享所有权,则使用shared_ptr,若不需要共享,仅仅自动释放资源,
  使用scoped_ptr。


                             二. boost::shared_ptr
 1. boost::shared_ptr的注意事项：
  (1). 不要把一个原生指针给多个shared_ptr来管理.
   int *ptr = new int;
   boost::shared_ptr<int> p1(ptr);
   boost::shared_ptr<int> p2(ptr);

  (2). 不要在函数实参里创建shared_ptr
    function(shared_ptr<int>(new int),g());
    //可能的过程是先new int,然后调用g(),g()发生异常,shared_ptr<int>没有创建,int内存泄漏
    //推荐写法
    shared_ptr<int> p(new int());
    function(p, g());

  (3). shared_ptr作为被保护的对象的成员时,小心因循环引用造成无法释放资源。解决方案是使用
     weak_ptr来保存。

  (4). 不要把this指针赋给shared_ptr,如下面的代码,会在t释放时析构一次,shared_ptr释放时析构一次。

     class test
     {
       public:
         boost::shared_ptr<test> pget()
         {
           return boost::shared_ptr<test>(this);
         }
     };
     test t;
     boost::shared_ptr<test> pt = t.pget();

     解决方案是使用enable_shared_from_this来实现
     class test: public boost::enable_shared_from_this<test>
     {
       public:
         boost::shared_ptr<test> pget()
         {
           return shared_from_this();
         }
     };
     test t;
     boost::shared_ptr<test> pt = t.pget();

  2. std::tr1::shared_ptr和boost::shared_ptr
     在新版本的C++标准中引入了shared_ptr智能指针,名字空间是std::tr1::shared_ptr。它和
     boost::shared_ptr的用法相同,在gcc4.3.x及以上版本加上选项-std=gnu++0x即可。
