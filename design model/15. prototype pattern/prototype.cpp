#include <iostream>
#include <string>
#include <List>

// 原型模式，让父类prototype在不知道子类是什么的情况下创建出子类对象的副本，进行操作。
class prototype {
public:
    virtual ~prototype() {
    }

    void cloneAndshow() {
        for (prototype* item : protolist) {
            prototype* temp = item->clone();
            item->info();
            delete temp;
        }
    }

    void addPrototype(prototype* imag) {
        protolist.push_front(imag);
    }
protected:
    virtual prototype *clone() = 0;
    virtual void info() const = 0;
private:
    // 保证一个原型只有一个数组维护所有原型对象
    static std::list<prototype *> protolist;
};

std::list<prototype *> prototype::protolist;

class item1 : public prototype {
public:
    item1() {
        name = "name1";
        age = 10;
        // 每当构建对象时，传递一个自身到父类中
        // 当然也可以独立写一个函数，需要时调用
        addPrototype(this);
    }
    item1(item1* item) {
        this->name = item->name;
        this->age = item->age;
    }

    void info() const override {
        std::cout << name << " " << age << "\n";
    }
    prototype* clone() override {
        // 子类为父类实现如何拷贝自己。
        return new item1(this);
    }
private:
    std::string name;
    int age;
};

class item2 : public prototype {
public:
    item2() {
        name = "name2";
        age =  20;
        addPrototype(this);
    }
    item2(item2* item) {
        this->name = item->name;
        this->age = item->age;
    }
    void info() const override {
        std::cout << name << " " << age << "\n";
    }
    prototype* clone() override {
        return new item2(this);
    }
private:
    std::string name;
    int age;
};

int main() {
    prototype *test1 = new item1;
    test1 = new item2;
    test1->cloneAndshow();
    delete test1;
    return 0;
}