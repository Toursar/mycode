#include<iostream>
#include<vector>
#include<string>
#include "UF.h"
using namespace std;

bool equation_possible(vector<string> &);

int main() {
    vector<string> equation = {"a==b", "b==c", "a==c", "c!=d", "d==a"};
    cout << equation_possible(equation) << endl;
    return 0;
}

bool equation_possible(vector<string>& equation)
{
    if (equation.empty())
        return true;
    //因为题中所说，只有小写字母，因此数组大小为26足够
    UF uf(26);
    int m = equation.size();
    for (int i = 0; i < m; ++i){
        if (equation[i][1] == '=') {
            //依次判断是否为相等关系，相等关系的两头连通起来
            char a = equation[i][0];
            char b = equation[i][3];
            uf.merge((a - 'a'), (b - 'a'));
        }
    }
    for (int i = 0; i < m; ++i){
        if (equation[i][1] == '!') {
            //依次判断是否为相等关系，相等关系的两头连通起来
            char a = equation[i][0];
            char b = equation[i][3];
            if (uf.connected((a - 'a'), (b - 'a')))
                return false;
        }
    }
    return true;
}