#include <iostream>
#include <vector>

using namespace std;
/*******声明为友元的原因：
 * 1. 如果声明为成员函数，那么应该传入一个参数ostream&，另一个为this
 * 这会导致，调用重载方法是出现 test << cout;的写法，不符合常规写法
 * 2. 重载<<会使用类的私有成员，因此需要声明为友元，而由于我们在重载过程中
 * 一直把ostream作为整体，不需要访问它的私有成员。
 * *************/
class Test
{
private:
	int m_a;
	int m_b;
	int area;
public:
	Test(int a = 0, int b = 0) : m_a(a), m_b(b){
		area = a * b;
	}
	//返回值为ostream&目的是可以是<<有传递性，如cout << "test is " << test << endl;这种写法
	friend ostream& operator<<(ostream& os, Test& temp)
	{
		os << "a = " << temp.m_a << " b = "<< temp.m_b << endl;
		os << "area = " << temp.area * temp.m_b << endl;
		return os;
	}
};

// 继承标准库中的vector类，然后添加一个<<的运算符重载，实现对vector自定义运算符
template<typename T>
class Mvector : public vector<T> {
public:
    Mvector() : vector<T>(){}
    Mvector(vector<T>& num) : vector<T>(num) {}
    Mvector<T>& operator<<(T num) {
        this->push_back(num);
        return *this;
    }
};

//利用composition的方式组合vector，并添加<<操作符的重载
template<typename T>
class Qvector {
public:
    Qvector() {}
    Qvector& operator<<(T num) {
        a.push_back(num);
        return *this;
    }
private:
    vector<T> a;
};

int main()
{
	Test test(2, 3);
	cout << test << endl;
	Qvector<int> num1;
	num1 << 1 << 2 << 3;
	Mvector<int> num2;
	num2 << 1 << 2 << 3;
	return 0;
}