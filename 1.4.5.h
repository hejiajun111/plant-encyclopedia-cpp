#include <bits/stdc++.h>
#define MAXSIZE 6490
using namespace std;
struct Plant
{                      // 植物信息定义
    string name;       // 名称
    string sname;      // 学名
    string place[100]; // 分布地
    string detail;     // 详情描述
};
typedef struct
{ // 顺序表
    Plant *p;
    int length; // 顺序表长度
} SqList;
int cmpNum = 0; // 比较次数
int movNum = 0;

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

int Partition(SqList &L, int low, int high)
{
    // 第一个记录作为枢轴
    L.p[0] = L.p[low];
    movNum++;
    string pivotkey = L.p[0].sname;

    while (low < high)
    {
        // 从右向左找第一个 < pivot 的
        while (low < high)
        {
            cmpNum++;
            if (L.p[high].sname < pivotkey)
                break;
            high--;
        }
        L.p[low] = L.p[high];
        movNum++;
        // 从左向右找第一个 > pivot 的
        while (low < high)
        {
            cmpNum++;
            if (L.p[low].sname > pivotkey)
                break;
            low++;
        }
        L.p[high] = L.p[low];
        movNum++;
    }

    // 枢轴放回最终位置
    L.p[low] = L.p[0];
    movNum++;
    return low;
}

void QSort(SqList &L, int low, int high)
{
    if (low < high)
    {
        int mid = Partition(L, low, high);
        QSort(L, low, mid - 1);
        QSort(L, mid + 1, high);
    }
}

void QuickSort(SqList &L)
{
    cmpNum = 0;
    movNum = 0;
    QSort(L, 1, L.length);
}