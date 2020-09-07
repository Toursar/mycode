#include<iostream>

using namespace std;

//使用加法和位运算进行乘法计算
//1. 开始j的二进制末尾为1代表i * j = i * (j - 1) + i
//2. 后面开始j就是偶数了，此时对j右移一位代表，j/2，同理左移i，代表i * 2，此时乘积应该相同
//3. 继续进行步骤1的操作，直到j为0结束
int muti(int i, int j)
{
    int res = 0;
    while(j > 0)
    {
        if (j & 1 == 1)
            res += i;
        i <<= 1;
        j >>= 1;
    }
    return res;
}
//与算符
void and_operator(int n)
{
    //除去数字n的最后一位1, n & (n - 1)
    cout << n << " 去除最后一位1后: " << (n & (n - 1)) << endl;
    //n & (-n)得到最后一位1
    cout << n << " 最后一位1是: " << (n & (-n)) << endl;
}
//异或操作,异或操作满足交换律和结合律
//利用异或的这些性质，可以用来查找一组数据中未重复数据
//A ^ B ^ B = A
void XOR_operator(int n)
{
    //任何数与0异或不变，与自己异或为0
    cout << "n ^ n = " << (n ^ n) << endl;
    cout << "n ^ 0 = " << (n ^ 0) << endl;
    //用于判断两数字是否异号
    cout << "-1 ^ 5 < 0 ? " << (((-1) ^ (5)) < 0) << endl;
    cout << "-1 ^ -5 < 0 ? " << (((-1) ^ (-5)) < 0) << endl;
    cout << "1 ^ 5 < 0 ? " << ((1 ^ 5) < 0) << endl;
}
//利用位运算可以进行大小写的转换
void Letter()
{
    //或' '可以转小写 ' 'ASCII码为00100000，大写 A ASCII码为 01000001, 大写 a ASCII码为 01100001
    cout << static_cast<char>(('A' | ' ')) << ' ' << static_cast<char>(('a' | ' ')) << endl;
    //与'_'可以转大写 '_'ASCII码为01011111，大写 A ASCII码为 01000001, 大写 a ASCII码为 01100001
    cout << static_cast<char>(('A' & '_')) << ' ' << static_cast<char>(('a' & '_')) << endl;
    //异或' '可以转大写 ' 'ASCII码为00100000，大写 A ASCII码为 01000001, 大写 a ASCII码为 01100001
    cout << static_cast<char>(('A' ^ ' ')) << ' ' << static_cast<char>(('a' ^ ' ')) << endl;
}

int main()
{
    XOR_operator(2);
    return 0;
}