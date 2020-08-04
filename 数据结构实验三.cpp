#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2

using namespace std;

//---------------------˳��ջ-------------------------
typedef struct
{//ջ��˳��洢�ṹ
    int *base;//ջ��ָ��
    int *top;//ջ��ָ��
    int stacksize;//ջ���õ��������
}SqStack;

//��ʼ��˳��ջ
void InitStack(SqStack &S)
{
    S.base=new int[MAXSIZE];//Ϊջ��̬����һ��MAXSIZE����������
    if(!S.base)
        cout<<"�洢����ʧ��"<<endl;
    else
    {
        S.top=S.base;//ջ��ָ���ʼ��Ϊ��ջ��ָ����ͬ
        S.stacksize=MAXSIZE;//ջ���������
        cout<<"˳��ջ��ʼ���ɹ���"<<endl;
    }
}

//ȡ˳��ջ��ջ��Ԫ��
void GetTop(SqStack S)
{
    if(S.top!=S.base)//���ջ�ǿ�
        cout<<"˳��ջջ��Ԫ��Ϊ��" <<*(S.top-1)<<endl;//���ջ��ָ����ָ����һ��Ԫ��
    else
        cout<<"��ǰջΪ��ջ"<<endl;
}

//˳��ջ����ջ����
void Push(SqStack &S,int e)
{
    if(S.top-S.base==MAXSIZE)
        cout<<"��ǰջ����"<<endl;//����ջ��
    else
    {
        *S.top++=e;//�ȼӺ�ѹ
        cout<<"��ջ�ɹ���"<<endl;
    }
}

//˳��ջ�ĳ�ջ����
void Pop(SqStack &S ,int &e)
{
    if(S.top==S.base)
        cout<<"��ǰջΪ��"<<endl;//�����Ƿ�ջ��
    else
    {
        e=*--S.top;//�ȼ���
        cout<<"��ջ�ɹ���"<<endl;
    }
}

//��ʾ˳��ջԪ��
void DisplayS(SqStack S)
{
    if(S.top==S.base)
        cout<<"��ǰջΪ��ջ"<<endl;
    else
    {
        cout<<"ջ��Ԫ��Ϊ";
        while(S.top!=S.base)
            cout<<*--S.top<<" ";
        cout<<endl;
    }
}

//---------------------��ջ-------------------------
typedef struct StackNode
{
    int data;//������
    struct StackNode *next;//ָ����
}StackNode ,*LinkStack;//LinkStackΪָ��ṹ��StackNode���͵�ָ��

//��ʼ����ջ
void InitStack(LinkStack &S)
{
    S=NULL;//����һ����ջ��ջ��ָ���ÿ�
    cout<<"��ջ��ʼ���ɹ���"<<endl;
}

//��ջ����ջ����
void Push(LinkStack &S,int e)
{//��ջ�������ǲ������ģ���˲�����ջ��
    StackNode *p=new StackNode;//�����µĽڵ�
    p->data=e;
    p->next=S;
    S=p;
    cout<<"��ջ�ɹ���"<<endl;
}

//��ջ�ĳ�ջ����
void Pop(LinkStack &S,int &e)
{
    if(S==NULL)
        cout<<"��ǰջΪ��"<<endl;//�����Ƿ�ջ��
    StackNode *p=new StackNode;
    p=S;
    e=S->data;
    S=S->next;
    delete p;//�ͷ�ջ��Ԫ�صĿռ�
    cout<<"��ջ�ɹ���"<<endl;
}

//��ջȡջ��Ԫ��
void GetTop(LinkStack S)
{
    if(S->next == NULL)
        cout<<"��ջջ��Ԫ��Ϊ��"<<S->data<<endl;
    else
        cout<<"��ǰջΪ��ջ"<<endl;
}

//��ʾ��ջԪ��
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

//----------------------˳���-------------------------
typedef struct
{//���е�˳��洢�ṹ
    int *base;//�洢�ռ����ַ
    int front;//ͷָ��
    int rear;//βָ��
}SqQueue;

//��ʼ��˳���
void InitQueue(SqQueue &Q)
{
    Q.base=new int[MAXSIZE];//Ϊ���ж�̬����һ��MAXSIZE����������
    if(!Q.base)
        cout<<"�洢����ʧ��"<<endl;//�ж��Ƿ����ɹ�
    else
    {
        Q.front=Q.rear=0;//��ʼ��ʱͷβָ���ָ����
        cout<<"˳��ӳ�ʼ���ɹ���"<<endl;
    }
}

//ȡ˳��ӵĶ�ͷԪ��
void GetHead(SqQueue Q)
{
    if(Q.front==Q.rear)
        cout<<"��ǰ˳���Ϊ��"<<endl;//���ж��Ƿ�ӿ�
    else
    cout<<"˳��Ӷ�ͷԪ��Ϊ��"<<Q.base[Q.front]<<endl;
}

//˳��ӵ���Ӳ���
void EnQueue(SqQueue &Q,int e)
{
    if((Q.rear+1)%MAXSIZE==Q.front)
        cout<<"��ǰ������"<<endl;//���ж��Ƿ����
    else
    {
        Q.base[Q.rear]=e;
        Q.rear=(Q.rear+1)%MAXSIZE;
        cout<<"��ӳɹ���"<<endl;
    }
}

//˳��ӵĳ��Ӳ���
void DeQueue(SqQueue &Q,int &e)
{
    if(Q.front==Q.rear)
        cout<<"��ǰ��Ϊ��"<<endl;//���ж��Ƿ�ӿ�
    else
    {
        e=Q.base[Q.front];
        Q.front=(Q.front+1)%MAXSIZE;
        cout<<"���ӳɹ���"<<endl;
    }
}

//��ʾ˳���Ԫ��
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
        cout<<"˳���Ϊ��"<<endl;
}

//----------------------����--------------------------
typedef struct QNode
{
    int data;//������
    struct QNode *next;//ָ����
}QNode,*Queueptr;//Queueptr��ָ��QNode���͵�ָ��

typedef struct
{
    Queueptr front; //��ͷָ��
    Queueptr rear; //��βָ��
}LinkQueue;

//��ʼ������
void InitQueue(LinkQueue &Q)
{
    Q.front=Q.rear=new QNode;//�����½ڵ���Ϊͷ�ҵ磬��ͷָ���βָ��ָ��˽ڵ�
    if(!Q.front)
        cout<<"�洢����ʧ�ܣ�"<<endl;
    else
    {
        Q.front->next=NULL;//ͷ����ָ�����ÿ�
        cout<<"���ӳ�ʼ���ɹ���"<<endl;
    }
}

//ȡ����ͷԪ��
void GetHead(LinkQueue Q)
{
    if(Q.front!=Q.rear)
        cout<<"���Ӷ�ͷԪ��Ϊ��"<<Q.front->next->data<<endl;
    else
        cout<<"��ǰ����Ϊ��"<<endl;
}


//���ӵ���Ӳ���
void EnQueue(LinkQueue &Q,int e)
{//�����������ǲ������ģ���˲����ж���
    QNode *p=new QNode;
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
    cout<<"��ӳɹ���"<<endl;
}

//���ӵĳ��Ӳ���
void DeQueue(LinkQueue &Q,int &e)
{
    if(Q.front==Q.rear)
        cout<<"��ǰ��Ϊ��"<<endl;//���ж��Ƿ����
    else
    {
        QNode *p=new QNode;
        p=Q.front->next;
        e=p->data;
        Q.front->next=p->next;//�޸Ķ�ͷ�ڵ��ָ����
        if(Q.rear==p)
            Q.rear=Q.front;//��������һ��Ԫ�ر�ɾ������ô����βָ��ָ���ͷָ��
        delete p;
        cout<<"���ӳɹ���"<<endl;
    }
}

//��ʾ����Ԫ��
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
        cout<<"����Ϊ��"<<endl;
}

void show()
{
    string s1(40,'*');
    string s2(10,'*');
    cout<<s1<<endl;
    cout<<s2<<left<<setw(20)<<"1.˳��ջ��ջ"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"2.˳��ջ��ջ"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"3.ȡ˳��ջջ��Ԫ��"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"4.��ʾ˳��ջԪ��"<<s2<<endl;

    cout<<s2<<left<<setw(20)<<"5.��ջ��ջ"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"6.��ջ��ջ"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"7.ȡ��ջջ��Ԫ��"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"8.��ʾ��ջԪ��"<<s2<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<s2<<left<<setw(20)<<"9.˳������"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"10.˳��ӳ���"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"11.ȡ˳��Ӷ�ͷԪ��"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"12.��ʾ˳���Ԫ��"<<s2<<endl;

    cout<<s2<<left<<setw(20)<<"13.�������"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"14.���ӳ���"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"15.ȡ���Ӷ�ͷԪ��"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"16.��ʾ����Ԫ��"<<s2<<endl;
    cout<<s2<<left<<setw(20)<<"17.�˳�"<<s2<<endl;
    cout<<s1<<endl;
    cout<<"����������ѡ��";

}
int main()
{
    SqStack S1;//˳��ջ
    LinkStack S2;//��ջ
    InitStack(S1); InitStack(S2);

    SqQueue Q1;//˳���
    LinkQueue Q2;//����
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
            cout<<"����Ҫ�����ֵ��";
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
            cout<<"����Ҫ�����ֵ��";
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
            cout<<"����Ҫ�����ֵ��";
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
            cout<<"����Ҫ�����ֵ��";
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
            cout<<"���벻�Ϸ���"<<endl;
        }
        cout<<"����������ѡ��";
        cin>>x;
    }
    return 0;
}
