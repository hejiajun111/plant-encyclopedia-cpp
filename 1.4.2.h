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

void BInsertSort(SqList &L, int &cmpNum, int &movNum)
{
    cmpNum = 0;
    movNum = 0;
    for (int i = 2; i <= L.length; i++)
    {
        // 保存待插入记录
        L.p[0] = L.p[i];
        movNum++;
        // 在已经有序的 [1, i-1] 中折半查找插入位置
        int l = 0;
        int r = i - 1;
        while (l < r)
        {
            int mid = (l + r + 1) / 2;
            // 关键字比较
            cmpNum++;
            if (L.p[0].sname < L.p[mid].sname)
                r = mid - 1;
            else
                l = mid;
        }
        // high + 1 即插入位置
        for (int j = i - 1; j >= l + 1; j--)
        {
            L.p[j + 1] = L.p[j];
            movNum++;
        }

        L.p[r + 1] = L.p[0];
        movNum++;
    }
}