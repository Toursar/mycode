#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<stack>
#include<map>

using namespace std;

int main()
{
    int n;
    while(cin >> n)
    {
        map<int, int> mp;
        stack<int> st;
        for (int i = 0; i < n; ++i)
        {
            int temp;
            cin >> temp;
            st.push(temp);
            mp[temp]++;
        }
        for (int i = 0; i < st.size(); ++i)
        {
            int temp = st.top();
            if (mp[temp] > 0)
            {
                cout << temp << endl;
                mp[temp]--;
            }
            st.pop();
        }
        mp.clear();
    }
    return 0;
}