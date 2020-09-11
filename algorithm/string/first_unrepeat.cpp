#include<iostream>
#include<vector>
#include<string>

using namespace std;
//找到一个字符串中第一个不重复的字符

char find_first(string &);

int main()
{
    string test("asa1f~!f!1s");
    cout << find_first(test);
    return 0;
}

char find_first(string& str)
{
    if (str.empty())
        return ' ';
    vector<int> memo(256, 0);
    for (int i = 0; i < str.size(); ++i)
    {
        memo[static_cast<int>(str[i])]++;
    }
    for (int i = 0; i < str.size(); ++i)
    {
        if (memo[static_cast<int>(str[i])] == 1)
        {
            return str[i];
        }
    }
    return ' ';
}