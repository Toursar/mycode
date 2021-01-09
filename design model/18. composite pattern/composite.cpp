#include <iostream>
#include <vector>
#include <string>

//组合模式，利用对象之间的整体部分关系，实现一个树形结构，方便的管理访问控制每一个对象
class Company {
public:
    Company(std::string _name) : name(_name) {}
    virtual bool add(Company*) = 0;
    virtual bool remove(Company*) = 0;
    virtual Company *get_child(int) const = 0;
    virtual bool exec() const = 0;
protected:
    std::string name;
};

// 子树结构
class DepartmentA : public Company {
public:
    DepartmentA(std::string _name) : Company(_name) {}

    virtual ~DepartmentA() {
        for (int i = 0; i < member.size(); ++i) {
            delete member[i];
        }
    }

    bool add(Company* part) override {
        member.push_back(part);
        return true;
    }

    bool remove(Company* part) override {
        for (auto iter = member.begin(); iter != member.end(); ++iter) {
            if (*iter = part) {
                member.erase(iter);
                return true;
            }
        }
        return false;
    }

    bool exec() const override {
        if (member.empty()) {
            return false;
        }
        for (auto iter = member.begin(); iter != member.end(); ++iter) {
            std::cout << name << "-";
            (*iter)->exec();
        }
        return true;
    }

    Company *get_child(int num) const {
        return member[num];
    }
private:
    std::vector<Company *> member;
};

// 叶子节点不存在add remove get_child所以函数内不做实现
class Project : public Company {
public:
    Project(std::string _name) : Company(_name) {}

    bool add(Company* part) override {
        return true;
    }

    bool remove(Company* part) override {
        return true;
    }

    bool exec() const override {
        std::cout << name << "\n";
        return true;
    }

    Company *get_child(int num) const {
        return nullptr;
    }
};

int main() {
    // 创建一系列节点
    Company *part = new DepartmentA("0");
    Company *part1 = new DepartmentA("1");
    Company *part2 = new DepartmentA("2");
    Company *part11 = new DepartmentA("1");
    Company *part12 = new Project("2");
    Company *part21 = new DepartmentA("1");
    Company *part22 = new Project("2");
    // 给定节点之间的附属关系
    part->add(part1);
    part->add(part2);
    part1->add(part11);
    part1->add(part12);
    part2->add(part21);
    part2->add(part22);

    part->exec();
    delete part;
    return false;
}