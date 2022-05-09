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
    void MakeTree()//������˽�к����������к�������
    {
        int i,s1,s2;
        SelectMin(i - 1,&s1,&s2);
        huffTree[s1].parent = i;
        huffTree[s2].parent = i;

        huffTree[i].leftchild  = s1;
        huffTree[i].rightchild = s2;

        huffTree[i].weight = huffTree[s1].weight + huffTree[s2].weight;
    }
    void SelectMin(int pos,int *s1,int *s2)//��1��pos�ҵ�Ȩֵ��С��������㣬�ѽ���±����s1��s2��
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
    int len; //�������
    int lnum; //Ҷ������
    HuffNode *huffTree; //�շ��������������ʾ
    string *huffCode; //ÿ���ַ���Ӧ�ĺշ�������
    void MakeTree(int n,int wt[]); //���к�������������main����
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

//����huffman��
void HuffMan::MakeTree(int n,int wt[]) //������Ҷ�ӽ���Ҷ��Ȩֵ
{//���к���������ӿ�
    int i;
    lnum = n;
    len = 2 * n - 1;
    huffTree = new HuffNode[2 * n];
    huffCode = new string[lnum + 1];//λ�ô�1��ʼ����
    //huffCodeʵ�����Ǹ���ά�ַ����飬��i�б�ʾ��i���ַ���Ӧ�ı���

    //huffTree��ʼ������1�ſ�ʼ����
    for(int i = 1;i <= n;i ++ )  huffTree[i].weight = wt[i - 1];
    for(int i = 1;i <= len;i ++ )
    {
        if(i > n) huffTree[i].weight = 0;
        huffTree[i].parent = 0;
        huffTree[i].leftchild = 0;
        huffTree[i].rightchild = 0;
    }
    MakeTree(); //����˽�к�������
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