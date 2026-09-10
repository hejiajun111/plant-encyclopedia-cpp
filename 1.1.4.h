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
{
    // 顺序表初始化
    L.plant = new Plant[10000];
    L.length = 0;
}
void ListInsert(SqList &L, int i, Plant p)
{ // 在顺序表L中第i个位置插入新的植物p
    for (int j = L.length - 1; j >= i - 1; j--)
        L.plant[j + 1] = L.plant[j]; // 插入位置及之后的植物后移
    L.plant[i - 1] = p;              // 将新植物p放入第i个位置
    L.length++;                      // 表长加1
}
void ReadFile(SqList &L, string filename)
{
    // 读取plant.txt文件，调用ListInsert函数将每条植物数据插入顺序表
    ifstream infile;
    infile.open(filename); // 打开文件
    string line;
    while (getline(infile, line))
    {                          // 读取一行植物数据
        Plant temp;            // 暂存每一行植物数据
        stringstream ss(line); // 分割每一行植物数据的4个数据项
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
                stringstream ssplace(s); // 保存每一行植物数据的分布地
                string place;
                int placenum = 0;
                while (getline(ssplace, place, '@'))
                {
                    temp.place[placenum] = place;
                    placenum++;
                }
            }
            if (flag == 3)
                temp.detail = s;
            flag++;
        }
        ListInsert(L, L.length + 1, temp); // 往顺序表中插入该行植物数据
    }
}
int Search_Seq(SqList L, string key)
{ // 在顺序表L中顺序查找植物学名等于key的数据元素
  // 若找到，则返回该元素在表中的下标，否则返回-1
    for (int i = 0; i < L.length; i++) // 从后往前找
        if (L.plant[i].sname == key)
            return i;
    return -1;
}
double ASL_Seq(SqList L)
{ // 返回基于顺序表的顺序查找的ASL
    return (L.length + 1) / 2.0;
}