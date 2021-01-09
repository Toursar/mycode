#include <iostream>
#include <string>

// 访问者模式，通过一个访问者类，将稳定的数据结构与易变的数据操作分离
class Visitor;

class ObjectStruct {
public:
    ObjectStruct(std::string _name) : name(_name) {}
    virtual void accept(Visitor* visitor) = 0;
    std::string getName() const {
        return name;
    }
private:
    std::string name;
};

class ConcreteElement1 : public ObjectStruct {
public:
    ConcreteElement1(std::string _name) : ObjectStruct(_name) {}

    void accept(Visitor *visitor) override;
};

class ConcreteElement2 : public ObjectStruct {
public:
    ConcreteElement2(std::string _name) : ObjectStruct(_name) {}

    void accept(Visitor *visitor) override;
};

class Visitor {
public:
    virtual void visit(ConcreteElement1* element) = 0;
    virtual void visit(ConcreteElement2* element) = 0;
};

class ConcreteVistor : public Visitor {
public:
    void visit(ConcreteElement1* element) override {
        std::cout << "visited " << element->getName() << "\n";
    }
    void visit(ConcreteElement2* element) override {
        std::cout << "visited " << element->getName() << "\n";
    }
};

void ConcreteElement1::accept(Visitor* visitor) {
        visitor->visit(this);
}

void ConcreteElement2::accept(Visitor* visitor) {
        visitor->visit(this);
}

int main() {
    ObjectStruct *part1 = new ConcreteElement1("A_part");
    ObjectStruct *part2 = new ConcreteElement2("B_part");
    Visitor *visitor = new ConcreteVistor;
    part1->accept(visitor);
    part2->accept(visitor);
    delete part1;
    delete part2;
    delete visitor;
    return 0;
}