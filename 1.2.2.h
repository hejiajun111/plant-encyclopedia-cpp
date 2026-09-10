#include <bits/stdc++.h>
using namespace std;
struct Plant
{                      // 植物信息定义
    string name;       // 名称
    string sname;      // 学名
    string place[100]; // 分布地
    string detail;     // 详情描述
};
typedef struct LNode
{ // 单链表
    Plant data;
    struct LNode *next;
} LNode, *LinkList;
void InitList(LinkList &L)
{
    // 链表初始化
    L = new LNode;
    L->next = NULL;
}
void ListInsert(LinkList &L, int i, Plant temp)
{ // 在带头结点的单链表L中第i个位置插入新的植物temp
    LinkList p = L;
    int j = 0;
    while (p && (j < i - 1)) // 查找第i-1个结点，p指向该结点
    {
        p = p->next;
        ++j;
    }
    LNode *s = new LNode; // 生成新结点*s
    s->data = temp;       // 将结点*s的数据域置为temp
    s->next = p->next;    // 将结点*s的指针域指向结点ai
    p->next = s;          // 将结点*p的指针域指向结点*s
}
int ReadFile(LinkList &L, string filename)
{
    // 读取plant.txt文件，调用ListInsert函数将每条植物数据插入链表
    // 返回树木数据的条数
    ifstream In(filename); // 打开文件
    string txt;
    int cnt = 0;
    while (getline(In, txt))
    {                          // 读取一行植物数据
        Plant temp;            // 暂存每一行植物数据
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
        cnt++;
        ListInsert(L, cnt, temp); // 往顺序表中插入该行植物数据
    }
    return cnt;
}
LNode *LocateElem(LinkList L, string key)
{                                     // 在带头结点的单链表L中查找植物学名为key的元素
    LinkList p = L->next;             // 初始化，p指向首元结点
    while (p && p->data.sname != key) // 顺链域向后扫描
        p = p->next;
    return p; // 查找成功返回学名为key的结点地址p，查找失败p为NULL
}
double ASL_LinkList(LinkList L, int count)
{ // 返回基于链表的顺序查找的ASL，count为链表L中的结点数
    return (count + 1) / 2.0;
}