#include<iostream>

using namespace std;
//声明为友元的原因：
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
	friend ostream& operator<<(ostream& os, Test& temp)
	{
		os << "a = " << temp.m_a << " b = "<< temp.m_b << endl;
		os << "area = " << temp.area * temp.m_b << endl;
		return os;
	}
};

int main()
{
	Test test(2, 3);
	cout << test << endl;
	return 0;
}