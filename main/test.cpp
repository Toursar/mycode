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
    delete root;
    return 0;
}