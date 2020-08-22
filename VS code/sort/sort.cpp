#include<iostream>
#include<vector>
#include<cmath>
#include<string.h>
#include<ctime>

using namespace std;
namespace heap
{
    class heap_sort{
    private:
        
    public: 
        vector<int> res; 
        heap_sort() { res.push_back(0); }
        ~heap_sort() {}
        void insert(int num)
        {
            res.push_back(num);
            swim(res.size() - 1);
        }
        void swim(int index)
        {
            while (index > 1 && res[index] < res[parent(index)])
            {
                swap(index, parent(index));
                index = parent(index);
            }
        }
        void sink(int index)
        {
            int m = res.size();
            while(left(index) < m)
            {
                int min = left(index);
                if (right(index) < m && res[right(index)] < res[min])
                    min = right(index);
                if (res[index] < res[min]) break;
                swap(min, index);
                index = min;
            }
        }
        void remove()
        {
            int m = res.size();
            swap(m - 1, 1);
            res.pop_back();
            sink(1);
        }
        int min_num() const
        {
            return res[1];
        }
        void swap(int i, int j)
        {
            int temp = res[j];
            res[j] = res[i];
            res[i] = temp;
        }
        int parent(int root) { return root / 2; }
        int left(int root) { return root * 2; }
        int right(int root) { return root * 2 + 1; }
    };
}

namespace quick
{
    class quick_sort
    {
    private:
        void sort_q(vector<int>& res, int left, int right);
    public:
        quick_sort(){};
        ~quick_sort(){};
        void sort1(vector<int>& arr);
    };

    void quick_sort::sort1(vector<int>& res)
    {
        int m = res.size();
        sort_q(res, 0, m - 1);
    }
    void quick_sort::sort_q(vector<int>& res, int m, int n)
    {
        if (m >= n)
            return;
        int mid = res[m];
        int left = m, right = n;
        while(left < right)
        {
            while (left < right && res[right] >= mid)
                --right;
            res[left] = res[right];
            //此处不应该再写left++项，应该交由下一个while循环判断
            //++left;  //防止只有两项时无论大小都发生交换的问题。
            while(left < right && res[left] < mid)
                ++left;
            res[right] = res[left];
            //同理此处不应该再写right++项
            //++right;
        }
        res[left] = mid;
        sort_q(res, m, left - 1);
        sort_q(res, left + 1, n);
    }
}

namespace merge
{
    class merge_sort
    {
    private:
        vector<int> temp;
        void sort_m(vector<int> &res, int m, int n);
        void sort_2(vector<int> &res, int m, int n);
    public:
        merge_sort(vector<int> &res) { temp = res; }
        ~merge_sort(){};
        vector<int> sort1(vector<int> &res);
    };

    vector<int> merge_sort::sort1(vector<int>& res)
    {
        sort_2(res, 0, res.size() - 1);
        return temp;
    }

    void merge_sort::sort_2(vector<int> &res, int m, int n)
    {
        if (m < n)
        {
            int mid = m + (n - m) / 2;
            sort_2(res, m, mid);
            sort_2(res, mid + 1, n);
            sort_m(res, m, n);
            res = temp;
        }
    }

    void merge_sort::sort_m(vector<int>& res, int m, int n)
    {
        if (m > n)
            return;
        int mid = m + (n - m) / 2;
        int left1 = m, right1 = mid;
        int left2 = mid + 1, right2 = n;
        int k = m;
        while(left1 <= right1 && left2 <= right2)
        {
            if (res[left1] < res[left2])
            {
                temp[k++] = res[left1];
                ++left1;
            }
            else
            {
                temp[k++] = res[left2];
                ++left2;
            }
        }
        while(left1 <= right1)
        {
            temp[k++] = res[left1];
            ++left1;
        }
        while(left2 <= right2)
        {
            temp[k++] = res[left2];
            ++left2;
        }
    }
}
//基数排序
namespace radix
{
    class radix_sort
    {
    private:
        vector<int> save;
    public:
        radix_sort(){};
        ~radix_sort(){};
        int find_max(vector<int> &data);
        void sort1(vector<int> &data);
    };

    void radix_sort::sort1(vector<int> &data)
    {
        //最大数的位数
        int m_bit = find_max(data);
        int m = data.size();
        int count[10] = {0};
        //当前比较的位数
        int temp_bit = 1;
        save.resize(m, 0);
        for (int i = 0; i < m_bit; ++i)
        {
            for (int i = 0; i < m; ++i)
            {
                //本步计算0-9上的数字个数
                count[(data[i] / temp_bit) % 10]++;
            }
            //这一步到下一个循环结束,将count转换为当前末尾为i的数字应该从save的那个位置开始保存
            int sum = count[0];
            count[0] = 0;
            for (int i = 1; i <= 9; ++i)
            {
                int temp = count[i];
                count[i] = sum;
                sum += temp;
            }
            //这里是关键步骤，将data数据依次写到save中，位置由前面的count给出
            //每写一位，将当前位置的count+1，以便下一个相同末位数的写入
            for (int i = 0; i < m; ++i)
            {
                int temp = (data[i] / temp_bit) % 10;
                save[count[temp]] = data[i];
                count[temp]++;
            }
            temp_bit *= 10;
            data = save;
            //注意将count初始化为0
            memset(count, 0, sizeof(count));
        }
    }

    int radix_sort::find_max(vector<int>& res)
    {
        int count = 1;
        int m = res.size();
        int biggest = INT_MIN;
        for (int i = 0; i < m; ++i)
        {
            biggest = max(res[i], biggest);
        }
        while(biggest >= 10)
        {
            ++count;
            biggest /= 10;
        }
        return count;
    }
}
//using namespace heap;
//using namespace quick;
//using namespace merge;
using namespace radix;
int main()
{
    srand(time(nullptr));
    vector<int> a(20, 0);
    for (auto iter = a.begin(); iter != a.end(); ++iter)
    {
        *iter = rand()%200;
    }
    radix_sort sorta;
    sorta.sort1(a);
    for (int i = 0; i < a.size(); ++i)
        cout << a[i] << endl;
}