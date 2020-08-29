#include<iostream>

using namespace std;
//抽象工厂主要用于同一个产品，存在多种不同子产品情况
//如下代码，每一个product都存在Pro和普通的两种。
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

class pro_product
{
public:
    pro_product()
    {
        cout << "pro constructor" << endl;
    }
    virtual ~pro_product()
    {
        cout << "de-pro" << endl;
    }
    virtual void pro_product_way() = 0;
};

class pro_son1 : public pro_product
{
public:
    pro_son1()
    {
        cout << "pro son1" << endl;
    }
    virtual ~pro_son1()
    {
        cout << "de pro son1" << endl;
    }
    void pro_product_way()
    {
        cout << "create pro son1" << endl;
    }
};

class pro_son2 : public pro_product
{
public:
    pro_son2()
    {
        cout << "pro son2" << endl;
    }
    virtual ~pro_son2()
    {
        cout << "de pro son2" << endl;
    }
    void pro_product_way()
    {
        cout << "create pro son2" << endl;
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
    virtual pro_product *create_pro() = 0;
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
    pro_product *create_pro()
    {
        return new pro_son1;
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
    pro_product *create_pro()
    {
        return new pro_son2;
    }
};

int main()
{
    factory *test1 = new son1_fac;
    product *test2 = test1->create();
    pro_product *test3 = test1->create_pro();
    test2->creat_product();
    test3->pro_product_way();
    delete test3;
    delete test2;
    delete test1;
    return 0;
}

//这样就满足了开放封闭性原则