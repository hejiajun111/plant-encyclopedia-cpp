#include <bits/stdc++.h>
#define m 6600 // 散列表的表长
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
LinkList H[m]; // 链地址法散列表的存储表示，m个单链表
void InitList()
{
    // 链表初始化
    for (int i = 0; i < m; ++i)
    {
        H[i] = new LNode;
        H[i]->next = NULL;
    }
}
int Hash(string sname)
{
    // 实现散列函数：字符串sname中各字符的下标（从0开始）的平方乘以字符对应的ASCII码值，相加后与6599取余
    int sum = 0;
    for (int i = 0; i < sname.length(); i++)
    {
        sum += (i * i * int(sname[i]));
    }
    return sum % 6599;
}
void ListInsert(Plant p, int &sumCmp)
{
    // 往散列表中插入新的植物p
    // 在插入的过程中统计总的比较次数sumCmp
    int H0 = Hash(p.sname);
    LinkList s = H[H0];
    while (s->next)
    {
        s = s->next;
        sumCmp++;
    }
    LinkList t = new LNode;
    t->data = p;
    t->next = NULL;
    s->next = t;
    sumCmp++;
}
int ReadFile(int &sumCmp, string filename)
{
    // 读取plant.txt文件，调用ListInsert函数将每条植物数据插入顺序表
    // 返回树木数据的条数
    ifstream is(filename);
    string txt;
    while (getline(is, txt))
    {
        Plant temp;
        stringstream ss(txt);
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
                stringstream sp(s);
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
        ListInsert(temp, sumCmp);
    }
    is.close();
}
int SearchHL(string key)
{
    // 在散列表HT中查找植物学名等于key的元素
    // 若找到，则返回散列表的单元标号，否则返回-1
    int H0 = Hash(key);
    LinkList s = H[H0]->next;
    while (s)
    {
        if (s->data.sname == key)
            return H0;
        s = s->next;
    }
    return -1;
}
double ASL_HL(int sumCmp, int count)
{
    // 返回基于链地址法的散列查找的ASL
    return (double)sumCmp / 6490;
}