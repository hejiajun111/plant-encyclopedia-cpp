#include <bits/stdc++.h>
using namespace std;
struct Plant
{                      // 植物信息定义
    string name;       // 名称
    string sname;      // 学名
    string place[100]; // 分布地
    string detail;     // 详情描述
};
typedef struct BSTNode
{ // 二叉排序树
    Plant data;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;
void InitBSTree(BSTree &T)
{
    // 二叉排序树初始化
    T = NULL;
}
void BSTreeInsert(BSTree &T, Plant temp)
{
    if (T == NULL)
    {
        T = new BSTNode;
        T->data = temp;
        T->lchild = NULL;
        T->rchild = NULL;
    }
    else if (temp.sname < T->data.sname)
    {
        BSTreeInsert(T->lchild, temp);
    }
    else if (temp.sname > T->data.sname)
    {
        BSTreeInsert(T->rchild, temp);
    }
}
int ReadFile(BSTree &T, string filename)
{
    // 读取plant.txt文件，调用BSTreeInsert函数将每条植物数据插入二叉排序树
    // 返回树木数据的条数
    ifstream infile(filename);
    string txt;
    int count = 0;
    while (getline(infile, txt))
    {                              // 读取一行植物数据
        Plant temp;                // 暂存每一行植物数据
        stringstream ss(txt); // 分割每一行植物数据的4个数据项
        string s;
        int flag = 0;
        while (getline(ss, s, '#'))
        {
            if (flag == 0)
                temp.name = s;
            if (flag == 1)
                temp.sname = s;
            if (flag == 2)
            {
                stringstream sp(s); // 保存每一行植物数据的分布地
                string place;
                int num = 0;
                while (getline(sp, place, '@'))
                {
                    temp.place[num] = place;
                    num++;
                }
            }
            if (flag == 3)
                temp.detail = s;
            flag++;
        }
        count++;
        BSTreeInsert(T, temp); // 往二叉排序树中插入该行植物数据
    }
    return count;
}
void InOrderTraverse(BSTree T)
{
    // 中序遍历二叉树T的递归算法
    if (T)
    {
        InOrderTraverse(T->lchild);
        cout << T->data.sname << endl;
        InOrderTraverse(T->rchild);
    }
}
BSTree SearchBST(BSTree T, string key)
{ // 在根指针T所指二叉排序树中递归地查找植物学名等于key的数据元素
  // 若查找成功，则返回指向该数据元素结点的指针，否则返回空指针
    if ((!T) || key == T->data.sname)
        return T; // 查找结束
    else if (key < T->data.sname)
        return SearchBST(T->lchild, key);
    else
        return SearchBST(T->rchild, key);
}

int GetSumCmp(BSTree T, int sumCmp)
{ // 统计查找成功时的总比较次数
    if (T)
    {
        sumCmp++;
        int temp = sumCmp;
        if (T->lchild)
            sumCmp += GetSumCmp(T->lchild, temp);
        if (T->rchild)
            sumCmp += GetSumCmp(T->rchild, temp);
    }
    return sumCmp;
}
double ASL_BSTree(BSTree T, int count)
{ // 返回基于二叉排序树查找的ASL，count为二叉树T中的结点数
    int sumCmp = GetSumCmp(T, 0);
    return double(sumCmp) / count;
}