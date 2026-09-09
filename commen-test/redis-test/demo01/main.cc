#include <iostream>
#include <hiredis/hiredis.h>
#include <string>
#include <sys/time.h>

//这个建立的连接显然是程序员自己要进行一个维护的,但是在工作中我们可以用一个对象来维护这个context
int  test()
{
    //该函数就是为了测试Redis服务器连接效果
    //创建连接的句柄
    redisContext *context=redisConnect("127.0.0.1",6379);
    //判断连接的情况
    //连接失败的时候
    if(context==nullptr||context->err)
    {
        //分两种
        if(context==nullptr)
        {
            std::cerr<<"连接失败!  没有分配内存"<<std::endl;
        }
        else
        {
            std::cerr<<"连接失败!  已分配内存,句柄状态错误!!!"<<std::endl;
            redisFree(context);
        }
        return -1;
    }
    else
    {
        std::cout<<"连接成功!!!"<<std::endl;
        //执行业务的操作

        //释放连接
        redisFree(context);
        return 0;
    }
}
//进阶版本,利用智能指针来维护我的context
//用unique_ptr的特性,也就是一个连接的资源只能由一个对象来维护,所以需要删除拷贝构造与赋值操作
class my_context
{

public:
my_context(const char* str,int port,const struct timeval& timeout={1,500000} )
:_context(redisConnectWithTimeout(str,port,timeout))
{
    // //判断一下初始化的结果
    if(_context==nullptr||_context->err)
    {
        throw std::runtime_error("redis connect faild");
    }
    else
    {
        std::cout<<"句柄初始化成功!"<<std::endl;
    }

}
my_context(my_context & con)=delete;
my_context& operator=(my_context& con)=delete;
~my_context()
{
    //析构函数
    if(_context!=nullptr)
    {
        redisFree(_context);
        std::cout<<"析构  释放内存!!!"<<std::endl;
    }
    else
    {
        std::cout<<"析构   不释放内存!!!"<<std::endl;
    }
}
private:
//这里面维护一个context指针类型
redisContext * _context;
};

void test2(int argc,char* argv[])
{
    //测试一下我创建的my_context类能否正常的维护我创建的context
    try
    {
        //创建一个my_context对象,这个是强构造函数,所以必须传入参数
        //首先先创建正常的参数
        std::string ip= argc>1? argv[1]:"127.0.0.1";
        int port=argc>2? std::stoi(argv[2]):6379;
        std::cout<<"ip:"<<ip<<" port:"<<port<<std::endl;
        my_context con(ip.c_str(),port);
    }
    catch(const std::exception& e)
    {
        //处理异常的情况
        std::cout<<"异常处理!!!"<<std::endl;
        std::cerr<<e.what()<<std::endl;
    }
}
int main(int argc,char* argv[])
{

    // int status=0;
    // status=test();
    test2(argc,argv);

    return 0;
}