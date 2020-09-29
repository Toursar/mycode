#include<iostream>
//模板方法模式,父类定义宏观的步骤，子类实现具体步骤怎么做
class template_method {
public:
    template_method(){}
    virtual ~template_method(){}
    virtual void step1() = 0;
    virtual void step2() = 0;
    virtual void do_job() {
        std::cout << "start" << std::endl;
        step1();
        step2();
        std::cout << "finish" << std::endl;
    }
};

class method1 : public template_method {
public:
    method1(){}
    ~method1(){}
    void step1() override {
        std::cout << "method1's step1" << std::endl;
    }
    void step2() override {
        std::cout << "method1's step2" << std::endl;
    }
};

class method2 : public template_method {
public:
    method2(){}
    ~method2(){}
    void step1() override {
        std::cout << "method2's step1" << std::endl;
    }
    void step2() override {
        std::cout << "method2's step2" << std::endl;
    }
};

int main() {
    template_method *test1 = new method1;
    template_method *test2 = new method2;
    test1->do_job();
    test2->do_job();
    delete test1;
    delete test2;
    test1 = nullptr;
    test2 = nullptr;
    return 0;
}