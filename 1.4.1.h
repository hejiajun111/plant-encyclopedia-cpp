#include <bits/stdc++.h>

#define MAXSIZE 6490

using namespace std;

struct Plant
{
    string name;
    string sname;
    string place[100];
    string detail;
};

typedef struct
{
    Plant *p;
    int length;
} SqList;

void InitList(SqList &L)
{
    // p[0] 留给哨兵，所以多开一个
    L.p = new Plant[MAXSIZE + 1];
    L.length = 0;
}

void ListInsert(SqList &L, int i, Plant p)
{
    // 在第 i+1 个位置插入
    // ReadFile 中一直是尾插，所以这里实际上不会移动元素
    for (int j = L.length; j > i; j--)
        L.p[j + 1] = L.p[j];

    L.p[i + 1] = p;
    L.length++;
}

void ReadFile(SqList &L, string filename)
{
    ifstream fin(filename);
    string line;

    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        Plant t;
        string places;

        // 先清空分布地
        for (int i = 0; i < 100; i++)
            t.place[i] = "";

        stringstream ss(line);

        getline(ss, t.name, '#');
        getline(ss, t.sname, '#');
        getline(ss, places, '#');
        getline(ss, t.detail);

        stringstream ps(places);
        string place;

        int cnt = 0;

        while (getline(ps, place, '@'))
        {
            if (cnt < 100)
                t.place[cnt++] = place;
        }

        ListInsert(L, L.length, t);
    }

    fin.close();
}

void InsertSort(SqList &L, int &cmpNum, int &movNum)
{
    cmpNum = 0;
    movNum = 0;
    for (int i = 2; i <= L.length; i++)
    {
        // 先判断当前记录是否需要插入
        cmpNum++;
        if (L.p[i].sname < L.p[i - 1].sname)
        {
            // 保存待插入记录
            L.p[0] = L.p[i];
            movNum++;
            // 第一个记录直接后移
            L.p[i] = L.p[i - 1];
            movNum++;
            int j = i - 2;
            while (true)
            {
                cmpNum++;
                if (!(L.p[0].sname < L.p[j].sname))
                    break;
                L.p[j + 1] = L.p[j];
                movNum++;
                j--;
            }
            L.p[j + 1] = L.p[0];
            movNum++;
        }
    }
}