#include<iostream>
#include<functional>

using namespace std;

class Test
{
public:
    int add(int a, int b)
    {
        cout << "class member function" << endl;
        cout<< a << " + " << b << " = " << a + b << endl;
        return a + b;
    }
    int operator()(int a, int b)
    {
        cout << "functor" << endl;
        cout<< a << " + " << b << " = " << a + b << endl;
        return a + b;
    }
};

int add_1(int a, int b)
{
    cout << "function" << endl;
    cout<< a << " + " << b << " = " << a + b << endl;
    return a + b;
}

//lambda函数嵌套使用
void lambda_test()
{
    auto f1 = [](int j, int i) {
        auto f3 = [j](int i) {
            cout << i - j << endl;
        };
        f3(i);
    };
    f1(1, 2);
    //返回一个lambda函数指针
    auto f2 = [](int j) {
        return [j](int i) {
            cout << "i = " << i << " j = " << j << endl;
            return i - j;
        };
    };
    cout << f2(1)(2) << endl;
}

int main()
{
    //1. functional包装普通函数
    //function<int(int, int)> f1 = add_1;

    //2. functional包装lambda表达式
    // function<int(int, int)> f2 = [](int a, int b) {
    //     cout << "labmda function" << endl;
    //     cout<< a << " + " << b << " = " << a + b << endl;
    //     return a + b;    
    // };

    //3. 包装类成员函数
    //可以提前绑定成员函数，这样需要增加第一参数为this指针，即对象本省
    //在调用成员函数时，需要将对象的地址当做参数传递
    // function<int(Test *, int, int)> f3_1 = &Test::add;
    // Test test1;
    // cout << f3_1(&test1, 1, 2) << endl;
    //可以先定义对象实例，然后使用bind将成员函数的第一隐含参数绑定为this指针
    // Test test2;
    // function<int(int, int)> f3_2 = bind(&Test::add, &test2, placeholders::_1, placeholders::_2);
    // cout << f3_2(1, 2) << endl;

    //4. 仿函数
    // function<int(Test*, int, int)> f4_1 = &Test::operator();
    // Test test3;
    // cout << f4_1(&test3, 1, 2) << endl;
    // Test test4;
    // function<int(int, int)> f4_2 = bind(&Test::operator(), &test4, placeholders::_1, placeholders::_2);
    // cout << f4_2(1, 2) << endl;
    return 0;
}