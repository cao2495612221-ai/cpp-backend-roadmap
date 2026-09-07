#include <iostream>
#include <hiredis/hiredis.h>
#include <string>

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
my_context(const char* str,int port)
:_context(redisConnect(str,port))
{
    // //判断一下初始化的结果
    // if(_context==nullptr||_context->err)
    // {
    //     //分两种
    //     if(_context==nullptr)
    //     {
    //         std::cerr<<"连接失败!  没有分配内存"<<std::endl;
    //     }
    //     else
    //     {
    //         std::cerr<<"连接失败!  已分配内存,句柄状态错误!!!"<<std::endl;
    //     }
    // }
    // else
    // {
    //     std::cout<<"句柄初始化成功!"<<std::endl;
    // }
    if(!_context||_context->err)
    {
        throw std::runtime_error("redis connect faild");
    }

}
my_context(my_context & con)=delete;
my_context& operator=(my_context& con)=delete;
~my_context()
{
    //析构函数
    if(_context==nullptr)
    {

    }
}
private:
//这里面维护一个context指针类型
redisContext * _context;

};
int main(int argc,char* argv[])
{

    int status=0;
    status=test();
    if(status==0)
    {
        std::cout<<"yes"<<std::endl;
    }
    else
    {
        std::cout<<"no"<<std::endl;
    }

    return 0;
}