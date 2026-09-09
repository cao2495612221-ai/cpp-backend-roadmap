#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
//
using fun=std::function<bool(int)>;

bool test(std::vector<int>& vec,fun f)
{
    //测试一下lambda表达式作为回调函数的效果
    int size=vec.size();
    bool flag=true;
    //这个test函数的主要作用就是测试一下vec里面的元素是否全是偶数
    for(int i=0;i<size;++i)
    {
        if(f(vec[i]))
        {
            flag=false;
            break;
        }
    }
    return flag;
}
bool is_odd(const int & num)
{
    return num%2==0?false:true;
}

int main(int argc,char* argv[])
{
    std::vector<int> vec={1,2,3,4,5,6,7,8,9};
    std::vector<int> vec2={2,4,6,8,10,12,14,16,18};
    if(test(vec,[](int num){return num%2==0?false:true;}))
    {
        std::cout<<"vec里面的元素全是偶数"<<std::endl;
    }
    else
    {
        std::cout<<"vec里面的元素不全是偶数"<<std::endl;
    }

    return 0;
}