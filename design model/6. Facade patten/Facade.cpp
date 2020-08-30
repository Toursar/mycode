#include<iostream>

using namespace std;
//外观模式，隐藏系统的复杂性，向客户端提供一个简单接口
//不满足开闭原则，增加功能需要对代码进行修改
class first_thing
{
public:
    first_thing(){};
    virtual ~first_thing(){}
    void dosomething()
    {
        cout << "first thing is done" << endl;
    }
};

class second_thing
{
public:
    second_thing(){};
    virtual ~second_thing(){}
    void dosomething()
    {
        cout << "second thing is done" << endl;
    }
};

class third_thing
{
public:
    third_thing(){};
    virtual ~third_thing(){}
    void dosomething()
    {
        cout << "third thing is done" << endl;
    }
};

class Facade
{
private:
    first_thing *test1 = new first_thing;
    second_thing *test2 = new second_thing;
    third_thing *test3 = new third_thing;
public:
    Facade(){}
    virtual ~Facade(){
        delete test1;
        delete test2;
        delete test3;
    }
    void doallthings()
    {
        test1->dosomething();
        test2->dosomething();
        test3->dosomething();
    }
};

int main()
{
    Facade *test1 = new Facade;
    test1->doallthings();
    return 0;
}