#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
//简单的懒汉模式(需要申明指向对象的指针，不然没法不实例化，也没法判断是否成功创建)
//问题：
//1. 不是线程安全的
//2. 不会释放申请的空间
namespace version1
{
    class Singleton_pattern
    {
    private:
        static Singleton_pattern* Single;
        Singleton_pattern(){
            cout << "constructor" << endl;
        }
        Singleton_pattern(Singleton_pattern &test) = delete;
        Singleton_pattern& operator=(const Singleton_pattern &test) = delete;
    public:
        ~Singleton_pattern(){
            cout << "deconstructor" << endl;
        }
        static Singleton_pattern* get_Instance()
        {
            if (Single == nullptr)
            {
                Single = new Singleton_pattern();
            }
            return Single;
        }
        void method()
        {
            cout << "method function" << endl;
        }
    };
    Singleton_pattern* Singleton_pattern::Single = nullptr;
}
//利用智能指针以及锁，保证线程安全，并且释放申请的内存
//注意cpu的乱序执行会导致在初始化对象时先进行返回指针，然后在调用对象的构造函数
//这会导致后面的线程判断对象已被创建，从而取到未初始化的对象。需要增加内存屏障或C++11的atomic类
namespace version2
{
    mutex mex;
    //声明一个智能指针
    class Singleton_pattern
    {
    public:
        typedef shared_ptr<Singleton_pattern> ptr;
        ~Singleton_pattern(){
            cout << "deconstructor" << endl;
        };
        static ptr get_Instance()
        {
            //double checked lock(DCL),不加第一个判断，会使每个想要创建该对象的线程都进行上锁操作，效率很低
            //不加第二个判断，会导致如果多个线程都通过第一个判断，此时Single为空，只有一个线程获得锁
            //此时第一个线程创建对象以后，释放锁，其他线程依旧会继续竞争锁，然后再创建对象。
            if (Single == nullptr)
            {
                lock_guard<mutex> lock(mex);
                if (Single == nullptr)
                    Single = shared_ptr<Singleton_pattern>(new Singleton_pattern);
            }
            return Single;
        }
        void method()
        {
            cout << "method function" << endl;
        }
    private:
        static ptr Single;
        Singleton_pattern(){
            cout << "constructor" << endl;
        };
        Singleton_pattern(Singleton_pattern &test) = delete;
        Singleton_pattern& operator=(const Singleton_pattern &test) = delete;
    };
    Singleton_pattern::ptr Singleton_pattern::Single = nullptr;
}
//C++11以后的最简单的实现懒汉模式单例的方法
//注意需要注释version3，否则恶汉模式的对象会在程序开始时就实例化，造成误判
namespace version4
{
    class Singleton_pattern
    {
    public:
        static Singleton_pattern& get_instance()
        {
            static Singleton_pattern single;
            return single;
        }
    private:
        Singleton_pattern() {
            cout << "constructor" << endl;
        }
        ~Singleton_pattern(){
            cout << "deconstructor" << endl;
        }
        Singleton_pattern(Singleton_pattern &) = delete;
        Singleton_pattern &operator=(const Singleton_pattern &) = delete;
    };  
}
//恶汉模式，利用了内部类来辅助释放内存，占了额外内存，但是外部调用不需要也声明智能指针了
namespace version3
{
//     class Singleton_pattern
//     {
//     public:
//         ~Singleton_pattern(){
//             cout << "deconstructor" << endl;
//         }
//         Singleton_pattern(Singleton_pattern &);
//         Singleton_pattern &operator=(const Singleton_pattern &);
//         void method()
//         {
//             cout << "method function" << endl;
//         }
//         static Singleton_pattern* get_instance()
//         {
//             return Single;
//         }

//     private:
//         static Singleton_pattern* Single;
//         Singleton_pattern(){
//             cout << "constructor" << endl;
//         }
//         //为了让内存能够释放，定义一个内部类，其中的析构函数释放当前类的唯一一个实例
//         class delete_ver
//         {
//         public:
//             delete_ver(){};
//             ~delete_ver()
//             {
//                 //如果实例存在释放它
//                 if (Single != nullptr)
//                     delete Singleton_pattern::Single;
//             }
//         };
//         //声明一个静态的对象
//         static delete_ver p;
//     };
//     //实例化，该对象会在程序结束后析构。
//     Singleton_pattern::delete_ver Singleton_pattern::p;
//     Singleton_pattern* Singleton_pattern::Single = new Singleton_pattern;
}
int main()
{
    //version2::Singleton_pattern::ptr test1 = version2::Singleton_pattern::get_Instance();
    //version3::Singleton_pattern* test2 = version3::Singleton_pattern::get_instance();
    int a = 0;
    version4::Singleton_pattern &test3 = version4::Singleton_pattern::get_instance();
    return 0;
}