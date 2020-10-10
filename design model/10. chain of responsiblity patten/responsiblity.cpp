#include<iostream>

using namespace std;
//责任链模式,如果责任连过长则会降低处理速度
class handler
{
protected:
    handler *handle;
public:
    handler(){
        handle = nullptr;
    }
    virtual ~handler(){
        if (handle != nullptr)
        {
            delete this->handle;
            this->handle = nullptr;
        }
    }
    void next_handler(handler* handle)
    {
        if (handle != nullptr)
        {
            delete this->handle;
        }
        this->handle = handle;
    }
    virtual void do_its_own_job(int info) = 0;
};

class chain1 : public handler
{
public:
    chain1(){}
    ~chain1(){}
    void do_its_own_job(int info)
    {
        if (info >= 0 && info < 6)
            cout << "chain_1's job" << endl;
        else
            handle->do_its_own_job(info);
    }
};

class chain2 : public handler
{
public:
    chain2(){}
    ~chain2(){}
    void do_its_own_job(int info)
    {
        if (info >= 6 && info <11)
            cout << "chain_2's job" << endl;
        else
            handle->do_its_own_job(info);
    }
};

class chain3 : public handler
{
public:
    chain3(){}
    ~chain3(){}
    void do_its_own_job(int info)
    {
        if (info >= 11 && info < 20)
            cout << "chain_3's job" << endl;
        else
            cout << "can not handle" << endl;
    }
};

int main()
{
    handler *hand1 = new chain1;
    handler *hand2 = new chain2;
    handler *hand3 = new chain3;
    hand1->next_handler(hand2);
    hand2->next_handler(hand3);
    hand1->do_its_own_job(15);
    delete hand1;
    return 0;
}