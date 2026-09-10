#include "1.1.2.h"

void InitList(LinkList &L)
{ // 构造一个空的单链表L
    L = new LNode;
    L->next = NULL;
}

int Check(string name, string filename)
{ // 读取文件，判断是否删除成功
    ifstream infile;
    infile.open(filename);
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
            if (temp.name == name)
            {
                infile.close();
                return 0;
            }
            flag++;
        }
    }
    infile.close();
    return 1;
}

string PlantInfo(string name, string filename)
{ // 查找待删除植物信息
    ifstream infile;
    infile.open(filename); // 打开文件
    string line;
    while (getline(infile, line))
    {                          // 读取一行植物数据
        string temp;           // 暂存每一行植物数据
        stringstream ss(line); // 分割每一行植物数据的4个数据项
        string s;
        int flag = 0;
        while (getline(ss, s, '#'))
        {
            if (flag == 0)
                temp = s;
            flag++;
            if (temp == name)
                return line;
            break;
        }
    }
    return "";
}

int main()
{
    string name;
    cin >> name;
    LinkList L;
    InitList(L);
    string filename = "data_edit/plant.txt";
    // 读plant.txt文件
    ReadFile(L, filename);
    string plant;
    if (PlantInfo(name, filename) != "")
    {
        plant = PlantInfo(name, filename);
        DeletePlant(L, name, filename);
        if (Check(name, filename)) // 如果删除成功，输出已删除植物的全部信息
            cout << plant << endl;
        else
            cout << "删除失败" << endl;
    }
    else
        cout << "删除失败" << endl;

    return 0;
}
