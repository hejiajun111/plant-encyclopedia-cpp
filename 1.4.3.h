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
    // p[0] 作为哨兵，实际数据从 p[1] 开始
    L.p = new Plant[MAXSIZE + 1];
    L.length = 0;
}

void ListInsert(SqList &L, int i, Plant p)
{
    // 在第 i+1 个位置插入
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

void SelectSort(SqList &L, int &cmpNum, int &movNum)
{
    cmpNum = 0;
    movNum = 0;
    for (int i = 1; i < L.length; i++)
    {
        int k = i;
        for (int j = i + 1; j <= L.length; j++)
        {
            cmpNum++;
            if (L.p[j].sname < L.p[k].sname)
                k = j;
        }
        if (k != i)
        {
            Plant temp = L.p[i];
            L.p[i] = L.p[k];
            L.p[k] = temp;
            movNum += 3;
        }
    }
}