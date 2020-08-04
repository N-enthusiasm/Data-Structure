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
typedef int VerTexType; //顶点的数据类型
typedef int ArcType;     //边的权值类型
using namespace std;
bool visited[MVNum],visited2[MVNum],visited3[MVNum],visited4[MVNum];

//-------------------邻接矩阵----------------------------
typedef struct
{
    VerTexType vexs[MVNum];  //顶点表
    ArcType arcs[MVNum][MVNum]; //邻接矩阵
    int vexnum,arcnum;  //图得当前点数和边数
}AMGraph;

//返回顶点v在图G中的位置(邻接矩阵)
int LocateVex(AMGraph G,int v)
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(v==G.vexs[i])
            return i;
    }
    return 0;
}

//采用邻接矩阵建立图
Status CreateUDN(AMGraph &G)
{
    cout<<"输入总顶点数，总边数:";
    cin>>G.vexnum>>G.arcnum; //输入顶点总数和边总数
    cout<<"依次输入顶点信息:";
    for(int i=0;i<G.vexnum;i++)
        cin>>G.vexs[i];

    //初始化各边权值为最大值
    for(int i=0;i<G.vexnum;i++)
    {
        for(int j=0;j<G.vexnum;j++)
            G.arcs[i][j]=MAXINT;
    }

    cout<<"输入每条边依附的顶点及权值:"<<endl;
    for(int k=0;k<G.arcnum;k++)
    {
        int v1,v2, w;
        cin>>v1>>v2>>w;  //依次输入一条边依附得顶点和边的权值
        //确定v1,v2在G中的位置，即顶点数组的下标
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        G.arcs[i][j]=w;
        G.arcs[j][i]=G.arcs[i][j];
    }
    return OK;
}

//用邻接矩阵表示深度优先搜索方式遍历图
void DFS_AM(AMGraph G,int v)
{
    //访问第v个结点，并置访问标志数组为true
    cout<<G.vexs[v];
    visited[v]=true;
    for(int w=0;w<G.vexnum;w++)
    {
        if((G.arcs[v][w]!=MAXINT) && (!visited[w]))//如果w是v的邻接点且w未访问
            DFS_AM(G,w);
    }
}

//---------------------邻接表-----------------------------
//边结点
typedef struct ArcNode
{
    int adjvex; //该边所指向的顶点位置
    struct ArcNode * nextarc;  //指向下一条边的指针
}ArcNode;

//顶点信息
typedef struct VNode
{
    VerTexType data;     //顶点值
    ArcNode * firstarc;  //指向第一条依附该顶点的边的指针
}VNode,AdjList[MVNum];  //AdjList表示邻接表类型

//邻接表
typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;    //图的当前顶点数和边数
}ALGraph;

//返回顶点v在图G中的位置(邻接表)
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

//采用邻接表建立图
Status CreateUDG(ALGraph &G)
{
    cout<<"输入总顶点数，总边数：";
    cin>>G.vexnum>>G.arcnum;  //输入总顶点数和总边数
    cout<<"依次输入顶点值:";
    for(int i=0;i<G.vexnum;i++)
    {
        cin>>G.vertices[i].data;  //输入顶点值
        G.vertices[i].firstarc=NULL; //初始化表头结点的指针域为NULL
    }
    cout<<"输入每条边依附的两个顶点:"<<endl;
    for(int k=0;k<G.arcnum;k++)
    {
        int v1,v2;
        cin>>v1>>v2;  //输入一条边依附的两个顶点
        //确定v1,v2在G中的位置，即顶点数组的下标
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        ArcNode *p1=new ArcNode; //生成一个新的边结点p1
        p1->adjvex=j;
        //将新结点*p1插入顶点vi的边表头部
        p1->nextarc=G.vertices[i].firstarc;
        G.vertices[i].firstarc=p1;

        ArcNode *p2=new ArcNode;  //生成一个新的边结点p2
        p2->adjvex=i;
        //将新结点*p2插入顶点vj的边表头部
        p2->nextarc=G.vertices[j].firstarc;
        G.vertices[j].firstarc=p2;
    }
    return OK;
}


//用邻接表表示深度优先搜索方式遍历图
void DFS_AL(ALGraph G,int v)
{
    //访问第v个顶点，并置访问标志数组相应分量值为true
    cout<<G.vertices[v].data;
    visited2[v]=true;
    ArcNode *p=G.vertices[v].firstarc;   //p指向v的第一个边结点
    while(p!=NULL)  //边结点非空
    {
        int w=p->adjvex;    //表示w是v的邻接点
        if(!visited2[w])
            DFS_AL(G,w); //如果w未访问，则递归调用DFS_AL
        p=p->nextarc;   //p指向下一个边结点
    }
}

//-------------------广度优先遍历----------------------------
//顺序队
typedef struct
{
    VerTexType *base;//基地址
    int front;//头指针
    int rear;//尾指针
}SqQueue;

//初始化队
Status InitQueue(SqQueue &Q)
{
    Q.base=new VerTexType[MAXSIZE];
    if(!Q.base) exit(OVERFLOW);
    Q.front=Q.rear=0;//头尾指针置为零，队列为空
    return OK;
}

//判断队列是否为空
Status QueueEmpty(SqQueue Q)
{
    if(Q.front==Q.rear)//如果头位置指针相等，则为空
        return OK;
    else
        return ERROR;
}

//入队
Status EnQueue(SqQueue &Q,int e)
{
    if(Q.front==(Q.rear+1)%MAXSIZE)//队满
        return ERROR;
    else
    {
        Q.base[Q.rear]=e;
        Q.rear=(Q.rear+1)%MAXSIZE;
        return OK;
    }
}

//出队
Status DeQueue(SqQueue &Q,int &e)
{
    if(Q.front==Q.rear)//队空
        return ERROR;
    else
    {
        e=Q.base[Q.front];
        Q.front=(Q.front+1)%MAXSIZE;
        return OK;
    }
}

//用邻接矩阵表示广度优先搜索方式遍历图
void BFS_AM(AMGraph G,int v)
{
    SqQueue Q;
    int i,j;

    InitQueue(Q);

    if(!visited3[v])
    {
        visited3[v]=true;
        cout<<G.vexs[v];

        EnQueue(Q,v);//把刚刚访问过的节点入队
        while(!QueueEmpty(Q))
        {
            DeQueue(Q,v); //队不空时出队得到队头结点
            for(j=0;j<G.vexnum;j++)
            {
                if(!visited3[j] && G.arcs[v][j]!=MAXINT)
                {//如果新的结点和刚访问过的结点之间有边且没被访问过
                    visited3[j]=true;//访问它
                    cout<<G.vexs[j];
                    EnQueue(Q,j);//再次入队，找下一个结点
                }
            }
        }
    }
}

//用邻接表表示广度优先搜索方式遍历图
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


//---------------Dijkstra最短路径------------------
void ShortestPath_DIJ(AMGraph G, int v0)
{
    //数组S用来记录是否已经确定最短路径
    bool S[MVNum];
    //数组D记录v0到第i个结点的最短路径长度
    //数组Path用来记录当前最短路径上v的前驱节点
    int D[MVNum],Path[MVNum];

    int n=G.vexnum;                         //n为G中顶点的个数
    for(int v=0;v<n;++v)
    {               //n个顶点依次初始化
       S[v]=false;               //S初始为空集
       D[v]=G.arcs[v0][v];       //将v0到各个终点的最短路径长度初始化
       if(D[v]<MAXINT)
           Path[v]=v0;          //v0和v之间有弧，将v的前驱置为v0
       else
           Path[v]=-1;          //如果v0和v之间无弧，则将v的前驱置为-1
    }
    S[v0]=true;      //将v0加入S
    D[v0]=0;          //源点到源点的距离为0
    /*开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S集*/
    int v=0;
    for(int i=1;i<n; ++i)
    {//对其余n-1个顶点，依次进行计算
        int min= MAXINT;
        for(int w=0;w<n;++w)
            if(!S[w] && D[w]<min)
            {//选择一条当前的最短路径，终点为v
                v=w;
                min=D[w];
            }
        S[v]=true; //将v加入S
        for(int w=0;w<n; ++w)
           //更新从v0出发到集合V?S上所有顶点的最短路径长度
            if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
            {
                D[w]=D[v]+G.arcs[v][w];     //更新D[w]
                Path[w]=v;                     //更改w的前驱为v
            }
    }
    cout<<"以v0为起点的图的最短路径为:"<<endl;
    for(int i=0;i<G.vexnum;i++)
    {
        cout<<"v"<<G.vexs[0]<<"->v"<<G.vexs[i]<<":";
        if(D[i]!=MAXINT) //可以到达
        {
            cout<<D[i]<<endl;
        }
        else
        {
            cout<<"不可达，无最短路径"<<endl;
        }
    }
}



void show()
{
    string s1(80,'*');
    string s2(20,'*');
    cout<<s1<<endl;
    cout<<s2<<setw(40)<<left<<"1.采用邻接矩阵建立图"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"2.采用邻接表建立图"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"3.用邻接矩阵表示深度优先搜索方式遍历图"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"4.用邻接表表示深度优先搜索方式遍历图"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"5.用邻接矩阵表示广度优先搜索方式遍历图"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"6.用邻接表表示广度优先搜索方式遍历图"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"7.求图的最短路径"<<s2<<endl;
    cout<<s2<<setw(40)<<left<<"8.退出"<<s2<<endl;
    cout<<s1<<endl;
    cout<<"请输入您的选择：";
}
int main()
{
    AMGraph G1;
    ALGraph G2;
    int v=0,v0=0;//遍历的起始点和最短路径的源点，如果要修改遍历起始点或源点直接修改v和v0即可

    int x;
    show();
    cin>>x;
    while(1)
    {
        switch(x)
        {
            case 1:
                CreateUDN(G1);
                cout<<"创建成功！"<<endl;
                break;
            case 2:
                CreateUDG(G2);
                cout<<"创建成功！"<<endl;
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
                cout<<"输入不合法，请重新输入。"<<endl;
        }
        cout<<"请输入您的选择：";
        cin>>x;
    }
    return 0;
}
