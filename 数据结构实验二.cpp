#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <math.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef int Status;
using namespace std;

//定义单链表的存储结构
typedef struct LNode
{
    int data;//数据域
    LNode *next;//指针域
}LNode,*LinkList;  //LnkList为指向LNode类型的指针

//将单链表初始化
Status InitList(LinkList &L)
{
    L=new LNode;
    L->next=NULL;
    return OK;
}

//查找元素在单链表中的位置
void LocateElem(LinkList L,int e)
{
    LNode *p=L->next; //初始化一个指向LNode类型的指针，初始值为链表的首元结点
    int n=1;
    while(p && p->data!=e)
    {
        p=p->next;
        n++;
    }
        if(p)
            cout<<"成功找到，该元素是第"<<n<<"个。";
        else
            cout<<"未找到该元素。";
}

//将元素插入到单链表的第i个位置
Status ListInsert(LinkList &L,int i,int e)
{
    LNode *p=L;
    int j=0;
    while(p && (j<i-1))
    {//找到第i-1个节点的位置
        p=p->next;
        j++;
    }
    if(!p || (j>i-1))
        //cout<<"输入的位置非法"<<endl; //如果跳出循环时p为空或者j>i-1，则出现错误
        return ERROR;
    else
    {
        LNode *s=new LNode; //生成一个新节点
        s->data=e;  //新节点的数据域为要插入的元素
        s->next=p->next; //新节点的指针域为原来的第i个节点
        p->next=s;//p的指针域为插入的新节点
        //cout<<"插入元素成功"<<endl;
        return OK;
    }
}

//创建单链表
Status CreataList(LinkList &L)
{
    int x,i=1;
    cout<<"请输入数据（以9999结束）：";
    cin>>x;
    while(x!=9999)
    {
        ListInsert(L,i,x);
        i++;
        cin>>x;
    }
}


//将单链表第i个位置的元素删除
Status ListDelete(LinkList &L,int i)
{
    LNode *p=L;
    int j=0;
    while((p->next) && j<i-1)
    {//找到第i-1个节点的位置
        p=p->next;
        j++;
    }
    if(!(p->next) || (j>i-1))
      //  cout<<"输入的位置非法"<<endl;//如果跳出循环时p的下一个元素为空或者j>i-1，则出现错误
      return ERROR;
    else
    {
        LNode *s=p->next;//用一个临时节点s存储要删除的节点
        p->next=p->next->next;//改变p的指向
        delete s;//删除这个节点
        //cout<<"删除元素成功"<<endl;
        return OK;
    }
}

//采用单链表结构编程实现两个有序单链表的归并运算
Status mergeList(LinkList &La,LinkList &Lb,LinkList &Lc)
{
	LNode *pa = La->next; //pa和pb分别指向两链表的首元结点
	LNode *pb = Lb->next;
	Lc=La;//初始时让Lc的头指针指向La所指的链表La的头结点
	LNode *pc=Lc;
	while(pa && pb)
    {//当La和Lb的都没有到达表尾时
        if(pa->data <= pb->data)
        {//如果两元素相等或者La的元素较小
            pc->next=pa; //把pa所指结点链接到pc所指结点之后
            pc=pa;       //pc指向pa
            pa=pa->next; //pa指向下一结点
        }
        else
        {//如果链表Lb当前节点的数据较小
            pc->next=pb; //把pb所指结点链接到pc所指结点之后
            pc=pb;       //pc指向pb
            pb=pb->next; //pb指向下一结点
        }
    }
    pc->next=pa?pa:pb;//跳出循环时如果pc->next=pa则说明La非空，就将La剩下的部分链接在Lc后，
    //如果跳出循环时pc->next!=pa就说明Lb非空或者二者都为空，就将Lb剩下的部分链接在Lc后
    return OK;
}

//显示单链表
void Display(LinkList &L)
{
    LNode *p=L->next;  //p是单链表的首元结点
    if(!p)
    {
        cout<<"当前单链表为空"<<endl;
        return;
    }
    while(p)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
}

void show()
{
    string s1(80,'*');
    string s2(20,'*');
    cout<<s1<<endl;
    cout<<s2<<left<<setw(40)<<"1.创建两个非递减的单链表"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"2.查找单链表中的元素"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"3.向单链表中插入元素"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"4.从单链表中删除元素"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"5.实现两个单链表的归并"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"6.显示单链表"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"7.退出"<<s2<<endl;
    cout<<s1<<endl;
    cout<<"请输入您的选择：";
}
int main()
{
    LinkList La,Lb,Lc;
    InitList(La);
    InitList(Lb);
    InitList(Lc);
    char ch;
    int elem,locate;

    show();
    int x;
    cin>>x;
    while(1)
    {
        switch(x)
        {
            case 1:
                CreataList(La);
                CreataList(Lb);
                break;
            case 2:
                cout<<"请输入要进行操作的单链表（a或b）：";
                cin>>ch;
                cout<<"请输入要查找的元素：";
                int elem;
                cin>>elem;
                if(ch=='a')
                    LocateElem(La,elem);
                else if(ch=='b')
                    LocateElem(Lb,elem);
                else
                    cout<<"输入不合法！";
                cout<<endl;
                break;
            case 3:
                cout<<"请输入要进行操作的单链表（a或b）：";
                cin>>ch;
                cout<<"请输入要插入的元素和要插入的位置：";
                cin>>elem>>locate;
                if(ch=='a')
                {
                    int k=ListInsert(La,locate,elem);
                    if(k==1)
                        cout<<"插入成功！"<<endl;
                    else
                        cout<<"插入失败！"<<endl;
                }
                else if(ch=='b')
                {
                    int k=ListInsert(Lb,locate,elem);
                    if(k==1)
                        cout<<"插入成功！"<<endl;
                    else
                        cout<<"插入失败！"<<endl;
                }
                else
                    cout<<"输入不合法！"<<endl;
                break;
            case 4:
                cout<<"请输入要进行操作的单链表（a或b）：";
                char ch;
                cin>>ch;
                cout<<"请输入要删除的元素的位置：";
                cin>>locate;
                if(ch=='a')
                {
                    int k=ListDelete(La,locate);
                    if(k==1)
                        cout<<"删除成功！"<<endl;
                    else
                        cout<<"删除失败！"<<endl;
                }
                else if(ch=='b')
                {
                    int k=ListDelete(Lb,locate);
                    if(k==1)
                        cout<<"删除成功！"<<endl;
                    else
                        cout<<"删除失败！"<<endl;
                }
                else
                    cout<<"输入不合法！"<<endl;
                break;
            case 5:
                mergeList(La,Lb,Lc);
                cout<<"单链表c的元素为：";
                Display(Lc);
                cout<<endl;
                break;
            case 6:
                cout<<"单链表a的元素为：";
                Display(La);
                cout<<endl;
                cout<<"单链表b的元素为：";
                Display(Lb);
                cout<<endl;
                break;
            case 7:
                return 0;
            default:
                cout<<"输入不合法！";
                break;
        }
        cout<<endl;
        cout<<"请输入您的选择：";
        cin>>x;
    }
    return 0;
}
