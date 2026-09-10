#include <bits/stdc++.h>
using namespace std;
struct Plant
{
    // 植物信息定义
    string name;       // 植物名称
    string sname;      // 学名
    string place[100]; // 分布地
    string detail;     // 详情描述
};

typedef struct LNode
{
    Plant data;         // 结点的数据域
    struct LNode *next; // 指针域
} LNode, *LinkList;

void ReadFile(LinkList &L, string filename)
{ // 从文件中读取数据，存入链表L中
    ifstream infile(filename);
    string line;
    LinkList r = L;
    while (getline(infile, line))
    {
        LinkList p = new LNode;
        Plant temp;
        stringstream ss(line);
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
                stringstream ssplace(s);
                string place;
                int num = 0;
                while (getline(ssplace, place, '@'))
                {
                    temp.place[num] = place;
                    num++;
                }
            }
            if (flag == 3)
                temp.detail = s;
            flag++;
        }
        p->data = temp;
        p->next = r->next;
        r->next = p;
        r = p;
    }
    infile.close();
    return;
}

void DeletePlant(LinkList &L, string name, string filename)
{ // 删除指定植物信息
    LNode *p = new LNode;
    p = L;
    while (p->next)
    {
        if (p->next->data.name == name)
        {
            LNode *q = new LNode;
            q = p->next;
            p->next = q->next;
            delete (q);
        }
        else
        {
            p = p->next;
        }
    }
    p = L->next;
    fstream file;
    file.open(filename, ios::out);
    while (p)
    {
        int n = 0;
        while (p->data.place[n] != "")
        {
            n++;
        }
        file << p->data.name << "#" << p->data.sname << "#";
        for (int i = 0; i < n - 1; i++)
        {
            file << p->data.place[i] << "@";
        }
        file << p->data.place[n - 1] << "#" << p->data.detail << endl;
        p = p->next;
    }
    file.close();
}