#include <iostream>
#include <string>
#include <stack>

// 备忘录模式
// 定义一个与Document成员相同的备忘录类，保存修改过的数据
class Memo {
public:
    Memo(const std::string& _content) : content(_content) {}
    ~Memo() {}
    std::string getContent() {
        return content;
    }
private:
    std::string content;
};

// 真正的操作类，可以进行保存和利用备忘录内容恢复
class Document {
public:
    Document(std::string _content = "") : content(_content) {}

    ~Document() {}

    Memo* save() const {
        return new Memo(content);
    }

    void resume(Memo* demo) {
        this->content = demo->getContent();
    }

    void change(const std::string newContent) {
        this->content = newContent;
    }

    void print() const {
        std::cout << content << std::endl;
    }

private:
    std::string content;
};

// 利用栈结构维护所有的备忘录内容，需要恢复时弹出栈顶的备忘录即可
class History {
public:
    void add(Memo* demo) {
        hist.push(demo);
    }

    Memo* getLastversion() {
        Memo *temp = hist.top();
        hist.pop();
        return temp;
    }
private:
    std::stack<Memo *> hist;
};

int main() {
    History history;
    Document doc;
    // 进行一系列操作，并保存
    doc.change("123");
    history.add(doc.save());
    doc.change("456");
    history.add(doc.save());
    doc.change("789");
    history.add(doc.save());

    // 撤销修改
    doc.resume(history.getLastversion());
    doc.print();
    doc.resume(history.getLastversion());
    doc.print();

    return 0;
}