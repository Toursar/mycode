#pragma once
#include<vector>

class UF
{
private:
    //保存每个节点的父节点。
    std::vector<int> parents;
    //连接此节点的后续节点数目，包括自己
    std::vector<int> size;
    //记录连通节点数量
    int nums;
public:
    //构造一个并查集，初始化其中的数组变量。
    UF(int n);
    ~UF();
    //返回并查集中有多少连通分量
    int count();
    //将两个分量连通起来
    void merge(int, int);
    //判断两个分量是否连通
    bool connected(int, int);
    //返回该分量的根
    int find(int);
};