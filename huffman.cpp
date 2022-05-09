#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MaxW = 1e5 + 10;

class HuffNode
{public:
    int weight;
    int parent;
    int leftchild;
    int rightchild;
};

class HuffMan
{private:
    void MakeTree()//建树，私有函数，被公有函数调用
    {
        int i,s1,s2;
        SelectMin(i - 1,&s1,&s2);
        huffTree[s1].parent = i;
        huffTree[s2].parent = i;

        huffTree[i].leftchild  = s1;
        huffTree[i].rightchild = s2;

        huffTree[i].weight = huffTree[s1].weight + huffTree[s2].weight;
    }
    void SelectMin(int pos,int *s1,int *s2)//从1到pos找到权值最小的两个结点，把结点下标存在s1和s2中
    {
        int w1,w2;
        w1 = w2 = MaxW;
        for(int i = 1;i <= pos;i ++)
        {
            if(huffTree[i].weight < w1 && huffTree[i].parent == 0)
            {
                w2 = w1;
                *s2 = *s1;
                w1 = huffTree[i].weight;
                *s1 = i;
            }
            else if(huffTree[i].weight < w2 && huffTree[i].parent == 0)
            {
                w2 = huffTree[i].weight;
                *s2 = i;
            }
        }
    }
 public:
    int len; //结点数量
    int lnum; //叶子数量
    HuffNode *huffTree; //赫夫曼树，用数组表示
    string *huffCode; //每个字符对应的赫夫曼编码
    void MakeTree(int n,int wt[]); //共有函数，被主函数main调用
    void Coding()
    {
        char *cd;
        int c,f,start;

        cd = new char[lnum];
        cd[lnum - 1] = '\0';
        
        for(int i = 1;i <= lnum;i ++)
        {
            start = lnum - 1;
            c = i;f = huffTree[i].parent;
            while(f != 0)
            {
                if(huffTree[f].leftchild == c)  cd[--start] = '0';
                else if(huffTree[f].rightchild == c)    cd[--start] = '1';
                c = f;
                f = huffTree[c].parent;
            }
            huffCode[i].assign(&cd[start]);
        }
        delete[] cd;
    }
    void Destroy()
    {
        len = 0;
        lnum = 0;
        delete []huffTree;
        delete []huffCode;
    }
};

//构建huffman树
void HuffMan::MakeTree(int n,int wt[]) //参数是叶子结点和叶子权值
{//共有函数，对外接口
    int i;
    lnum = n;
    len = 2 * n - 1;
    huffTree = new HuffNode[2 * n];
    huffCode = new string[lnum + 1];//位置从1开始计算
    //huffCode实质上是个二维字符数组，第i行表示第i个字符对应的编码

    //huffTree初始化，从1号开始编码
    for(int i = 1;i <= n;i ++ )  huffTree[i].weight = wt[i - 1];
    for(int i = 1;i <= len;i ++ )
    {
        if(i > n) huffTree[i].weight = 0;
        huffTree[i].parent = 0;
        huffTree[i].leftchild = 0;
        huffTree[i].rightchild = 0;
    }
    MakeTree(); //调用私有函数建树
}

int main()
{
    int wt[1000];
    int n;
    cin >> n;
    HuffMan myhuff;
    while(n -- )
    {
        int num;
        cin >> num;
        for(int i = 0;i < num;i ++ )   cin >> wt[i];
        myhuff.MakeTree(num,wt);
        myhuff.Coding();
        for(int i = 1;i <= num;i ++ )
        {
            cout << myhuff.huffTree[i].weight << '-' << myhuff.huffCode[i] << endl;
        }
        myhuff.Destroy();
    }
    return 0;
}