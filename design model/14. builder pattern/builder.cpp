#include <iostream>
#include <vector>

// 生成器模式，对于复杂的构造函数问题，可以将每个组件的构造移动到另一个builder类中实现
// 避免了繁杂的构造函数的使用，同时对每个构造的组件使用工厂模式可以实现组件的多样化设计
// 其次添加一个主管类，可以实现类似的模板模式，给出一些既定的可用模板，不必用户亲自创建
class product {
public:
    void getpart() const {
        std::cout << "this product has parts:\n";
        for (const std::string& part : productParts) {
            std::cout << part << "\n";
        }
    }
    void addPart(const std::string& part) {
        productParts.push_back(part);
    }
private:
    std::vector<std::string> productParts;
};

class builder {
public:
    builder() : item(new product) {}
    virtual ~builder() {
        delete item;
    }
    virtual builder *produceWall() = 0;
    virtual builder *produceFloor() = 0;
    virtual builder *produceDoor() = 0;
    product* getproduct() {
        return item;
    }
    void reset() {
        if (item != nullptr) {
            delete item;
        }
        item = new product;
    }
protected:
    product *item = nullptr;
};

class concretBuilder : public builder {
    builder *produceWall() override {
        std::string part = "Wall";
        item->addPart(part);
        return this;
    }
    builder *produceFloor() override {
        std::string part = "Floor";
        item->addPart(part);
        return this;
    }
    builder *produceDoor() override {
        std::string part = "Door";
        item->addPart(part);
        return this;
    }
};

class templateMethod {
public:
    void setBuilder(builder* _builder) {
        if (build != _builder) {
            if (build == nullptr) {
                delete build;
            }
            build = _builder;
        }
    }

    void makeSimple() {
        build->produceWall()->getproduct()->getpart();
    }

    void makePro() {
        product* product1 = build->produceWall()->produceDoor()->produceFloor()->getproduct();
        product1->getpart();
    }
private:
    builder *build;
};

int main() {
    templateMethod model;
    builder *my = new concretBuilder;
    model.setBuilder(my);
    model.makeSimple();
    my->reset();
    model.makePro();
    delete my;
    my = nullptr;
}