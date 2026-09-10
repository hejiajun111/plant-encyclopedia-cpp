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
typedef struct
{ // 开放地址法散列表的存储表示
    Plant *key;
    int length;
} HashTable;
void InitHT(HashTable &HT)
{ // 散列表初始化
    HT.key = new Plant[m];
    HT.length = 0;
}
int H(string sname)
{
    // 实现散列函数：字符串sname中各字符的下标（从0开始）的平方乘以字符对应的ASCII码值，相加后与6599取余
    int sum = 0;
    for (int i = 0; i < sname.size(); i++)
    {
        sum += (i * i * int(sname[i]));
    }
    return sum % 6599;
}
void HTInsert(HashTable &HT, Plant p, int &sumCmp)
{ // 往散列表中插入新的植物p
  // 在插入的过程中统计总的比较次数sumCmp
    int H0 = H(p.sname);
    sumCmp++;
    if (HT.key[H0].name == "") // 该位置未被占用，直接插入
        HT.key[H0] = p;
    else
    {
        for (int i = 1; i < m; i++)
        {
            sumCmp++;
            int Hi = (H0 + i) % m; // 按照线性探测法计算下一个散列地址Hi
            if (HT.key[Hi].name == "")
            { // 若单元Hi为空，插入该单元
                HT.key[Hi] = p;
                break;
            }
        }
    }
    HT.length++;
}
void ReadFile(HashTable &HT, int &sumCmp, string filename)
{
    // 读取plant.txt文件，调用HT函数将每条植物数据插入散列表
    ifstream infile(filename); // 打开文件
    string line;
    while (getline(infile, line))
    {                              // 读取一行植物数据
        Plant temp;                // 暂存每一行植物数据
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

        HTInsert(HT, temp, sumCmp); // 往散列表中插入该行植物数据
    }
}
int SearchHash(HashTable HT, string key)
{ // 在散列表HT中查找植物学名等于key的元素
  // 若找到，则返回散列表的单元标号，否则返回-1
    int H0 = H(key);            // 根据散列函数H（key）计算散列地址
    if (HT.key[H0].sname == "") // 若单元H0为空，则所查元素不存在
        return -1;
    else if (HT.key[H0].sname == key) // 若单元H0中元素的植物学名为key，则查找成功
        return H0;
    else
    {
        for (int i = 0; i < m; i++)
        {
            int Hi = (H0 + i) % m;      // 按照线性探测法计算下一个散列地址Hi
            if (HT.key[Hi].sname == "") // 若单元Hi为空，则所查元素不存在
                return -1;
            else if (HT.key[Hi].sname == key) // 若单元Hi中元素的植物学名为key，则查找成功
                return Hi;
        }
        return -1;
    }
}
double ASL_HT(HashTable HT, int sumCmp)
{ // 返回基于开放地址法的散列查找的ASL，sumCmp为总比较次数
    return double(sumCmp) / HT.length;
}