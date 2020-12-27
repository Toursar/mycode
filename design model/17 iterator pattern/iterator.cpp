#include <iostream>

// 迭代器模式

// 首先创建一个链表
// 定义链表的节点
struct Node {
    Node *next;
    int val;
    Node(int num) : next(nullptr) , val(num) {}
};

class Iterator;
class concreteIter;

// 链表的操作类
class Mlist {
public:
    Mlist() : head(nullptr), tail(nullptr), dummyHead(new Node(-1)), size(0) {}

    Mlist(Mlist &) = default;

    ~Mlist() {
        Node *temp = dummyHead;
        while (temp != nullptr) {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
    }

    void add(int num) {
        Node *temp = new Node(num);
        if (size == 0) {
            head = temp;
            dummyHead->next = head;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
        ++size;
    }

    void add(std::initializer_list<int> nums) {
        Node *temp = new Node(*(nums.begin()));
        if (head == nullptr) {
            head = temp;
            dummyHead->next = head;
        }
        if (tail == nullptr) {
            tail = temp;
        }
        ++size;
        for (auto iter = nums.begin() + 1; iter != nums.end(); ++iter) {
            Node *temp = new Node(*iter);
            tail->next = temp;
            tail = temp;
            ++size;
        }
    }

    bool remove(Node* node) {
        Node *cur = head, *pre = dummyHead;
        while (cur != nullptr) {
            if (cur != node) {
                pre = cur;
                cur = cur->next;
                continue;
            }
            if (size == 1) {
                head = tail = nullptr;
            } else if (pre == dummyHead) {
                head = cur->next;
                dummyHead->next = head;
            } else if (cur == tail) {
                tail = pre;
            }
            pre->next = cur->next;
            delete cur;
            --size;
            return true;
        }
        return false;
    }

    Node* get_head() const {
        return this->head;
    }

    Node* get_tail() const {
        return this->tail;
    }

    Iterator *getIterator();

    int getSize() const {
        return size;
    }

private:
    Node *head;
    Node *tail;
    Node *dummyHead;
    int size;
};

// 抽象的iterator
class Iterator {
public:
    virtual bool has_next() const = 0;
    virtual Iterator *next() = 0;
    virtual Node *operator*() const = 0;
};

// 实现对于Mlist的iterator操作
class concreteIter : public Iterator {
public:
    concreteIter(Mlist* m_list) : list(m_list), curNode(m_list->get_head()), currentIdx(1) {}
    bool has_next() const override {
        if (currentIdx == list->getSize()) {
            return false;
        }
        return true;
    }

    Iterator* next() override {
        curNode = curNode->next;
        ++currentIdx;
        return this;
    }

    Node* operator*() const {
        return curNode;
    }
private:
    Mlist* list;
    Node *curNode;
    int currentIdx;
};

Iterator* Mlist::getIterator() {
    return new concreteIter(this);
}


int main() {
    Mlist list;
    list.add({1, 2, 3});
    Iterator* iter = list.getIterator();
    std::cout << (*(*iter))->val << " ";
    while (iter->has_next()) {
        iter = iter->next();
        std::cout << (*(*iter))->val << " ";
    }
    std::cout << std::endl;
    return 0;
}