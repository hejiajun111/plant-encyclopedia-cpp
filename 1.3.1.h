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
{ // 读取文件，将数据存入链表L
    ifstream fin(filename);
    if (!fin)
        return;

    // L 为已经初始化的头结点
    LinkList tail = L;
    while (tail->next)
        tail = tail->next;

    string line;
    while (getline(fin, line))
    {
        // 兼容 Windows 换行符
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.empty())
            continue;

        Plant plant;
        string places;
        stringstream ss(line);

        if (!getline(ss, plant.name, '#') ||
            !getline(ss, plant.sname, '#') ||
            !getline(ss, places, '#'))
            continue;

        getline(ss, plant.detail);

        stringstream ps(places);
        for (int i = 0; i < 100 && getline(ps, plant.place[i], '@'); ++i)
            ;

        tail->next = new LNode{plant, nullptr};
        tail = tail->next;
    }
}

// int Is_EngChar(char c)
// { // 判断是否为英文字符，若是，则返回1，不是则返回0
//     if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z' || (c >= 'A' && c <= 'Z')) || c == '=' || c == '!' || c == '?' || c == '_' || c == '{' || c == '}' || c == ',' || c == ';' || c == '-' || c == '/' || c == '(' || c == ')' || c == ':' || c == '×' || c == '[' || c == ']' || c == '.' || c == 'I')
//         return 1;

//     else
//         return 0;
// }

// pos 和返回值均为从 1 开始的字节位置，匹配失败返回 0
int Index_BF(const string &S, const string &T, int pos)
{ // 返回模式T在主串S中第pos个字符开始第一次出现的位置。若不存在，则返回值为0
  // 其中，T非空，1≤pos≤S.length
  // 为判断是否为汉字，需调用Is_EngChar函数
    int n = S.size(), m = T.size();
    if (pos < 1 || pos > n + 1)
        return 0;
    // 枚举匹配起点，逐字节比较
    for (int start = pos - 1; start <= n - m; ++start)
    {
        int j = 0;
        while (j < m && S[start + j] == T[j])
            ++j;

        if (j == m)
            return start + 1;
    }
    return 0;
}

void SearchInfo(LinkList L, const string &keyWord)
{ // 调用Index_BF算法进行关键信息查询
    if (!L || keyWord.empty())
        return;

    for (LinkList p = L->next; p; p = p->next)
    {
        if (Index_BF(p->data.detail, keyWord, 1))
            cout << p->data.name << '\n';
    }
}