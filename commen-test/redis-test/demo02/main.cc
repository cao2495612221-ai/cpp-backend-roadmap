#include <iostream>
#include <hiredis/hiredis.h>
#include <string>
#include <sys/time.h>
#include <memory>
//自定义删除器,首先智能指针在回收资源的时候,是通过删除器来进行
//资源的释放的,所以我们可以自定义一个删除器,这个删除器的主要目的就是为了
//释放redisContext对象,因为这个对象是通过redisFree来进行释放,而且redisContext
//底层是一个C语言结构体,C语言结构体没有析构函数的
struct redisContextDeleter 
{
    //重载操作符
    void operator()(redisContext *context) noexcept
    {
        if(context!=nullptr)
        {
            std::cout<<"自定义删除器,释放资源"<<std::endl;
            redisFree(context);
        }
    }
};

//using 对类型进行一个重新绑定
using unique_redisContext_ptr=std::unique_ptr<redisContext,redisContextDeleter>;
//自动实现一个工厂函数,这个函数的主要目的就是生产一个context对象
unique_redisContext_ptr make_unique_redisContext(const char* str,int port,const struct timeval& timeout={1,500000})
{
    //创建一个context对象
    redisContext * context=redisConnectWithTimeout(str,port,timeout);
    //判断一下初始化的结果
    if(context==nullptr||context->err)
    {
        throw std::runtime_error("redis connect faild");
    }
    return unique_redisContext_ptr(context);
}

void test(int argc,char* argv[])
{

    try{
        std::string ip=argc>1? argv[1]:"127.0.0.1";
        int port =argc>2? std::stoi(argv[2]):6379;
        std::cout<<"ip:"<<ip<<" port:"<<port<<std::endl;
        unique_redisContext_ptr context=make_unique_redisContext(ip.c_str(),port);

    }
    catch(const std::exception& e)
    {
        std::cerr<<"异常处理!!!"<<std::endl;
        std::cerr<<e.what()<<std::endl;
    }
    
}

int main(int argc,char* argv[])
{

    test(argc,argv);


    return 0;
}