#include<iostream>

using namespace std;
//代理模式
class subject
{
protected:
    subject(){}
public:
    virtual ~subject(){}
    virtual void dowork() = 0;
};

class be_proxyed : public subject
{
public:
    be_proxyed(){}
    virtual ~be_proxyed(){}
    void dowork()
    {
        cout << "know what to do" << endl;
    }
};

class proxy : public subject
{
private:
    subject *sub;
    void notice()
    {
        cout << "told subject" << endl;
    }
    void memo()
    {
        cout << "memory client" << endl;
    }
public:
    proxy(){
        sub = new be_proxyed;
    }
    virtual ~proxy(){
        if (sub != nullptr)
        {
            delete sub;
            sub = nullptr;
        }
    }
    void dowork()
    {
        notice();
        sub->dowork();
        memo();
    }
};

int main()
{
    subject *test1 = new proxy;
    test1->dowork();
    delete test1;
    test1 = nullptr;
    return 0;
}