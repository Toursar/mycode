#include<iostream>
#include<vector>
#include<algorithm>

// 新增的利用{}进行初始化的方式，编译器遇到{}的形式，就会将其中的元素打包创建一个initializer_list对象
// 可以利用initializer_list来创建对象，C++11中的各个容器也都增加了这样的初始化方式
// initializer_list对象底层为array容器。利用中括号可以创建不定长的初始化参数（参数类型需要相同）。
class print {
public:
    print(int a, int b) {
        std::cout << "print(int, int) " << a << " " << b << std::endl;
    }
    print(std::initializer_list<int> initlist) {
        std::cout << "print(initializer_list) ";
        for (int a : initlist) {
            std::cout << a << " ";
        }
        std::cout << std::endl;
    }
};

void print_vector() {
    //vector中使用的initializer_list
    std::vector<int> a{1, 2, 3, 4};

    std::vector<int> b;
    b = {1, 2, 3, 4};

    std::vector<int> c({2, 3, 4});

    c.insert(c.begin() + 1, {3, 3, 3});
    for (int num : c) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// max和min方法现在也可以利用这个方法进行多个值的比较，不再局限于两两比较了
void max_min() {
    int biggest = std::max({2.3, 3.5, 4.5, 1.2, 3.9});
    int smallest = std::min({2.3, 3.5, 4.5, 1.2, 3.9});
    std::cout << "max is " << biggest << ". min is " << smallest << std::endl;
}

int main() {
    print test1(1, 4);
    print test2{1, 2, 3};
    print test3 {1, 2, 3, 4};
    print_vector();
    max_min();
    return 0;
}