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
//除去数字n的最后一位1, n & (n - 1)
void remove_last1(int n)
{
    cout << n << " 去除最后一位1后: " << (n & (n - 1)) << endl;
}

int main()
{
    cout << muti(5, 9) << endl;
    remove_last1(7);
    return 0;
}