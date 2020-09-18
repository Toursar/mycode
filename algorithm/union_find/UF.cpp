#include "UF.h"

UF::UF(int n) : nums(n) {
    //
    parents.resize(n);
    //初始化每个节点的后续节点数目，也就是此节点后面还有多长
    size.resize(n);
    for (int i = 0; i < n; ++i) {
        //初始化父节点都为自身，每个节点之间不互相连通
        parents[i] = i;
        //每个节点的只有自身，后继总量为1
        size[i] = 1;
    }
}

UF::~UF() {}

void UF::merge(int first, int second) {
    //先找到两个节点的根节点
    int par_first = find(first);
    int par_second = find(second);
    //根据两个根节点的连通分量大小，即后继的节点数
    //将节点数小的根节点连接到大的根节点上，同时更新根节点size的值
    if (size[par_first] > size[par_second]) {
        parents[par_second] = par_first;
        size[par_first] += size[par_second];
    } else {
        parents[par_first] = par_second;
        size[par_second] += size[par_first];
    }
    //两个区域连通，连通分量减一
    --nums;
}

int UF::count() {
    return nums;
}

//判断连通只需要判断两个节点的根节点是否一样即可判断。
bool UF::connected(int first, int second) {
    int par_first = find(first);
    int par_second = find(second);
    return par_first == par_second;
}

int UF::find(int n) {
    while (parents[n] != n) {
        //下面一行是进行路径压缩，目的是让构建的并查集为一个类多路树结构
        //并且高度不超过3，这要查找的时间复杂度为 O(1)
        //实际效果就是让 n 的爷爷节点当自己的父节点，这样树高度就会减小
        //因为么每次合并连通分量都会调用find因此会不停的缩减树的高度
        //所以不会出现高度大于3的情况（merge完成可能大于3）
        parents[n] = parents[parents[n]];
        n = parents[n];
    }
    return n;
}