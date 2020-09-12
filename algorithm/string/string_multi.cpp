#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string string_muti(string &, string &);
string string_add(string &, string &);

int main()
{
    string str1("123");
    string str2("456");
    cout << string_muti(str1, str2) << endl;
    cout << string_add(str1, str2) << endl;
    return 0;
}
//大致想法，首先以第一个数字为基准，第二个数字的每一位与第一个数字相乘
//然后把结果相加，得到最终结果。
string string_muti(string& str1, string& str2)
{
    string res = "";
    string temp = "";
    //定义进位     第二个数字乘完以后末尾应该加几个0
    int upper = 0, bit = 0;
    int n = str2.size() - 1;
    int num1, num2;
    while(n >= 0)
    {
        //每次进行一位数字的乘法都需要对m进行初始化
        int m = str1.size() - 1;
        //根据相乘的第二位的位置，确定应该为当前计算结果加几个0
        for (int i = 0; i < bit; ++i)
        {
            temp.push_back('0');
        }
        //每次循环得到被乘数的一位，进行乘法
        num2 = n >= 0 ? (str2[n] - '0') : 0;
        while(m >= 0 || upper != 0)
        {
            //每次循环得到乘数的一位，进行乘法
            num1 = m >= 0 ? (str1[m] - '0') : 0;
            //当前乘法的结果为两个数相乘+上次乘法的进位
            int multi_res = num1 * num2 + upper;
            //当前位应该为多少
            int res = multi_res % 10;
            //当前位产生的进位应该为多少
            upper = multi_res / 10;
            temp.push_back((res + '0'));
            --m;
        }
        //得到的字符串是逆序的，需要倒过来
        reverse(temp.begin(), temp.end());
        //将当前得到的结果与之前的结果相加
        res = string_add(res, temp);
        --n;
        //bit记录右边有多少个零
        bit += 1;
        temp.clear();
    }
    return res;
}

string string_add(string& str1, string& str2)
{
    int upper = 0;
    string temp;
    int num1, num2;
    int m = str1.size() - 1;
    int n = str2.size() - 1;
    //知道两个数字的都为空，且进位为0，退出循环
    while(m >= 0 || n >= 0 || upper != 0)
    {
        //位数够，则为当前位的数字，不够为0
        num1 = m >= 0 ? (str1[m] - '0') : 0;
        num2 = n >= 0 ? (str2[n] - '0') : 0;
        //结果为两个数相加+进位
        int add_res = num1 + num2 + upper;
        int res = add_res % 10;
        upper = add_res / 10;
        temp.push_back((res + '0'));
        --m;
        --n;
    }
    //将求到的逆序字符串倒回来。
    reverse(temp.begin(), temp.end());
    return temp;
}