#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    int T;
    cin >> T;
    int m, n;
    vector<vector<int>> res;
    for (int k = 0; k < T; ++k)
    {
        cin >> n >> m;
        vector<int> a1(n, 0);
        vector<vector<int>> a2(m, vector<int>(2, 0));
        for (int i = 0; i < n; ++i)
        {
            cin >> a1[i];
        }
        for (int i = 0; i < m; ++i)
        {
            cin >> a2[i][0];
            a2[i][1] = i + 1;
        }
        sort(a2.begin(), a2.end(), [](vector<int>& a, vector<int>& b)
             {
                 return a[0] < b[0];
             });
        vector<int> temp;
        for (int i = 0; i < n; ++i)
        {
            int left = 0, right = a2.size() - 1;
            while(left <= right)
            {
                int mid = left + (right - left) / 2;
                if (a1[i] < a2[mid][0])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            if (left >= a2.size())
                temp.push_back(-1);
            else
                temp.push_back(a2[left][1]);
        }
        res.push_back(temp);
    }
    for (int i = 0; i < T; ++i)
    {
        for (int j = 0; j < res[i].size(); ++j)
        {
            if (j != res[i].size() - 1)
                cout << res[i][j] << ' ';
            else
                cout << res[i][j] << endl;
        }
    }
}