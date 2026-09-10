#include "iostream"
#include <bits/stdc++.h>
#include <string>
#include <stdlib.h>
using namespace std;
#define MAXLEN 5000 // 串的最大长度
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
{
    ifstream fin(filename);
    string line, places;
    auto tail = L;

    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        auto p = new LNode{};
        stringstream ss(line);
        getline(ss, p->data.name, '#');
        getline(ss, p->data.sname, '#');
        getline(ss, places, '#');
        getline(ss, p->data.detail);
        tail = tail->next = p;
    }
}

void SearchInfo(LinkList L, string keyword)
{
    int m = keyword.size();
    if (!m)
        return;
    vector<int> pi(m);

    for (int i = 1, j = 0; i < m; ++i)
    {
        while (j && keyword[i] != keyword[j])
            j = pi[j - 1];
        if (keyword[i] == keyword[j])
            ++j;
        pi[i] = j;
    }
    
    for (auto p = L->next; p; p = p->next)
    {
        int j = 0;
        for (char c : p->data.detail)
        {
            while (j && c != keyword[j])
                j = pi[j - 1];
            if (c == keyword[j])
                ++j;
            if (j == m)
            {
                cout << p->data.name << '\n';
                break;
            }
        }
    }
}