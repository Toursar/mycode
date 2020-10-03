#include<vector>
#include<unordered_map>

 //使用map定义的前缀树
 //优点：节省空间，只创建存在的字符节点
 //但是访问效率不如数组定义的前缀树
class Trie {
private:
    //首先定义一个内部类，声明每个前缀树的节点
    struct TrieNode {
        //每个字符都会对应一个新的前缀树
        std::unordered_map<char, TrieNode*> child;
        //用来标识，是否存在以此字符为结尾的字符串
        bool has = false;
    };
    TrieNode* root;
public:
    Trie() {
        //初始化最开始的根节点，根节点一般不会保存字符
        root = new TrieNode();
    }
    //在前缀树中插入字符串
    void insert(std::string word) {
        //从根节点开始
        TrieNode* cur = root;
        for (int i = 0; i < word.size(); ++i) {
            //如果该字符不存在，那么创建该字符的节点
            if (cur->child.count(word[i]) <= 0)
                cur->child.insert({word[i], new TrieNode()});
            //继续下一个字符
            cur = cur->child[word[i]];
        }
        //直到遍历完节点，将结尾的标识符定位true
        cur->has = true;
    }
    //在前缀树中查找某个字符串
    bool search(std::string word) {
        TrieNode* cur = root;
        //遍历方式与插入类似，遍历过程中对每个字符判定是否存在，不存在就说明前缀树中没有该字符串，直接返回
        for (int i = 0; i < word.size(); ++i) {
            if (cur->child.count(word[i]) <= 0)
                return false;
            cur = cur->child[word[i]];
        }
        //最后根据标识符确定是否存在此字符串
        if (!cur->has)
            return false;
        return true;
    }
    //判断前缀树是否存在此前缀
    bool startsWith(std::string prefix) {
        TrieNode* cur = root;
        //判断方式与search几乎一致
        for (int i = 0; i < prefix.size(); ++i) {
            if (cur->child.count(prefix[i]) <= 0)
                return false;
            cur = cur->child[prefix[i]];
        }
        return true;
    }
};

//使用数组方式储存，这种方式适合字符的范围确定，比如只出现小写字母
//优点：访问任何一个节点都非常迅速
//缺点：需要较多额外空间，即使这些空间可能根本用不上
//插入，查找和寻找前缀的操作方式与哈希映射几乎一致

// class Trie {
// private:
//     std::vector<Trie*> child;
//     bool has;
// public:
//     Trie() {
//         child.resize(26, nullptr);
//         has = false;
//     }
    
//     void insert(std::string word) {
//         Trie* cur = this;
//         for (int i = 0; i < word.size(); ++i) {
//             if (cur->child[word[i] - 'a'] == nullptr)
//                 cur->child[word[i] - 'a'] = new Trie();
//             cur = cur->child[word[i] - 'a'];
//         }
//         cur->has = true;
//     }
    
//     bool search(std::string word) {
//         Trie* cur = this;
//         for (int i = 0; i < word.size(); ++i) {
//             if (cur->child[word[i] - 'a'] == nullptr)
//                 return false;
//             cur = cur->child[word[i] - 'a'];
//         }
//         if (!cur->has)
//             return false;
//         return true;
//     }
    
//     bool startsWith(std::string prefix) {
//         Trie* cur = this;
//         for (int i = 0; i < prefix.size(); ++i) {
//             if (cur->child[prefix[i] - 'a'] == nullptr)
//                 return false;
//             cur = cur->child[prefix[i] - 'a'];
//         }
//         return true;
//     }
// };