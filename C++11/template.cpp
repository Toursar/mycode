#include<iostream>

using namespace std;

//递归输出的终点
void test()
{
	cout << "null" << endl;
}

//递归输出的终点，选择此函作为递归终点
template<typename T>
void test(T head)
{
	cout << head << endl;
}

//可变长参数模板，递归输出
//程序会先调用此函数，每次处理一个参数，参数总长度减少，直到变长参数为空
template<typename T, typename ...Args>
void test(T head, Args... args)
{
	cout << head << endl;
	//递归终点的函数需要提前声明，否则会导致找不到递归终点函数
	test(args...);
}

int main()
{
    // test(1.2, 'a', 1);
	// test();
	int a = 0, b, c = 1;
	int d = (b = a, c);
	cout << a << b << c << d;
	return 0;
}