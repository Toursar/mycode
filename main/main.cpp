#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cmath>

using namespace std;

namespace convert_test
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
        //不为静态变量赋值，会默认给0,指针给nullptr
        static int a;
        cout << "a = " << a << endl;
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
        //调用一此构造函数，在创建对象时，调用一次拷贝构造在传参时
    }
    void test2(Test& a)
    {
        //仅调用一次构造函数
    }
    //测试构造函数调用情况,引用的作用
    void test_main()
    {
        Test a;
        test1(a);
        test2(a);
    }
}
//模板的特化，偏特化
namespace template_test
{
    template<class T1, class T2>
    class Test
    {
    public:
        Test(T1 _a, T2 _b) : a(_a), b(_b)
        {
            cout << "general template constrctor" << endl;
        }
        ~Test() { cout << "deconstruct" << endl; }
    private:
        T1 a;
        T2 b;
    };

    template<class T1, class T2>
    class Test<T1*, T2*>
    {
    public:
        Test(T1* _a, T2* _b) : a(_a), b(_b)
        {
            cout << "partial pointer specialization constrctor" << endl;
        }
        ~Test() { cout << "deconstruct" << endl; }
    private:
        T1* a;
        T2* b;
    };

    template<class T2>
    class Test<int, T2>
    {
    public:
        Test(int _a, T2 _b) : a(_a), b(_b)
        {
            cout << "partial int specialization constrctor" << endl;
        }
        ~Test() { cout << "deconstruct" << endl; }
    private:
        int a;
        T2 b;
    };

    template<>
    class Test<int, double>
    {
    public:
        Test(int _a, double _b) : a(_a), b(_b)
        {
            cout << "all int double specialization constrctor" << endl;
        }
        ~Test() { cout << "deconstruct" << endl; }
    private:
        int a;
        double b;
    };
    int main_test()
    {
        int a = 1, c = 2;
        double b = 2.1, d = 3.2;
        cout << "test1 using ";
        //优先调用偏特化版本，会调用<int,T2>的版本
        Test<int, int> test1(a, c);
        cout << "test2 using ";
        Test<int*, int*> test2(&a, &c);
        cout << "test3 using ";
        Test<int, double> test3(a, b);
        cout << "test4 using ";
        Test<double, double> test4(b, d);
        return 0;
    }
}

int main()
{
    return 0;
}
