#include<iostream>

using namespace std;
//装饰器模式
class product
{
public:
    product()
    {
        cout << "product constructor" << endl;
    }
    virtual ~product()
    {
        cout << "product deconstructor" << endl;
    }
    virtual void dosomething() = 0;
};

class son_product : public product
{
public:
    son_product()
    {
        cout << "son_product constructor" << endl;
    }
    virtual ~son_product()
    {
        cout << "son_product deconstructor" << endl;
    }
    void dosomething()
    {
        cout << "do son_product thing" << endl;
    }
};

class decorator : public product
{
private:
    product *product1;
public:
    decorator(product *temp)
    {
        this->product1 = temp;
        cout << "decorator constructor" << endl;
    }
    virtual ~decorator()
    {
        cout << "decorator deconstructor" << endl;
    }
    void dosomething()
    {
        product1->dosomething();
        domorething();
    }
    virtual void domorething() = 0;
};

class decorator_1 : public decorator
{
private:
    //product *product1;
public:
    //父类没有默认构造，子类构造前需要通过参数列表调用对应父类的构造函数
    decorator_1(product *temp) : decorator(temp){}
    ~decorator_1(){}
    void domorething()
    {
        cout << "effect of 1" << endl;
    }
};

class decorator_2 : public decorator
{
private:
    //product *product1;
public:
    decorator_2(product *temp) : decorator(temp){}
    ~decorator_2(){}
    void domorething()
    {
        cout << "effect of 2" << endl;
    }
};

int main()
{
    //构建一个对象
    product *test1 = new son_product;
    //对对象进行装饰
    decorator *test2 = new decorator_1(test1);
    //对对象进行装饰
    decorator *test3 = new decorator_2(test2);
    test3->dosomething();
    delete test3;
    delete test2;
    delete test1;
    return 0;
}