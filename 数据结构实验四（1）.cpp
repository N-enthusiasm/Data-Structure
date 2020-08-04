#include <iostream>
#include <cstdlib>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int Status;
using namespace std;

//采用二叉链表结构建立二叉树
typedef struct BiTNode
{
    char data;//结点数据域
    struct BiTNode *lchild,*rchild;//左右孩子指针
}BiTNode,*BiTree;

//构造空二叉树
void InitBiTree(BiTree &T)
{
    T=new BiTNode;
    T->lchild=T->rchild=NULL;
    T->data = '#';
}

void CreateBiTree(BiTree &T)
{
    char x;
    cin>>x;
    if(x=='#')
        T=NULL;
    else
    {
        T=new BiTNode;
        T->data=x;
        CreateBiTree(T->lchild);//建立左子树
        CreateBiTree(T->rchild);//建立右子树
    }
}

//-----------------------顺序栈---------------------
typedef struct
{
    BiTree *base;//栈底指针
    BiTree *top;//栈顶指针
    int stacksize;//栈的最大容量
}SqStack;

//初始化栈
Status InitStack(SqStack &S)
{
    S.base=new BiTree[MAXSIZE];
    if(!S.base) exit(OVERFLOW);
    S.top=S.base;//初始化时栈顶指针=栈底指针
    S.stacksize=MAXSIZE;
    return OK;
}

//判断栈非空
Status isEmpyt(SqStack S)
{
    if(S.top==S.base)//如果栈顶指针=栈底指针，栈就为空
        return OK;
    else
        return ERROR;
}

//入栈
Status Push(SqStack &S,BiTree e)
{
    if(S.top-S.base==S.stacksize)//栈满
        return ERROR;
    *S.top++=e;
    return OK;
}

//出栈
Status Pop(SqStack &S,BiTree &e)
{
    if(S.base==S.top)//栈空
        return ERROR;
    e=*--S.top;
    return OK;
}

//---------------------顺序队---------------------------
typedef struct
{
    BiTree *base;//基地址
    int front;//头指针
    int rear;//尾指针
}SqQueue;

//初始化队
Status InitQueue(SqQueue &Q)
{
    Q.base=new BiTree[MAXSIZE];
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
Status EnQueue(SqQueue &Q,BiTree e)
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
Status DeQueue(SqQueue &Q,BiTree &e)
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

//二叉树的先序遍历
void PreOrderTraverse(BiTree T)
{
    if(T)
    {//如果结点不为空，按照根左右的顺序访问
        cout<<T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
//二叉树的中序遍历（递归）
void InOrderTraverserecursive(BiTree T)
{
    if(T)
    {//如果结点不为空，按照左根右的顺序访问
        InOrderTraverserecursive(T->lchild);
        cout<<T->data;
        InOrderTraverserecursive(T->rchild);
    }
}

//二叉树的后序遍历
void PostOrderTraverse(BiTree T)
{
    if(T)
    {//如果结点不为空，按照左右根的顺序访问
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout<<T->data;
    }
}

//非递归中序遍历
void InOrderTraverse(BiTree T)
{
    SqStack S;
    InitStack(S);//初始化栈
    BiTree p;//p是树的根节点T
    p=T;
    BiTree q=new BiTNode;//q是一个树节点,用来存放栈顶弹出的元素
    while(p || !isEmpyt(S))
    {
        if(p)
        {//如果p非空，就将p入栈，p指向其左孩子
            Push(S,p);
            p=p->lchild;
        }
        else if(!p)
        {//如果p为空，就将栈顶元素弹出赋值给q，输出q的值，p指向q的右孩子
            Pop(S,q);
            cout<<q->data;
            p=q->rchild;
        }
    }
}

//二叉树的层序遍历
void cengxu(BiTree T)
{
    SqQueue Q;
    InitQueue(Q);
    BiTree p=T;//p是树的根节点T

    if(p)
    {
        EnQueue(Q,p);//根节点进队
        while(!QueueEmpty(Q))
        {
            DeQueue(Q,p);//弹出的元素放在q
            cout<<p->data;
            if(p->lchild)
                EnQueue(Q,p->lchild);
            if(p->rchild)
                EnQueue(Q,p->rchild);
        }
    }
}

//求二叉树的高度
int Depth(BiTree T)
{
    if(T==NULL) return ERROR;
    else
    {
        int m=Depth(T->lchild);
        int n=Depth(T->rchild);
        if(m>n)
            return m+1;
        else
            return n+1;
    }
}

//求二叉树的叶子结点个数
int LeafCount(BiTree T)
{
    if(T==NULL) return ERROR;
    else
    {
        if(T->lchild==NULL && T->rchild==NULL)
            return 1;
        else
            return LeafCount(T->lchild)+LeafCount(T->rchild);
    }
}
int main()
{
    BiTree T;
    cout<<"请按根左右的顺序输入树中元素：（输入#则表示当前结点为空）";
    CreateBiTree(T);
    cout<<"先序遍历结果：";
    PreOrderTraverse(T);
    cout<<endl;
    cout<<"后序遍历结果：";
    PostOrderTraverse(T);
    cout<<endl;
    cout<<"中序遍历结果："<<endl;
    cout<<"递归:";
    InOrderTraverserecursive(T);
    cout<<endl;
    cout<<"非递归:";
    InOrderTraverse(T);
    cout<<endl;
    cout<<"层序遍历结果：";
    cengxu(T);
    cout<<endl;
    cout<<"树的深度：";
    cout<<Depth(T)<<endl;
    cout<<"树的叶子结点个数：";
    cout<<LeafCount(T)<<endl;
    return 0;
}
