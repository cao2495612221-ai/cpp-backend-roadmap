#include <iostream>
#include <cstring>
#include <string>
#include <hiredis/hiredis.h>

int main(int argc,char * argv[])
{

	//创建一个Redis连接   首先ip地址是本地环路连接,默认端口号是6379
	redisContext * context=redisConnect("127.0.0.1",6379);
	
	//判断连接是否出错,根据redisContext的返回值来进行一个判断
	if(context==nullptr||context->err)
	{
		if(context)
		{
			std::cerr<<"连接失败:"<<context->errstr<<std::endl;
			//释放context
			redisFree(context);
		}
		else
		{
			std::cerr<<"连接失败:无法分配上下文"<<std::endl;
		}
		return -1;

	}
	else
	{
		std::cout<<"[1] redis 连接成功!!!!"<<std::endl;

		//业务代码
		
		redisFree(context);
	}
	
	return 0;
}
