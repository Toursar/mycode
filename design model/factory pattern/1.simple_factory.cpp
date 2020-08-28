#include<iostream>

using namespace std;
//父类是产品类，定义一个虚函数，子类需要实现不同的生产方式
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
        cout << "son1_constructor" << endl;
    }
    ~son_product1()
    {
        cout << "deconstructor son1" << endl;
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
        cout << "son2_constructor" << endl;
    }
    ~son_product2()
    {
        cout << "deconstructor son2" << endl;
    }
    void creat_product()
    {
        cout << "create son2" << endl;
    }
};
//定义一个工厂，create函数对不同的接收参数，创建不同对象，返回值是父类对象指针
class factory
{
public:
    factory(){
        cout << "factory constructor" << endl;
    };
    ~factory(){
        cout << "factory deconstructor" << endl;
    };
    product* create(int name)
    {
        switch (name)
        {
        case 1:
            return (new son_product1);
            break;
        case 2:
            return (new son_product2);
            break;
        default:
            cout << "not have this product" << endl;
            return nullptr;
            break;
        }
    }
};

int main()
{
    factory* test = new factory;
    product* a = test->create(1);
    //产生的不同父类指针可以调用对应的子类方法
    a->creat_product();
    a == nullptr;
    delete a;
    delete test;
    //product* b = test.create(2);
    //product* c = test.create(3);
    return 0;
}
//简单工厂模式，每次新增一种产品，都需要对工厂类中的创建函数进行修改
//违背了开放封闭原则：对象实体可以拓展，但不可以修改