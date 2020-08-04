#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2

using namespace std;

//---------------------顺序栈-------------------------
typedef struct
{//栈的顺序存储结构
    int *base;//栈底指针
    int *top;//栈顶指针
    int stacksize;//栈可用的最大容量
}SqStack;

//初始化顺序栈
void InitStack(SqStack &S)
{
    S.base=new int[MAXSIZE];//为栈动态分配一个MAXSIZE容量的数组
    if(!S.base)
        cout<<"存储分配失败"<<endl;
    else
    {
        S.top=S.base;//栈顶指针初始化为和栈底指针相同
        S.stacksize=MAXSIZE;//栈的最大容量
        cout<<"顺序栈初始化成功！"<<endl;
    }
}

//取顺序栈的栈顶元素
void GetTop(SqStack S)
{
    if(S.top!=S.base)//如果栈非空
        cout<<"顺序栈栈顶元素为：" <<*(S.top-1)<<endl;//输出栈顶指针所指的下一个元素
    else
        cout<<"当前栈为空栈"<<endl;
}

//顺序栈的入栈操作
void Push(SqStack &S,int e)
{
    if(S.top-S.base==MAXSIZE)
        cout<<"当前栈已满"<<endl;//先判栈满
    else
    {
        *S.top++=e;//先加后压
        cout<<"入栈成功！"<<endl;
    }
}

//顺序栈的出栈操作
void Pop(SqStack &S ,int &e)
{
    if(S.top==S.base)
        cout<<"当前栈为空"<<endl;//先判是否栈空
    else
    {
        e=*--S.top;//先减后弹
        cout<<"出栈成功！"<<endl;
    }
}

//显示顺序栈元素
void DisplayS(SqStack S)
{
    if(S.top==S.base)
        cout<<"当前栈为空栈"<<endl;
    else
    {
        cout<<"栈中元素为";
        while(S.top!=S.base)
            cout<<*--S.top<<" ";
        cout<<endl;
    }
}

//---------------------链栈-------------------------
typedef struct StackNode
{
    int data;//数据域
    struct StackNode *next;//指针域
}StackNode ,*LinkStack;//LinkStack为指向结构体StackNode类型的指针

//初始化链栈
void InitStack(LinkStack &S)
{
    S=NULL;//构造一个空栈，栈顶指针置空
    cout<<"链栈初始化成功！"<<endl;
}

//链栈的入栈操作
void Push(LinkStack &S,int e)
{//链栈理论上是不会满的，因此不用判栈满
    StackNode *p=new StackNode;//生成新的节点
    p->data=e;
    p->next=S;
    S=p;
    cout<<"入栈成功！"<<endl;
}

//链栈的出栈操作
void Pop(LinkStack &S,int &e)
{
    if(S==NULL)
        cout<<"当前栈为空"<<endl;//先判是否栈空
    StackNode *p=new StackNode;
    p=S;
    e=S->data;
    S=S->next;
    delete p;//释放栈顶元素的空间
    cout<<"出栈成功！"<<endl;
}

//链栈取栈顶元素
void GetTop(LinkStack S)
{
    if(S->next == NULL)
        cout<<"链栈栈顶元素为："<<S->data<<endl;
    else
        cout<<"当前栈为空栈"<<endl;
}

//显示链栈元素
void DisplayS(LinkStack S)
{
    StackNode *p=new StackNode;
    p=S;
    while(p)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

//----------------------顺序队-------------------------
typedef struct
{//队列的顺序存储结构
    int *base;//存储空间基地址
    int front;//头指针
    int rear;//尾指针
}SqQueue;

//初始化顺序队
void InitQueue(SqQueue &Q)
{
    Q.base=new int[MAXSIZE];//为队列动态分配一个MAXSIZE容量的数组
    if(!Q.base)
        cout<<"存储分配失败"<<endl;//判断是否分配成功
    else
    {
        Q.front=Q.rear=0;//初始化时头尾指针均指向零
        cout<<"顺序队初始化成功！"<<endl;
    }
}

//取顺序队的队头元素
void GetHead(SqQueue Q)
{
    if(Q.front==Q.rear)
        cout<<"当前顺序队为空"<<endl;//先判断是否队空
    else
    cout<<"顺序队队头元素为："<<Q.base[Q.front]<<endl;
}

//顺序队的入队操作
void EnQueue(SqQueue &Q,int e)
{
    if((Q.rear+1)%MAXSIZE==Q.front)
        cout<<"当前队已满"<<endl;//先判断是否队满
    else
    {
        Q.base[Q.rear]=e;
        Q.rear=(Q.rear+1)%MAXSIZE;
        cout<<"入队成功！"<<endl;
    }
}

//顺序队的出队操作
void DeQueue(SqQueue &Q,int &e)
{
    if(Q.front==Q.rear)
        cout<<"当前队为空"<<endl;//先判断是否队空
    else
    {
        e=Q.base[Q.front];
        Q.front=(Q.front+1)%MAXSIZE;
        cout<<"出队成功！"<<endl;
    }
}

//显示顺序队元素
void DisplayQ(SqQueue Q)
{
    if(Q.front!=Q.rear)
    {
        int i=0;
        while(((Q.front+i)%MAXSIZE)!=Q.rear)
        {
            cout<<Q.base[(Q.front+i)%MAXSIZE]<<" ";
            i++;
        }
        cout<<endl;
    }
    else
        cout<<"顺序队为空"<<endl;
}

//----------------------链队--------------------------
typedef struct QNode
{
    int data;//数据域
    struct QNode *next;//指针域
}QNode,*Queueptr;//Queueptr是指向QNode类型的指针

typedef struct
{
    Queueptr front; //队头指针
    Queueptr rear; //队尾指针
}LinkQueue;

//初始化链队
void InitQueue(LinkQueue &Q)
{
    Q.front=Q.rear=new QNode;//生成新节点作为头家电，队头指针队尾指针指向此节点
    if(!Q.front)
        cout<<"存储分配失败！"<<endl;
    else
    {
        Q.front->next=NULL;//头结点的指针域置空
        cout<<"链队初始化成功！"<<endl;
    }
}

//取链队头元素
void GetHead(LinkQueue Q)
{
    if(Q.front!=Q.rear)
        cout<<"链队队头元素为："<<Q.front->next->data<<endl;
    else
        cout<<"当前链队为空"<<endl;
}


//链队的入队操作
void EnQueue(LinkQueue &Q,int e)
{//链队理论上是不会满的，因此不用判队满
    QNode *p=new QNode;
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
    cout<<"入队成功！"<<endl;
}

//链队的出队操作
void DeQueue(LinkQueue &Q,int &e)
{
    if(Q.front==Q.rear)
        cout<<"当前队为空"<<endl;//先判断是否队满
    else
    {
        QNode *p=new QNode;
        p=Q.front->next;
        e=p->data;
        Q.front->next=p->next;//修改队头节点的指针域
        if(Q.rear==p)
            Q.rear=Q.front;//如果是最后一个元素被删除，那么将队尾指针指向队头指针
        delete p;
        cout<<"出队成功！"<<endl;
    }
}

//显示链队元素
void DisplayQ(LinkQueue Q)
{
    QNode *p=Q.front->next;
    if(p)
    {
        while(p)
        {
            cout<<p->data<<" ";
            p=p->next;
        }
        cout<<endl;
    }
    else
        cout<<"链队为空"<<endl;
}

void show()
{
    string s1(40,'*');
    string s2(10,'*');
    cout<<s1<<endl;
    cout<<s2<<left<<setw(20)<<"1.顺序栈入栈"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"2.顺序栈出栈"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"3.取顺序栈栈顶元素"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"4.显示顺序栈元素"<<s2<<endl;

    cout<<s2<<left<<setw(20)<<"5.链栈入栈"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"6.链栈出栈"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"7.取链栈栈顶元素"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"8.显示链栈元素"<<s2<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<s2<<left<<setw(20)<<"9.顺序队入队"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"10.顺序队出队"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"11.取顺序队队头元素"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"12.显示顺序队元素"<<s2<<endl;

    cout<<s2<<left<<setw(20)<<"13.链队入队"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"14.链队出队"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"15.取链队队头元素"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"16.显示链队元素"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"17.退出"<<s2<<endl;
    cout<<s1<<endl;
    cout<<"请输入您的选择：";

}
int main()
{
    SqStack S1;//顺序栈
    LinkStack S2;//链栈
    InitStack(S1); InitStack(S2);

    SqQueue Q1;//顺序队
    LinkQueue Q2;//链队
    InitQueue(Q1); InitQueue(Q2);

    int e,elem;
    show();
    int x;
    cin>>x;
    while(1)
    {
        switch(x)
        {
        case 1:
            cout<<"输入要插入的值：";
            cin>>e;
            Push(S1,e);
            break;
        case 2:
            Pop(S1,elem);
            break;
        case 3:
            GetTop(S1);
            break;
        case 4:
            DisplayS(S1);
            break;
        case 5:
            cout<<"输入要插入的值：";
            cin>>e;
            Push(S2,e);
            break;
        case 6:
            Pop(S2,elem);
            break;
        case 7:
            GetTop(S2);
            break;
        case 8:
            DisplayS(S2);
            break;
        case 9:
            cout<<"输入要插入的值：";
            cin>>e;
            EnQueue(Q1,e);
            break;
        case 10:
            DeQueue(Q1,elem);
            break;
        case 11:
            GetHead(Q1);
            break;
        case 12:
             DisplayQ(Q1);
            break;
        case 13:
            cout<<"输入要插入的值：";
            cin>>e;
            EnQueue(Q2,e);
            break;
        case 14:
            DeQueue(Q2,elem);
            break;
        case 15:
            GetHead(Q2);
            break;
        case 16:
             DisplayQ(Q2);
            break;
        case 17:
            return 0;
        default:
            cout<<"输入不合法！"<<endl;
        }
        cout<<"请输入您的选择：";
        cin>>x;
    }
    return 0;
}
