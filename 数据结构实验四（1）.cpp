#include <iostream>
#include <cstdlib>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int Status;
using namespace std;

//���ö�������ṹ����������
typedef struct BiTNode
{
    char data;//���������
    struct BiTNode *lchild,*rchild;//���Һ���ָ��
}BiTNode,*BiTree;

//����ն�����
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
        CreateBiTree(T->lchild);//����������
        CreateBiTree(T->rchild);//����������
    }
}

//-----------------------˳��ջ---------------------
typedef struct
{
    BiTree *base;//ջ��ָ��
    BiTree *top;//ջ��ָ��
    int stacksize;//ջ���������
}SqStack;

//��ʼ��ջ
Status InitStack(SqStack &S)
{
    S.base=new BiTree[MAXSIZE];
    if(!S.base) exit(OVERFLOW);
    S.top=S.base;//��ʼ��ʱջ��ָ��=ջ��ָ��
    S.stacksize=MAXSIZE;
    return OK;
}

//�ж�ջ�ǿ�
Status isEmpyt(SqStack S)
{
    if(S.top==S.base)//���ջ��ָ��=ջ��ָ�룬ջ��Ϊ��
        return OK;
    else
        return ERROR;
}

//��ջ
Status Push(SqStack &S,BiTree e)
{
    if(S.top-S.base==S.stacksize)//ջ��
        return ERROR;
    *S.top++=e;
    return OK;
}

//��ջ
Status Pop(SqStack &S,BiTree &e)
{
    if(S.base==S.top)//ջ��
        return ERROR;
    e=*--S.top;
    return OK;
}

//---------------------˳���---------------------------
typedef struct
{
    BiTree *base;//����ַ
    int front;//ͷָ��
    int rear;//βָ��
}SqQueue;

//��ʼ����
Status InitQueue(SqQueue &Q)
{
    Q.base=new BiTree[MAXSIZE];
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
Status EnQueue(SqQueue &Q,BiTree e)
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
Status DeQueue(SqQueue &Q,BiTree &e)
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

//���������������
void PreOrderTraverse(BiTree T)
{
    if(T)
    {//�����㲻Ϊ�գ����ո����ҵ�˳�����
        cout<<T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
//������������������ݹ飩
void InOrderTraverserecursive(BiTree T)
{
    if(T)
    {//�����㲻Ϊ�գ���������ҵ�˳�����
        InOrderTraverserecursive(T->lchild);
        cout<<T->data;
        InOrderTraverserecursive(T->rchild);
    }
}

//�������ĺ������
void PostOrderTraverse(BiTree T)
{
    if(T)
    {//�����㲻Ϊ�գ��������Ҹ���˳�����
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout<<T->data;
    }
}

//�ǵݹ��������
void InOrderTraverse(BiTree T)
{
    SqStack S;
    InitStack(S);//��ʼ��ջ
    BiTree p;//p�����ĸ��ڵ�T
    p=T;
    BiTree q=new BiTNode;//q��һ�����ڵ�,�������ջ��������Ԫ��
    while(p || !isEmpyt(S))
    {
        if(p)
        {//���p�ǿգ��ͽ�p��ջ��pָ��������
            Push(S,p);
            p=p->lchild;
        }
        else if(!p)
        {//���pΪ�գ��ͽ�ջ��Ԫ�ص�����ֵ��q�����q��ֵ��pָ��q���Һ���
            Pop(S,q);
            cout<<q->data;
            p=q->rchild;
        }
    }
}

//�������Ĳ������
void cengxu(BiTree T)
{
    SqQueue Q;
    InitQueue(Q);
    BiTree p=T;//p�����ĸ��ڵ�T

    if(p)
    {
        EnQueue(Q,p);//���ڵ����
        while(!QueueEmpty(Q))
        {
            DeQueue(Q,p);//������Ԫ�ط���q
            cout<<p->data;
            if(p->lchild)
                EnQueue(Q,p->lchild);
            if(p->rchild)
                EnQueue(Q,p->rchild);
        }
    }
}

//��������ĸ߶�
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

//���������Ҷ�ӽ�����
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
    cout<<"�밴�����ҵ�˳����������Ԫ�أ�������#���ʾ��ǰ���Ϊ�գ�";
    CreateBiTree(T);
    cout<<"������������";
    PreOrderTraverse(T);
    cout<<endl;
    cout<<"������������";
    PostOrderTraverse(T);
    cout<<endl;
    cout<<"������������"<<endl;
    cout<<"�ݹ�:";
    InOrderTraverserecursive(T);
    cout<<endl;
    cout<<"�ǵݹ�:";
    InOrderTraverse(T);
    cout<<endl;
    cout<<"������������";
    cengxu(T);
    cout<<endl;
    cout<<"������ȣ�";
    cout<<Depth(T)<<endl;
    cout<<"����Ҷ�ӽ�������";
    cout<<LeafCount(T)<<endl;
    return 0;
}
