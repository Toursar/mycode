#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>
#include<windows.h>

using namespace std;

int main()
{
    thread th1, th2;
    int i = 0;
    int a = 0, b = 0;
    int x = 0, y = 0;
    for (;;)
    {
        ++i;
        a = b = 0;
        x = y = 0;
        //如果CPU不乱序执行，那么一定不会出现x=0 && y=0的情况
        auto f1 = [&]() {a = 1;x = b;};
        auto f2 = [&]() {b = 1;y = a;};
        th1 = thread(f1);
        th2 = thread(f2);
        if (i % 10000 == 0)
            cout << "第" << i << "次" << endl;
        Sleep(1);
        if (x == 0 && y == 0)
        {
            cout << "第" << i << "次"
                 << " x = " << x
                 << " y = " << y << endl;
            //th1.join();
            //th2.join();
            th1.detach();
            th2.detach();
            break;
        }
        //th1.join();
        //th2.join();
        th1.detach();
        th2.detach();
    }
    return 0;
}