#include<iostream>

using namespace std;
//模板方法模式
class template_method
{
public:
    template_method(){｝
    virtual ~template_method(){}
    virtual void do_its_own_job() = 0;
};