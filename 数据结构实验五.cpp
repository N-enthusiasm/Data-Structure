#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100
#define MAXINT 3698
#define MVNum 100

typedef int Status;
typedef int VerTexType; //�������������
typedef int ArcType;     //�ߵ�Ȩֵ����
using namespace std;
bool visited[MVNum],visited2[MVNum],visited3[MVNum],visited4[MVNum];

//-------------------�ڽӾ���----------------------------
typedef struct
{
    VerTexType vexs[MVNum];  //�����
    ArcType arcs[MVNum][MVNum]; //�ڽӾ���
    int vexnum,arcnum;  //ͼ�õ�ǰ�����ͱ���
}AMGraph;

//���ض���v��ͼG�е�λ��(�ڽӾ���)
int LocateVex(AMGraph G,int v)
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(v==G.vexs[i])
            return i;
    }
    return 0;
}

//�����ڽӾ�����ͼ
Status CreateUDN(AMGraph &G)
{
    cout<<"�����ܶ��������ܱ���:";
    cin>>G.vexnum>>G.arcnum; //���붥�������ͱ�����
    cout<<"�������붥����Ϣ:";
    for(int i=0;i<G.vexnum;i++)
        cin>>G.vexs[i];

    //��ʼ������ȨֵΪ���ֵ
    for(int i=0;i<G.vexnum;i++)
    {
        for(int j=0;j<G.vexnum;j++)
            G.arcs[i][j]=MAXINT;
    }

    cout<<"����ÿ���������Ķ��㼰Ȩֵ:"<<endl;
    for(int k=0;k<G.arcnum;k++)
    {
        int v1,v2, w;
        cin>>v1>>v2>>w;  //��������һ���������ö���ͱߵ�Ȩֵ
        //ȷ��v1,v2��G�е�λ�ã�������������±�
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        G.arcs[i][j]=w;
        G.arcs[j][i]=G.arcs[i][j];
    }
    return OK;
}

//���ڽӾ����ʾ�������������ʽ����ͼ
void DFS_AM(AMGraph G,int v)
{
    //���ʵ�v����㣬���÷��ʱ�־����Ϊtrue
    cout<<G.vexs[v];
    visited[v]=true;
    for(int w=0;w<G.vexnum;w++)
    {
        if((G.arcs[v][w]!=MAXINT) && (!visited[w]))//���w��v���ڽӵ���wδ����
            DFS_AM(G,w);
    }
}

//---------------------�ڽӱ�-----------------------------
//�߽��
typedef struct ArcNode
{
    int adjvex; //�ñ���ָ��Ķ���λ��
    struct ArcNode * nextarc;  //ָ����һ���ߵ�ָ��
}ArcNode;

//������Ϣ
typedef struct VNode
{
    VerTexType data;     //����ֵ
    ArcNode * firstarc;  //ָ���һ�������ö���ıߵ�ָ��
}VNode,AdjList[MVNum];  //AdjList��ʾ�ڽӱ�����

//�ڽӱ�
typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;    //ͼ�ĵ�ǰ�������ͱ���
}ALGraph;

//���ض���v��ͼG�е�λ��(�ڽӱ�)
int LocateVex(ALGraph G,int v)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(v==G.vertices[i].data)
        return i;
    }
    return 0;
}

//�����ڽӱ���ͼ
Status CreateUDG(ALGraph &G)
{
    cout<<"�����ܶ��������ܱ�����";
    cin>>G.vexnum>>G.arcnum;  //�����ܶ��������ܱ���
    cout<<"�������붥��ֵ:";
    for(int i=0;i<G.vexnum;i++)
    {
        cin>>G.vertices[i].data;  //���붥��ֵ
        G.vertices[i].firstarc=NULL; //��ʼ����ͷ����ָ����ΪNULL
    }
    cout<<"����ÿ������������������:"<<endl;
    for(int k=0;k<G.arcnum;k++)
    {
        int v1,v2;
        cin>>v1>>v2;  //����һ������������������
        //ȷ��v1,v2��G�е�λ�ã�������������±�
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        ArcNode *p1=new ArcNode; //����һ���µı߽��p1
        p1->adjvex=j;
        //���½��*p1���붥��vi�ı߱�ͷ��
        p1->nextarc=G.vertices[i].firstarc;
        G.vertices[i].firstarc=p1;

        ArcNode *p2=new ArcNode;  //����һ���µı߽��p2
        p2->adjvex=i;
        //���½��*p2���붥��vj�ı߱�ͷ��
        p2->nextarc=G.vertices[j].firstarc;
        G.vertices[j].firstarc=p2;
    }
    return OK;
}


//���ڽӱ��ʾ�������������ʽ����ͼ
void DFS_AL(ALGraph G,int v)
{
    //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    cout<<G.vertices[v].data;
    visited2[v]=true;
    ArcNode *p=G.vertices[v].firstarc;   //pָ��v�ĵ�һ���߽��
    while(p!=NULL)  //�߽��ǿ�
    {
        int w=p->adjvex;    //��ʾw��v���ڽӵ�
        if(!visited2[w])
            DFS_AL(G,w); //���wδ���ʣ���ݹ����DFS_AL
        p=p->nextarc;   //pָ����һ���߽��
    }
}

//-------------------������ȱ���----------------------------
//˳���
typedef struct
{
    VerTexType *base;//����ַ
    int front;//ͷָ��
    int rear;//βָ��
}SqQueue;

//��ʼ����
Status InitQueue(SqQueue &Q)
{
    Q.base=new VerTexType[MAXSIZE];
    if(!Q.base) exit(OVERFLOW);
    Q.front=Q.rear=0;//ͷβָ����Ϊ�㣬����Ϊ��
    return OK;
}

//�ж϶����Ƿ�Ϊ��
Status QueueEmpty(SqQueue Q)
{
    if(Q.front==Q.rear)//���ͷλ��ָ����ȣ���Ϊ��
        return OK;
    else
        return ERROR;
}

//���
Status EnQueue(SqQueue &Q,int e)
{
    if(Q.front==(Q.rear+1)%MAXSIZE)//����
        return ERROR;
    else
    {
        Q.base[Q.rear]=e;
        Q.rear=(Q.rear+1)%MAXSIZE;
        return OK;
    }
}

//����
Status DeQueue(SqQueue &Q,int &e)
{
    if(Q.front==Q.rear)//�ӿ�
        return ERROR;
    else
    {
        e=Q.base[Q.front];
        Q.front=(Q.front+1)%MAXSIZE;
        return OK;
    }
}

//���ڽӾ����ʾ�������������ʽ����ͼ
void BFS_AM(AMGraph G,int v)
{
    SqQueue Q;
    int i,j;

    InitQueue(Q);

    if(!visited3[v])
    {
        visited3[v]=true;
        cout<<G.vexs[v];

        EnQueue(Q,v);//�Ѹոշ��ʹ��Ľڵ����
        while(!QueueEmpty(Q))
        {
            DeQueue(Q,v); //�Ӳ���ʱ���ӵõ���ͷ���
            for(j=0;j<G.vexnum;j++)
            {
                if(!visited3[j] && G.arcs[v][j]!=MAXINT)
                {//����µĽ��͸շ��ʹ��Ľ��֮���б���û�����ʹ�
                    visited3[j]=true;//������
                    cout<<G.vexs[j];
                    EnQueue(Q,j);//�ٴ���ӣ�����һ�����
                }
            }
        }
    }
}

//���ڽӱ��ʾ�������������ʽ����ͼ
void BFS_AL(ALGraph G,int v)
{
    int i;
    SqQueue Q;

    InitQueue(Q);
    //for (i=0;i<G.vexnum;i++)
    //{
        if(!visited4[v])
        {
            visited4[v]=true;
            cout<<G.vertices[v].data;
            EnQueue(Q,v);

            while(!QueueEmpty(Q))
            {
                DeQueue(Q,v);
                ArcNode *p=G.vertices[v].firstarc;
                while(p!=NULL)
                {
                    if(!visited4[p->adjvex])
                    {
                        visited4[p->adjvex]=true;
                        cout<<G.vertices[p->adjvex].data;
                        EnQueue(Q, p->adjvex);
                    }
                    p=p->nextarc;
                }
            }
        //}
    }
}


//---------------Dijkstra���·��------------------
void ShortestPath_DIJ(AMGraph G, int v0)
{
    //����S������¼�Ƿ��Ѿ�ȷ�����·��
    bool S[MVNum];
    //����D��¼v0����i���������·������
    //����Path������¼��ǰ���·����v��ǰ���ڵ�
    int D[MVNum],Path[MVNum];

    int n=G.vexnum;                         //nΪG�ж���ĸ���
    for(int v=0;v<n;++v)
    {               //n���������γ�ʼ��
       S[v]=false;               //S��ʼΪ�ռ�
       D[v]=G.arcs[v0][v];       //��v0�������յ�����·�����ȳ�ʼ��
       if(D[v]<MAXINT)
           Path[v]=v0;          //v0��v֮���л�����v��ǰ����Ϊv0
       else
           Path[v]=-1;          //���v0��v֮���޻�����v��ǰ����Ϊ-1
    }
    S[v0]=true;      //��v0����S
    D[v0]=0;          //Դ�㵽Դ��ľ���Ϊ0
    /*��ʼ��ѭ����ÿ�����v0��ĳ������v�����·������v�ӵ�S��*/
    int v=0;
    for(int i=1;i<n; ++i)
    {//������n-1�����㣬���ν��м���
        int min= MAXINT;
        for(int w=0;w<n;++w)
            if(!S[w] && D[w]<min)
            {//ѡ��һ����ǰ�����·�����յ�Ϊv
                v=w;
                min=D[w];
            }
        S[v]=true; //��v����S
        for(int w=0;w<n; ++w)
           //���´�v0����������V?S�����ж�������·������
            if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
            {
                D[w]=D[v]+G.arcs[v][w];     //����D[w]
                Path[w]=v;                     //����w��ǰ��Ϊv
            }
    }
    cout<<"��v0Ϊ����ͼ�����·��Ϊ:"<<endl;
    for(int i=0;i<G.vexnum;i++)
    {
        cout<<"v"<<G.vexs[0]<<"->v"<<G.vexs[i]<<":";
        if(D[i]!=MAXINT) //���Ե���
        {
            cout<<D[i]<<endl;
        }
        else
        {
            cout<<"���ɴ�����·��"<<endl;
        }
    }
}



void show()
{
    string s1(80,'*');
    string s2(20,'*');
    cout<<s1<<endl;
    cout<<s2<<setw(40)<<left<<"1.�����ڽӾ�����ͼ"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"2.�����ڽӱ���ͼ"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"3.���ڽӾ����ʾ�������������ʽ����ͼ"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"4.���ڽӱ��ʾ�������������ʽ����ͼ"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"5.���ڽӾ����ʾ�������������ʽ����ͼ"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"6.���ڽӱ��ʾ�������������ʽ����ͼ"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"7.��ͼ�����·��"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"8.�˳�"<<s2<<endl;
    cout<<s1<<endl;
    cout<<"����������ѡ��";
}
int main()
{
    AMGraph G1;
    ALGraph G2;
    int v=0,v0=0;//��������ʼ������·����Դ�㣬���Ҫ�޸ı�����ʼ���Դ��ֱ���޸�v��v0����

    int x;
    show();
    cin>>x;
    while(1)
    {
        switch(x)
        {
            case 1:
                CreateUDN(G1);
                cout<<"�����ɹ���"<<endl;
                break;
            case 2:
                CreateUDG(G2);
                cout<<"�����ɹ���"<<endl;
                break;
            case 3:
                DFS_AM(G1,v);
                cout<<endl;
                break;
            case 4:
                DFS_AL(G2,v);
                cout<<endl;
                break;
            case 5:
                BFS_AM(G1,v);
                cout<<endl;
                break;
            case 6:
                BFS_AL(G2,v);
                cout<<endl;
                break;
            case 7:
                ShortestPath_DIJ(G1,v0);
                break;
            case 8:
                return 0;
            default:
                cout<<"���벻�Ϸ������������롣"<<endl;
        }
        cout<<"����������ѡ��";
        cin>>x;
    }
    return 0;
}
