#include<iostream>
#include<string>
#include<mutex>
#include<set>
//享元模式
class flyweight {
protected:
    int state = 0;
public:
    virtual void set_ele(const std::string &) = 0;
    virtual void back_ele() = 0;
};

class concrete : public flyweight {
private:
    std::string things;
public:
    concrete(std::string things) {
        this->things = things;
    }
    void set_ele(const std::string &user) override {
        std::cout << user << " using " << things << std::endl;
        state = 1;
    }
    void back_ele() override {
        state = 0;
    }
    int get_state() {
        return state;
    }
};

std::mutex mtx;

class factory {
private:
    std::set<concrete *> pool;
    static factory *flyweight_singleton;
    class del_single{
        ~del_single() {
            if (flyweight_singleton)
                delete flyweight_singleton;
        }
    };
    static del_single del;
    factory() {
        for (int i = 1; i <= 2; ++i) {
            std::string temp = " thing_";
            temp.push_back(i + '0');
            pool.insert(new concrete(temp));
        }
    }
public:
    factory(factory &) = delete;
    factory &operator=(const factory&) = delete;
    static factory* get_instence() {
        if (!flyweight_singleton) {
            std::lock_guard<std::mutex> lock(mtx);
            if (!flyweight_singleton) {
                flyweight_singleton = new factory();
            }
        }
        return flyweight_singleton;
    }
    concrete* get_concrete() {
        for (concrete* a : pool) {
            if (a->get_state() == 0) {
                return a;
            }
        }
        return nullptr;
    }
};

factory* factory::flyweight_singleton = nullptr;

int main() {
    factory *fac = factory::get_instence();
    concrete *test1 = fac->get_concrete();
    test1->set_ele("asd");
    concrete *test2 = fac->get_concrete();
    test2->set_ele("qwe");
    test2->back_ele();
    concrete *test3 = fac->get_concrete();
    test3->set_ele("zxc");
    std::cout << (test1 == test2) << (test2 == test3) << std::endl;
    delete fac;
    delete test1;
    delete test2;
    delete test3;
    return 0;
}