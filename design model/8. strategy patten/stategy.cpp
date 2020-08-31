#include<iostream>

using namespace std;
//策略模式,类似于状态模式，策略模式侧重于对同一个操作产生不同的方法完成
//状态模式则是，不同状态会产生不同操作
class strategy
{
public:
    strategy(){}
    virtual ~strategy(){}
    virtual void using_strategy() = 0;
};

class version1_strategy : public strategy
{
public:
    version1_strategy(){}
    ~version1_strategy(){}
    void using_strategy() override
    {
        cout << "using strategy model one" << endl;
    }
};

class version2_strategy : public strategy
{
public:
    version2_strategy(){}
    ~version2_strategy(){}
    void using_strategy() override
    {
        cout << "using strategy model two" << endl;
    }
};

class context
{
private:
    strategy *stg;
public:
    context(){
        stg = nullptr;
    };
    virtual ~context(){
        if (stg != nullptr)
        {
            delete stg;
            stg = nullptr;
        }
    };
    virtual void change_model(strategy* stg1)
    {
        if (stg != nullptr)
        {
            delete stg;
        }
        stg = stg1;
        stg->using_strategy();
    }
};

int main()
{
    strategy *test1 = new version1_strategy;
    strategy *test2 = new version2_strategy;
    context *context1 = new context;
    context1->change_model(test1);
    context1->change_model(test2);
    if (context1 != nullptr)
    {
        delete context1;
        context1 = nullptr;
    }
    return 0;
}