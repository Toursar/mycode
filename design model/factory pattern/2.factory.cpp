#include<iostream>

using namespace std;
//工厂也派生出对应的子类，创建不同对象，有不同的子工厂完成
class product
{
public:
    product(){
        cout << "father constructor" << endl;
    }
    virtual ~product(){
        cout << "father deconstructor" << endl;
    }
    virtual void creat_product() = 0;
};


class son_product1 : public product
{
public:
    son_product1()
    {
        cout << "son1_product" << endl;
    }
    ~son_product1()
    {
        cout << "de son1_product" << endl;
    }
    void creat_product()
    {
        cout << "create son1" << endl;
    }
};

class son_product2 : public product
{
public:
    son_product2()
    {
        cout << "son2_product" << endl;
    }
    ~son_product2()
    {
        cout << "de son2_product" << endl;
    }
    void creat_product()
    {
        cout << "create son2" << endl;
    }
};

class factory
{
public:
    factory(){
        cout << "factory constructor" << endl;
    };
    virtual ~factory(){
        cout << "factory deconstructor" << endl;
    };
    virtual product *create() = 0;
};

class son1_fac : public factory
{
public:
    son1_fac()
    {
        cout << "son1_fac" << endl;
    }
    ~son1_fac()
    {
        cout << "de son1_fac" << endl;
    }
    product *create()
    {
        return new son_product1;
    }
};

class son2_fac : public factory
{
public:
    son2_fac()
    {
        cout << "son2_fac" << endl;
    }
    ~son2_fac()
    {
        cout << "de son2_fac" << endl;
    }
    product *create()
    {
        return new son_product2;
    }
};

int main()
{
    factory *test1 = new son1_fac;
    product *test2 = test1->create();
    test2->creat_product();
    delete test2;
    delete test1;
    return 0;
}

//这样就满足了开放封闭性原则