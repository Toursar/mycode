#include<iostream>
#include<vector>

using namespace std;

vector<int> res;

void isprimer(int n)
{
    //初始假设1-n全为素数。
    vector<int> primer(n, 1);
    //每个素数的整数倍一定不是素数
    //同时素数的判断只需要前sqrt(n)即可，前后的结果一定是一样的
    for (int i = 2; i * i < n; ++i)
    {
        if (primer[i])
        {
            //为了去重，使用j = i * i，无需从2 * i开始
            for (int j = i * i; j < n; j += i)
                primer[j] = 0;
        }
    }
    for (int i = 2; i < n; ++i)
    {
        if (primer[i] == 1)
            res.push_back(i);
    }
}

int main()
{
    isprimer(20);
    for (int a : res)
        cout << a << " ";
    cout << endl;
}