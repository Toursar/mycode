#include<iostream>
#include<string>
//字符串匹配RK算法，利用哈希值计算
class RK {
public:
    int compare(std::string& str, std::string& pattern) {
        //主字符串的长度
        int m = str.size();
        //模式串长度
        int n = pattern.size();
        int pat_hash = hash_func(pattern);
        //首先计算第一个等长的主字符串的模式
        std::string temp = str.substr(0, n);
        int str_hash = hash_func(temp);
        for (int i = 0; i <= m - n; ++i) {
            //如果hash值相等而且字符串也相等，那么即可返回
            if (pat_hash == str_hash && is_equal(str, pattern, i)) {
                return i;
            }
            //只要当前截取主字符串并非最后一个，那么就计算nexthash值
            if (i < m - n)
                next_hash(str, str_hash, i, n);
        }
        return -1;
    }
private:
    //计算字符串hash值
    int hash_func(std::string& str) {
        int res = 0;
        for (char a : str) {
            res += a - 'a' + 1;
        }
        return res;
    }
    //判断两个字符串是否相等
    bool is_equal(std::string &str1, std::string& str2, int start) {
        int m = str1.size();
        int n = str2.size();
        std::string temp = str1.substr(start, n);
        for (int i = 0; i < n; ++i) {
            if (temp[i] != str2[i])
                return false;
        }
        return true;
    }
    //计算下一个的hash值
    void next_hash(std::string& str, int& str_hash, int start, int n) {
        str_hash -= (str[start] - 'a' + 1);
        str_hash += (str[start + n] - 'a' + 1);
    }
};
//BM算法
class BM {
public:
    int BM_compare(std::string& str, std::string& pattern) {
        int m = str.size();
        int n = pattern.size();
        //定义模式串的开始位置
        int start = 0;
        while (start <= m - n) {
            int i;
            //寻找坏字符的位置
            for (i = n - 1; i >= 0; --i) {
                if (str[i + start] != pattern[i])
                    break;
            }
            //如果坏字符位置为-1那么就是匹配成功
            if (i < 0)
                return start;
            //找到模式串中与坏字符相同的字符位置
            int index = find_char(pattern, str[i + start], i);
            //主字符串的起始位置进行相应的改变
            start += index == -1 ? i + 1 : i - index;
        }
        return -1;
    }
private:
    //寻找模式串中坏字符存在的位置
    int find_char(std::string& pattern, char bad_char, int right) {
        for (int i = right - 1; i >= 0; --i) {
            if (pattern[i] == bad_char)
                return i;
        }
        return -1;
    }
};

int main()
{
    BM bm;
    RK rk;
    std::string str = "aabcabcd";
    std::string target = "abc";
    std::cout << bm.BM_compare(str, target) << std::endl;
    std::cout << rk.compare(str, target) << std::endl;
    return 0;
}