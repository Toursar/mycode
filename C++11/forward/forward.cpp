#include<iostream>
#include<utility>

using namespace std;

void test(int& a){
    cout << "按引用传递" << endl;
}

void test(int&& a){
    cout << "按右值引用传递" << endl;
}

//使用模板参数的右值引用，可以接受左值右值的参数
template<typename T>
void func1(T && a) {
    //当调用函数形参作为另一个函数的参数时，无论如何都是左值
    test(a);
}

//使用模板参数的右值引用，可以接受左值右值的参数
template<typename T>
void func2(T && a) {
    //可以使用forward进行完美转发
    test(forward<T>(a));
}

int main()
{
    int a = 1;
    int& b = a;
    int &&c = 1;
    func1(a);
    func1(move(a));
    func2(move(b));
    func2(c);
    return 0;
}