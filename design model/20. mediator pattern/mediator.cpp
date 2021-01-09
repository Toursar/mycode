#include <iostream>
#include <vector>
#include <string>

// 中介者模式，通过添加一个中介者，各个相互耦合的类通过中介者进行耦合
// 从而去除了多个类之间的复杂耦合关系

class Colleague;

// 中介者抽象
class Mediator {
public:
    virtual void regist(Colleague *coll) = 0;
    virtual void relay(std::string Id, std::string msg) const = 0;

protected:
    std::vector<Colleague *> customers;
};

// 同事类的抽象
class Colleague {
public:
    Colleague(std::string _id) : id(_id) {}
    void setMedia(Mediator* _media) {
        this->media = _media;
    }
    virtual void send(std::string id, std::string _msg) const = 0;
    virtual void recieve(std::string _id, std::string _msg) const = 0;
    std::string getId() {
        return id;
    }
protected:
    Mediator *media;
    std::string id;
};

// 中介者的具体实现
class Concretemedia : public Mediator {
public:
    void regist(Colleague* coll) override {
        customers.push_back(coll);
        coll->setMedia(this);
    }
    void relay(std::string Id, std::string msg) const override {
        for (auto a : customers) {
            if (a->getId() == Id) {
                a->recieve(a->getId(), msg);
            }
        }
    }
};

// 两个不同的同事类的实现，这里的两个虚函数send和recieve实现其实是一样的，可以将其提升到共同的父类
// 但是大多是情况，这些抽象函数的实现是不同的，所以这里就不往父类中提取了
class ConcreteColleague1 : public Colleague {
public:
    ConcreteColleague1(std::string _id) : Colleague(_id) {}
    void send(std::string id, std::string _msg) const override {
        std::cout << this->id << " send message to " << id << "\n";
        media->relay(id, _msg);
    }
    void recieve(std::string _id, std::string _msg) const override {
        std::cout << "recieve message from " << _id << " is " << _msg << "\n";
    }
};

class ConcreteColleague2 : public Colleague {
public:
    ConcreteColleague2(std::string _id) : Colleague(_id) {}
    void send(std::string id, std::string _msg) const override {
        std::cout << this->id << " send message to " << id << "\n";
        media->relay(id, _msg);
    }
    void recieve(std::string _id, std::string _msg) const override {
        std::cout << "recieve message from " << _id << " is " << _msg << "\n";
    }
};

int main() {
    Mediator *mda = new Concretemedia;
    Colleague *coll1 = new ConcreteColleague1("No.1");
    Colleague *coll2 = new ConcreteColleague2("No.2");
    mda->regist(coll1);
    mda->regist(coll2);
    coll1->send("No.2", "Hello!");
    coll2->send("No.1", "You too!");
}