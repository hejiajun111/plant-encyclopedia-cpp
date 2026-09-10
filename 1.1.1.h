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

    // 建立头结点
    L = new LNode;
    L->next = NULL;

    LNode *tail = L;

    ifstream fin(filename.c_str());
    if (!fin.is_open())
        return;

    string line;

    while (getline(fin, line))
    {
        // 兼容 Windows 文件的 \r\n
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty())
            continue;

        // 找三个 #
        size_t p1 = line.find('#');
        if (p1 == string::npos)
            continue;

        size_t p2 = line.find('#', p1 + 1);
        if (p2 == string::npos)
            continue;

        size_t p3 = line.find('#', p2 + 1);
        if (p3 == string::npos)
            continue;

        Plant t;

        t.name = line.substr(0, p1);
        t.sname = line.substr(p1 + 1, p2 - p1 - 1);
        t.detail = line.substr(p3 + 1);

        // 清空地点数组
        for (int i = 0; i < 100; i++)
            t.place[i] = "";

        // 解析分布地
        string places = line.substr(p2 + 1, p3 - p2 - 1);

        int cnt = 0;
        size_t start = 0;

        while (start <= places.size() && cnt < 100)
        {
            size_t pos = places.find('@', start);

            if (pos == string::npos)
            {
                t.place[cnt++] = places.substr(start);
                break;
            }

            t.place[cnt++] = places.substr(start, pos - start);
            start = pos + 1;
        }

        // 尾插法
        LNode *p = new LNode;
        p->data = t;
        p->next = NULL;

        tail->next = p;
        tail = p;
    }

    fin.close();
}

int InPlant(LinkList L, string name)
{ // 判断该植物名称name是否存在于链表中

    if (L == NULL)
        return 0;

    LNode *p = L->next;

    while (p != NULL)
    {
        if (p->data.name == name)
            return 1;

        p = p->next;
    }

    return 0;
}

bool InsertPlant(LinkList &L, string filename)
{
    Plant plant;
    int n;

    getline(cin >> ws, plant.name);
    getline(cin, plant.sname);

    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++)
        getline(cin, plant.place[i]);

    getline(cin, plant.detail);

    // 判断是否已存在
    if (InPlant(L, plant.name))
        return false;

    // 判断原文件最后有没有换行
    bool needNewLine = false;

    {
        ifstream fin(filename, ios::binary);

        if (fin)
        {
            fin.seekg(0, ios::end);

            streampos len = fin.tellg();

            if (len > 0)
            {
                fin.seekg(-1, ios::end);

                char ch;
                fin.get(ch);

                if (ch != '\n')
                    needNewLine = true;
            }
        }
    }

    // 追加新植物
    ofstream fout(filename, ios::app);

    if (!fout)
        return false;

    // 原文件末尾没有换行时，先补一个
    if (needNewLine)
        fout << '\n';

    fout << plant.name << "#"
         << plant.sname << "#";

    for (int i = 0; i < n; i++)
    {
        if (i)
            fout << "@";

        fout << plant.place[i];
    }

    fout << "#" << plant.detail;

    fout.close();

    // 同时加入链表
    LNode *node = new LNode;
    node->data = plant;
    node->next = NULL;

    LNode *p = L;

    while (p->next != NULL)
        p = p->next;

    p->next = node;

    return true;
}