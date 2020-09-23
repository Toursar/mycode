#include<iostream>
#include<vector>
#include<cmath>
#include<string.h>
#include<ctime>
#include<queue>
#include<algorithm>
#include<climits>

using namespace std;
//堆排序（不稳定）
namespace heap
{
    class heap_sort{
    private:
        
    public: 
        vector<int> res; 
        heap_sort() { res.push_back(0); }
        ~heap_sort() {}
        //将要插入的数字放在数组末端，然后使用swim将插入的数字上浮到正确位置
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
        //删除操作，将顶端的待删除数字与尾端的数字交换，然后删除尾端
        //将顶端的被交换数字进行sink操作，下沉到正确位置
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
        //当前节点的父节点，左右子节点的下标关系
        int parent(int root) { return root / 2; }
        int left(int root) { return root * 2; }
        int right(int root) { return root * 2 + 1; }
    };
}
//快速排序（不稳定）
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
        //递归的出口
        if (m >= n)
            return;
        //取数组第一个数字为当前排序进行比较的标准数字
        int mid = res[m];
        int left = m, right = n;
        while(left < right)
        {
            //数组最右边比标准大的数字，无需交换，跳过
            while (left < right && res[right] >= mid)
                --right;
            //交换右边比标准数字小的到左端
            res[left] = res[right];
            //此处不应该再写left++项，应该交由下一个while循环判断
            //++left;  //防止只有两项时无论大小都发生交换的问题。
            //数组左端比标准数字小的无需交换，跳过
            while(left < right && res[left] < mid)
                ++left;
            //交换左端，比标准数字大的到右端。
            res[right] = res[left];
            //同理此处不应该再写right++项
            //++right;
        }
        //一趟排序之后，当left = right时的位置即为标准数字的位置
        //一次遍历的结果是，标准位置左端的数字都比标准数字小，右端都比标准数字大
        res[left] = mid;
        //一次递归，左右子数组，即可完成排序
        sort_q(res, m, left - 1);
        sort_q(res, left + 1, n);
    }
}
//归并排序（稳定）
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
            //将数组打散成只含一个数的小数组
            sort_2(res, m, mid);
            sort_2(res, mid + 1, n);
            //将两个小数组合并为一个有序的大数组
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
        //循环会将两个数组依次放入一个临时数组
        //直到两个数组中有一个数组元素全部放完
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
        //把没放完的另一个数组直接全部放入临时数组，构建出一个更大的有序数组
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
//基数排序（稳定）
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
            //这一步到下一个循环结束,将count转换为当前末尾为i的数字应该从save的哪个位置开始保存
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
//插入排序（稳定），希尔排序（不稳定）
namespace shell_sort
{
    class shell
    {
    public:
        void insert_sort(vector<int>&, int, int);
        void shell_sort1(vector<int>&);
        void swap(int &, int &);
    };
    //插入排序
    void shell::insert_sort(vector<int>& data, int start = 0, int gap = 1)
    {
        if (data.empty())
        {
            cout << "array is empty!" << endl;
            return;
        }
        int m = data.size();
        for (int i = start; i < m; i += gap)
        {
            for (int j = i; j > start; j -= gap)
            {
                //分别与前面的数字比较，若是小，则交换
                if (data[j] < data[j - gap])
                    swap(data[j], data[j - gap]);
                else
                    break;
            }
        }
    }

    void shell::shell_sort1(vector<int>& data)
    {
        int m = data.size();
        //首先定义gap为数组一半，之后每次分段排序后gap减半
        int gap = m / 2;
        while (gap > 0)
        {
            for (int i = 0; i < gap; ++i)
            {
                this->insert_sort(data, i, gap);
            }
            gap /= 2;
        }
    }

    void shell::swap(int &a, int &b)
    {
        int temp = b;
        b = a;
        a = temp;
    }
}
//计数排序
namespace count
{
    class count_sort
    {
    public:
        void count_sort1(vector<int>&);
    };

    void count_sort::count_sort1(vector<int>& data)
    {
        //找到数据中最大的值，构建最大值大小的数组
        //以数组中的值为新数组的下标进行储存
        //储存完成后，按照下标顺序遍历新的数组即可得到排序结果
        int max_num = INT_MIN;
        for (int num : data)
        {
            max_num = max(max_num, num);
        }
        //注意数组的大小为max_num + 1。
        vector<queue<int>> res(max_num + 1, queue<int>());
        for (int num : data)
        {
            res[num].push(num);
        }
        int data_num = 0;
        //将新数组中有值的队列一次弹出
        //使用队列的原因是可以保证排序的稳定性
        for (int i = 0; i < res.size(); ++i)
        {
            while(!res[i].empty())
            {
                data[data_num++] = res[i].front();
                res[i].pop();
            }
        }
    }
}

//区间调度算法
namespace sort_algorithm
{
    void main_test()
    {
        //将区间以区间的末尾进行排序
        vector<vector<int>> res = {{1, 4}, {0, 1}, {1, 3}, {1, 2}, {2, 4}, {3, 5}, {4, 5}};
        sort(res.begin(), res.end(), [](const vector<int> &a, const vector<int> &b) -> bool {
            return a[1] < b[1];
        });
        vector<vector<int>> temp;
        int lowest = res[0][0];
        int count = 0;
        for (auto res1 : res)
        {
            //判断后面的区间头是否与前一个的区间为相交，相交则不能同时完成
            if (res1[0] >= lowest)
            {
                lowest = res1[1];
                continue;
            }
            ++count;
            temp.push_back(res1);
        }
        cout << count << " need to be deleted " << endl;
        for (int i = 0; i < temp.size(); ++i)
        {
            cout << '{' << temp[i][0] << ',' << temp[i][1] << '}' << endl;
        }
    }
}


int main()
{
    srand(time(nullptr));
    vector<int> a(20, 0);
    for (auto iter = a.begin(); iter != a.end(); ++iter)
    {
        *iter = rand()%200;
    }
    count::count_sort test1;
    test1.count_sort1(a);
    for (int i = 0; i < a.size(); ++i)
        cout << a[i] << endl;
}