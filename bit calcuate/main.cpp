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
}

int main()
{
    cout << muti(5, 9) << endl;
    and_operator(6);
    XOR_operator(12);
    return 0;
}