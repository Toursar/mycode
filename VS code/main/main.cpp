#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cmath>

using namespace std;

namespace test1
{
    int a = 1;
    void short_convert()
    {
        short a = 1, b = 1;
        //下一句C++不会报错
        a = a + 1;
        b += 1;
        cout << "a = " << a << " b = " << b << endl;
    }
    void plus()
    {
        int a = 4;
        int b = 1;
        ++a = (++a) + (++a);
        cout << a << " " << b << endl;
    }
    void transfer()
    {
        int a = -1111;
        unsigned int b = 4294966185;
        short c;
        a = b;
        cout << a << endl;
    }
    void static_var()
    {
        static int a;
    }
}

namespace const_test
{
    void const_test()
    {
        int a = 1, b = 2;
        //1
        const int *ptr1 = &a;
        //下面会报错
        //*ptr1 = b;
        //可以通过
        ptr1 = &b;
        //2
        int *const ptr2 = &a;
        //可以通过
        *ptr2 = 2;
        //报错
        //ptr2 = &b;
        //3
        const int *const ptr3 = &a;
        //编译错误
        //const int c = 3;
        //int *ptr4 = &c;
    }
    void test1(const int a)
    {
        cout << a << endl;
        //++a;
    }
    void test2(const int* p1, int *const p2)
    {
        int a = 3;
        *p2 = 2;
        //致命错误，将指针指向局部变量，函数结束a会被释放
        p1 = &a;
    }
    void test3()
    {
        const int &a = 1;
        int c = 2;
        //非常引用初始量必须为左值。
        //int &b = 2;
        //int &const d = c;
    }
}

namespace class_test
{
    class Test
    {
    public:
        Test() { cout << "constrctor" << endl; }
        ~Test() { cout << "deconstruct" << endl; }
        Test(Test &a) { cout << "copy" << endl; }
    };
    void test1(Test a)
    {
    }
    void test2(Test& a)
    {
    }
    //测试构造函数调用情况,引用的作用
    void test_main()
    {
        Test a;
        test1(a);
        test2(a);
    }
}

class Test
{
public:
    Test(int _a, int _b) : a(_a), b(_b), c(&a)
    {
        cout << "constrctor" << endl;
    }
    ~Test() { cout << "deconstruct" << endl; }
    Test(Test &a) { cout << "copy" << endl; }
    void add() const;
    void ad() { add(); }

private:
    int a;
    mutable int b;
    int *c;
};

void Test::add() const
{
    cout << *c << endl;
    *c = b;
    cout << *c << a << endl;
}
int main()
{
    Test a(1, 2);
    a.add();
    return 0;
}
