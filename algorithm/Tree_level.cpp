#include <iostream>
#include<vector>
#include<queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
    ~TreeNode()
    {
        //释放root连接的所有节点
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }
};

TreeNode* maketree(int n, int num)
{
    if (n == 0)
        return nullptr;
    TreeNode *root = new TreeNode(num);
    root->left = maketree(n - 1, num + 1);
    root->right = maketree(n - 1, num + 1);
    return root;
}

void desplay(TreeNode* root)
{
    if (root == nullptr)
        return;
    queue<TreeNode *> qu;
    qu.push(root);
    while(!qu.empty())
    {
        //如果需要分层输出，可以加循环
        //int m = qu.size();
        //for (int i = 0; i < m; ++i)
        //{
            TreeNode *temp = qu.front();
            cout << temp->val << endl;
            qu.pop();
            if (temp->left != nullptr)
                qu.push(temp->left);
            if (temp->right != nullptr)
                qu.push(temp->right);
        //}
    }
}

int main() {
    TreeNode *root = maketree(3, 2);
    desplay(root);
    //只需要释放root即可，其他的节点会被root的析构函数释放。
    delete root;
    return 0;
}