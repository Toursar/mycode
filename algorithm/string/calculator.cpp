#include <iostream>
#include<stack>

using namespace std;

int calculator(string &);
bool is_num(char);

int main() {
    string a("3 * (4 - 2) - (7 / 3)");
    cout << calculator(a) << endl;
    return 0;
}

int calculator(string& str) {
    if (str.empty())
        return 0;
    //第一个数字没有符号，我们默认为+号
    char sign = '+';
    int num = 0;
    //使用栈实现计算器
    stack<int> st;
    while (str.size() > 0) {
        //为了方便处理括号的递归调用，我们每次选择string的第一个字符后，都会从原string中删除该字符
        char c = str.front();
        str.erase(0, 1);
        //首先提取一整个数字
        if (is_num(c))
            num = num * 10 + (c - '0');
        //如果遇到括号，那么进行递归，优先运算出括号内的结果
        if (c == '(') {
            num = calculator(str);
        }
        //如果不是数字，且不是空格，那么就是符号了
        //同时应该注意最后一个数字后面没有符号了，也需要计算
        if ((!is_num(c) && c != ' ') || str.size() == 0) {
            //每次计算我们都是与当前数字的前一个符合进行组合
            //由于算式没有第一个符合，因此第一个符号我们默认为+
            switch (sign) {
                int temp;
                //如果为+-号，直接与前面的符号运算以后入栈
                case '+':
                    st.push(num);
                    break;
                case '-':
                    st.push(-1 * num);
                    break;
                //如果为乘除，则将栈顶的元素与当前数字运算再入栈
                //相当于优先计算乘除法，因为上面的加减并没有计算，而是直接入栈了
                case '*':
                    temp = st.top();
                    st.pop();
                    st.push(temp * num);
                    break;
                case '/':
                    temp = st.top();
                    st.pop();
                    st.push(temp / num);
                    break;
            }
            //更新符号，为下一次计算准备
            sign = c;
            //每次计算完成，需要把num置为零
            num = 0;
        }
        //递归的出口，递归结束后可以返回当前递归函数栈内的元素和
        //相当于优先计算了小括号
        if (c == ')')
            break;
    }
    //将栈内的所有元素相加，由于-号入栈时已经转换为负数
    //所以直接进行累加即可
    int res = 0;
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    return res;
}
//判断字符是否为一个数字
bool is_num(char a) {
    return ((a - '0') >= 0 && (a - '0') < 10) ? 1 : 0;
}