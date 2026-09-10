#include <bits/stdc++.h>
#define MVNum 34 // 最大顶点数
#define ERROR 0
using namespace std;

typedef struct
{
    string vexs[MVNum];     // 顶点表
    int arcs[MVNum][MVNum]; // 邻接矩阵
    int vexnum;             // 图的总顶点数
    int arcnum;             // 图的总边数
} Graph;
int LocateVex(Graph G, string u)
{
    for (int i = 0; i < G.vexnum; i++)
        if (G.vexs[i] == u)
            return i;

    return ERROR;
}

string OrigialVex(Graph G, int u)
{
    if (u >= 0 && u < G.vexnum)
        return G.vexs[u];

    return "";
}
void InitGraph(Graph &G)
{
    G.vexnum = 34; // 34个省级行政单位
    string place[] = {"北京", "上海", "天津", "重庆", "内蒙古", "广西", "西藏", "宁夏", "新疆", "香港", "澳门", "河北", "山西", "辽宁", "吉林", "黑龙江", "江苏", "浙江", "安徽", "福建", "江西", "山东", "河南", "湖北", "湖南", "广东", "海南", "四川", "贵州", "云南", "陕西", "甘肃", "青海", "台湾"};
    for (int i = 0; i < G.vexnum; i++)
        G.vexs[i] = place[i];
}
void CreateGraph(Graph &G, string filename)
{
    const int INF = 0x3f3f3f3f;
    // 初始化邻接矩阵
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            if (i == j)
                G.arcs[i][j] = 0;
            else
                G.arcs[i][j] = INF;
        }
    }
    G.arcnum = 0;
    ifstream fin(filename);
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        string a, b, dis;
        stringstream ss(line);
        getline(ss, a, '#');
        getline(ss, b, '#');
        getline(ss, dis, '#');

        if (a.empty() || b.empty() || dis.empty())
            continue;

        int x = LocateVex(G, a);
        int y = LocateVex(G, b);
        int w = stoi(dis);

        G.arcs[x][y] = w;
        G.arcnum++;
    }

    fin.close();
}

int Dijkstra(Graph G, string v1, string v2)
{
    const int INF = 0x3f3f3f3f;
    int s = LocateVex(G, v1);
    int t = LocateVex(G, v2);
    vector<int> dis(MVNum, INF);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dis[s] = 0;
    pq.push({0, s});

    while (!pq.empty())
    {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();

        if (d != dis[u])
            continue;

        for (int v = 0; v < G.vexnum; v++)
        {
            if (G.arcs[u][v] == INF)
                continue;

            if (dis[v] > dis[u] + G.arcs[u][v])
            {
                dis[v] = dis[u] + G.arcs[u][v];
                pq.push({dis[v], v});
            }
        }
    }

    return dis[t];
}

int GetDistribution(string name, string distribution[], string filename)
{
    ifstream fin(filename);
    string line;

    while (getline(fin, line))
    {
        string pname, sname, places, detail;
        stringstream ss(line);

        getline(ss, pname, '#');
        getline(ss, sname, '#');
        getline(ss, places, '#');
        getline(ss, detail);

        if (pname == name)
        {
            stringstream ps(places);
            string place;

            int cnt = 0;
            while (getline(ps, place, '@'))
                distribution[cnt++] = place;

            fin.close();
            return cnt;
        }
    }

    fin.close();
    return 0;
}