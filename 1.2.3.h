#include <bits/stdc++.h>
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
    Plant *plant;
    int length;
} SqList;
void InitList(SqList &L)
{ // 顺序表初始化
    L.plant = new Plant[10000];
    L.length = 0;
}
void ListInsert(SqList &L, int i, Plant p)
{
    // 在顺序表L中第i个位置插入新的植物p
    for (int j = L.length; j >= i; j--)
    {
        *(L.plant + j + 1) = *(L.plant + j);
    }
    L.plant[i] = p;
}
void ReadFile(SqList &L, string filename)
{ // 读取plant.txt文件，调用ListInsert函数将每条植物数据插入顺序表
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
        ListInsert(L, ++L.length, temp);
        // cerr << L.length << "\n";
    }
    is.close();
}
void Sort_Seq(SqList L)
{
    // 根据植物学名对顺序表L由小到大进行排序
    int m = L.length;
    sort(L.plant + 1, L.plant + m + 1, [](Plant &x, Plant &y) -> bool
         { return x.sname < y.sname; });
}
int Search_Bin(SqList L, string key)
{
    // 在顺序表L中折半查找植物学名等于key的数据元素
    // 若找到，则返回该元素在表中的下标，否则返回-1
    int l = 1, r = L.length;
    while (l < r)
    {
        int mid = (l + r + 1) / 2;
        if (L.plant[mid].sname > key)
            r = mid - 1;
        else
            l = mid;
    }
    return L.plant[l].sname == key ? l : -1;
}

double ASL_Bin(SqList L)
{
    int n = L.length;
    if (n == 0)
        return 0;
    int k = log2(n);
    long long sum = 1LL * (k + 1) * n - (1LL << (k + 1)) + k + 2;

    return (double)sum / n;
}