#include <iostream>
#include<vector>

using namespace std;

int main() {
    vector<int> array = {1, 2, 3, 3 ,4};
    cout << find(array, 3) << endl;
    return 0;
}

int find(vector<int>& array, int target)
{
    int m = array.size();
    if (target < array[0] || target > array[m - 1]) return -1;
    int left = 0, right = m - 1;
    while(left < right)
    {
        int mid = left + (right - left) / 2;
        if (array[mid] > target)
        {
            right = mid;
        }
        else if (array[mid] == target)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    return left;
}