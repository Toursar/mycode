#include<iostream>

using namespace std;

class adaptee
{
public:
    adaptee(){}
    virtual ~adaptee(){}
    void request(int a)
    {
        cout << a << endl;
    }
};

class adaptor
{
public:
    adaptor(){}
    virtual ~adaptor(){}
    virtual void convert_request(int a, int b) = 0;
};

//可以不使用继承适配器类，直接在父类中进行接口转换
class version1_adaptor : public adaptor
{
private:
    adaptee *adaptee1;
public:
    version1_adaptor(adaptee * temp_adaptee){
        this->adaptee1 = temp_adaptee;
    };
    virtual ~version1_adaptor(){}
    void convert_request(int a, int b) override
    {
        //类似于转换接口操作
        a *= b;
        //调用原本的接口
        adaptee1->request(a);
    }
};

//直接在父类中进行接口转换
// class adaptor
// {
// private:
//     adaptee *adaptee1;
// public:
//     adaptor(adaptee * temp_adaptee){
//         this->adaptee1 = temp_adaptee;
//     }
//     virtual ~adaptor(){}
//     void convert_request(int a, int b)
//     {
//         a = a - b;
//         adaptee1->request(a);
//     }
// };


int main()
{
    //构建目标对象的实例
    adaptee *test1 = new adaptee;
    //将对象传给适配器包装
    adaptor *test2 = new version1_adaptor(test1);
    //调用适配器接口
    test2->convert_request(3, 1);
    delete test2;
    delete test1;
    return 0;
}