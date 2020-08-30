#include<iostream>

using namespace std;
//状态模式，根据传入的state类的区别，进行不同的操作
class state
{
public:
    state(){}
    virtual ~state(){}
    virtual void do_diff_things() = 0;
};

class state_one : public state
{
public:
    state_one(){}
    ~state_one(){}
    void do_diff_things() override
    {
        cout << "do things in one model" << endl;
    }
};

class state_two : public state
{
public:
    state_two(){}
    ~state_two(){}
    void do_diff_things() override
    {
        cout << "do things in two model" << endl;
    }
};
//进行操作的主体
class context
{
private:
    state *state1 = nullptr;
public:
    context(){}
    virtual ~context(){
        if (state1 != nullptr)
        {
            delete state1;
            state1 = nullptr;
        }
    }
    void change_state(state* state1)
    {
        if (this->state1 != nullptr)
        {
            delete this->state1;
            this->state1 = nullptr;
        }
        this->state1 = state1;
    }
    void do_diff_things()
    {
        state1->do_diff_things();
    }
};

int main()
{
    context *test1 = new context;
    //创建不同的状态实例，如果直接传递临时对象，需要在
    //change_state中注意内存分配
    //state *test2 = new state_one();
    //state *test3 = new state_two();
    test1->change_state(new state_one);
    test1->do_diff_things();
    test1->change_state(new state_two);
    test1->do_diff_things();
    delete test1;
    //delete test2;
    //delete test3;
    return 0;
}