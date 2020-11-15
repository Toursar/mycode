#include<iostream>
#include<string>

// 使用继承的关系实现
namespace tup_inherited {
    // 类模板的声明
    template <typename... Value>
    class tuple;

    // 偏特化版本的递归出口
    template <>
    class tuple<>{};

    // 特化版本的调用，使用继承的方法实现模板的参数分离
    // 每个类都会继承自一个参数比自身少一个的类，直到没有参数
    // 声明继承关系的主要目的是要获得这些类之间内存的依赖关系：子类中包含父类的关系
    template<typename Head, typename... Tail>
    class tuple<Head, Tail...> : private tuple<Tail...> {
        typedef tuple<Tail...> inherited;
        // 将第一个参数作为自身数据保存，其他参数委托父类构造
    public:
        tuple(Head h, Tail... tail) : m_head(h), inherited(tail...) {}

        Head head() {
            return m_head;
        }

        // 返回自身，转换为inherited类型，即子类对象转换为父类，即只有tail的部分
        inherited& tail() {
            return *this;
        }
    protected:
        Head m_head;
    };
}

// 使用composition (has a)关系实现
namespace tup_composition {
    template <typename... Value>
    class tuple;

    // 同样的偏特化递归出口
    template<>
    class tuple<>{};

    // 真正执行的偏特化版本
    template<typename Head, typename... Tail>
    class tuple<Head, Tail...> {
        typedef tuple<Tail...> composition;
    public:
        tuple(Head h, Tail... tail) : m_head(h), m_tail(tail...) {}
        Head head() {
            return m_head;
        }

        composition& tail() {
            return m_tail;
        }
    private:
        composition m_tail;
        Head m_head;
    };
}

int main() {
    tup_composition::tuple<int, std::string, double> test(1,"123", 1.2);
    std::cout << test.tail().head() << std::endl;
    return 0;
}