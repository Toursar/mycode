#include<iostream>
#include<list>
#include<string>

using namespace std;
//提前声明主题对象，让观察者对象调用
class subject;
//观察者负责收到通知以后进行工作
class observer
{
protected:
    //用来获取主题对象传送的消息
    subject *sub;
public:
    observer(subject *sub){
        this->sub = sub;
    }
    virtual ~observer(){}
    virtual void be_noted() = 0;
};


class A_observer : public observer
{
public:
    A_observer(subject *sub) : observer(sub){}
    virtual ~A_observer(){}
    void be_noted() override;
};

class B_observer : public observer
{
public:
    B_observer(subject *sub) : observer(sub){}
    virtual ~B_observer(){}
    void be_noted() override;
};
//主题对象，维护观察者对象的链表，并且进行通知消息
class subject
{
protected:
    list<observer *> oberver_list;
public:
    //主题对象发送的消息，可由观察者接收
    string notice;
    subject(){}
    virtual ~subject(){};
    //将观察者加入链表
    virtual void add_observer(observer *ob) = 0;
    virtual void remove_observer(observer *ob) = 0;
    //通知所有观察者
    virtual void notify() = 0;
};

class subject_owner : public subject
{
public:
    subject_owner(){}
    virtual ~subject_owner(){}
    void add_observer(observer* ob) override
    {
        oberver_list.emplace_back(ob);
    }
    void remove_observer(observer* ob) override
    {
        for (list<observer *>::iterator iter = oberver_list.begin(); iter != oberver_list.end(); ++iter)
        {
            if (*iter == ob)
            {
                oberver_list.erase(iter);
                break;
            }
        }
    }
    void notify() override
    {
        for (auto iter = oberver_list.begin(); iter != oberver_list.end(); ++iter)
        {
            (*iter)->be_noted();
        }
    }
};
//只有主题对象定义以后才可以进行实现，因为需要调用sub.
void A_observer::be_noted()
{
    cout << "A do " << sub->notice << endl;
}

void B_observer::be_noted()
{
    cout << "B do " << sub->notice << endl;
}

int main()
{
    //创建对象
    subject *test1 = new subject_owner();
    observer *ob1 = new A_observer(test1);
    observer *ob2 = new B_observer(test1);
    //将观察者加入链表
    test1->add_observer(ob1);
    test1->add_observer(ob2);
    //添加消息
    test1->notice = "go out";
    //通知所有观察者
    test1->notify();
    return 0;
}