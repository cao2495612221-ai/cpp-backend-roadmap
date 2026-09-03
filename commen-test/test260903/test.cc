#include <iostream>
#include <vector>
using namespace std;

int main(int argc,char* argv[])
{
	
	char c=0;
	int num=0;
	vector<char> v;
	cin>>num;
	v.reserve(num);
	cin.get(c);
	c=0;
	while(num--)
	{
		cin.get(c);
		v.push_back(c);
	}
	for(auto & e:v)
	{
		cout<<"字符:"<<e<<"对应的ASCII:"<<(int)e<<endl;
	}
		
	
	return 0;
}
