#include <iostream>
#include <cmath>
#include <cstdlib>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
using namespace std;
//定义顺序表的存储结构
typedef struct
{
    int *elem;
    int length;
}SqList;

//将顺序表初始化
Status InitList(SqList &L)
{
    L.elem=new int[MAXSIZE];//为顺序表分配一个MAXSIZE大小的数组空间
    if(!L.elem)  exit(OVERFLOW);//分配存储后检查是否分配成功，分配失败就退出
    L.length=0; //初始化顺序表时空表长度为0
    return OK;
}
//创建顺序表
Status CreateList(SqList &L)
{
    int a,i=0;
    cin>>a;//输入元素
    while(a!=-1)
    {
        if(L.length==MAXSIZE)//如果线性表的长度已经达到最大值，就返回error
            return ERROR;
        else
        {
            L.elem[i++]=a;
            L.length++;
            cin>>a;
        }
    }
    return OK;
}
//顺序表的清空
void ClearList(SqList &L)
{
    L.length=0;//长度置0即可
}
//顺序表的销毁
void DestoryList(SqList &L)
{
    if(L.elem) delete []L.elem;//删除顺序表的数组空间
    L.length=0;//顺序表置空
    L.elem=NULL;//存储空间基地址置空
}

//判断顺序表是否为空
Status isEmpty(SqList L)
{
    if(L.length==0)
        return OK;//为空返回1
    else
        return ERROR;//不为空返回0
}

//在顺序表指定位置插入元素
Status ListInsert(SqList &L,int i ,int e)
{
    if(i>L.length+1 || i<1) return ERROR;//插入位置不合法
    if(L.length==MAXSIZE) return ERROR;//当前储存空间已满
    for(int j=L.length-1;j>=i-1;j--)
    {//第i个位置之后的元素依次向后移动
        L.elem[j+1]=L.elem[j];
    }
    L.elem[i-1]=e;//在第i个位置上插入元素
    L.length++;//表长度加一
    return OK;
}

//删除顺序表指定位置元素
Status ListDelete(SqList &L,int i,int e)
{
    if(i>L.length||i<1) return ERROR;//插入位置不合法
    if(L.length==0) return ERROR;//当前是空表
    for(int j=i;j<=L.length-1;j++)
    {//i位置之后的元素依次向前移动
        L.elem[j-1]=L.elem[j];
    }
    --L.length;//表长度减一
    return OK;
}

//求两个集合的交集
void Listintersection(SqList &La,SqList &Lb,SqList &Lc)
{
    int i,j,k=0;
    for(i=0;i<La.length;i++)
    {
        j=0;
        while(La.elem[i]!=Lb.elem[j] && j<Lb.length)
        //让表a中的某个元素和表b中的每个元素依次比较，当两元素不等时，让a中的这个元素和b中的下一个元素比较
            j++;
        if(j<Lb.length)
        {//如果跳出while循环时j<Lb.length，说明当前a中元素和b中元素相等
            Lc.elem[k]=Lb.elem[j];
            k++;
        }
    }
    Lc.length=k;//最后循环结束，c表的长度就是k
}

//求两个集合的并集
void mergeList(SqList &La,SqList &Lb,SqList &Lc)
{
    int i,j,k;
    for(i=0;i<La.length;i++)
    //先将a中的所有元素赋给表c
        Lc.elem[i]=La.elem[i];

    k=La.length;//k为Lc的初始长度

    for(i=0;i<Lb.length;i++)
    {
        j=0;
        while(Lb.elem[i]!=La.elem[j] && j<La.length)
        //让b中的某个元素和表a中的每个元素依次比较，当两元素不相等时，
        //让b中的这个元素和a中的下一个元素比较
            j++;
        if(j==La.length)
        //如果跳出while循环时i==La.length，说明当前b中的这个元素和a中的任何一个都不相等
            Lc.elem[k++]=Lb.elem[i];
    }
    Lc.length=k;//最后循环结束，c表的长度就是k
}

//求两个集合的差集
void subtract(SqList &La,SqList &Lb,SqList &Lc)
{
    int i,j,k=0;
    for(i=0;i<La.length;i++)
    {
        j=0;
        while(La.elem[i]!=Lb.elem[j] && j<Lb.length)
        //让表a中的某个元素和表b中的每个元素依次比较，当两元素不相等时，
        //让a中的这个元素和b中的下一个元素比较
            j++;
        if(j==Lb.length)
        //如果跳出while循环时j==Lb.length，说明当前a中的这个元素不在b中
            Lc.elem[k++]=La.elem[i];
    }
    Lc.length=k;//最后循环结束，c表的长度就是k
}

void show()
{
    cout<<"1----清空线性表"<<endl;
    cout<<"2----判断线性表是否为空"<<endl;
    cout<<"3----求线性表长度"<<endl;
    cout<<"4----获取线性表指定位置元素"<<endl;
    cout<<"5----求前驱"<<endl;
    cout<<"6----求后继"<<endl;
    cout<<"7----在线性表指定位置插入元素"<<endl;
    cout<<"8----删除线性表指定位置元素"<<endl;
    cout<<"9----显示线性表"<<endl;
    cout<<"     退出，输入一个负数！"<<endl;
    cout<<"请输入操作码：";
}
int main()
{
/*
//-------------集合的运算------------------------
    SqList L1,L2,L3;
//--------------L1---------------------
    if(InitList(L1)==1)//初始化
        cout<<"初始化成功！"<<endl<<endl;
    else
    {
        cout<<"初始化失败"<<endl<<endl;
        return 0;
    }
    cout<<"请输入线性表中的元素（以-1结束）："<<endl;
    if(CreateList(L1)==1)//创建线性表
        cout<<"创建成功"<<endl<<endl;
    else
    {
        cout<<"创建失败"<<endl<<endl;
        return 0;
    }

//----------------L2----------------------------
    if(InitList(L2)==1)//初始化
        cout<<"初始化成功！"<<endl<<endl;
    else
    {
        cout<<"初始化失败"<<endl<<endl;
        return 0;
    }
    cout<<"请输入线性表中的元素（以-1结束）："<<endl;
    if(CreateList(L2)==1)//创建线性表
        cout<<"创建成功"<<endl<<endl;
    else
    {
        cout<<"创建失败"<<endl<<endl;
        return 0;
    }

//--------------L3------------------------------
    if(InitList(L3)==1)//初始化
        cout<<"初始化成功！"<<endl<<endl;
    else
    {
        cout<<"初始化失败"<<endl<<endl;
        return 0;
    }

    cout<<"交集：";
    Listintersection(L1,L2,L3);
    for(int i=0;i<L3.length;i++)
        cout<<L3.elem[i]<<" ";
    cout<<endl<<endl;

    cout<<"并集：";
    mergeList(L1,L2,L3);
    for(int i=0;i<L3.length;i++)
        cout<<L3.elem[i]<<" ";
    cout<<endl<<endl;

    cout<<"差集：";
    subtract(L1,L2,L3);
    for(int i=0;i<L3.length;i++)
        cout<<L3.elem[i]<<" ";
    cout<<endl<<endl;
*/
    int x;//操作码
    int a;//线性表的某一位置
    int e;//元素
    SqList L;

    cout<<"----------创建顺序表----------"<<endl;
    if(InitList(L)==1)//初始化
        cout<<"初始化成功！"<<endl<<endl;
    else
    {
        cout<<"初始化失败"<<endl<<endl;
        return 0;
    }
    cout<<"请输入线性表中的元素（以-1结束）："<<endl;
    if(CreateList(L)==1)//创建线性表
        cout<<"创建成功"<<endl<<endl;
    else
    {
        cout<<"创建失败"<<endl<<endl;
        return 0;
    }
    show();
    cin>>x;
    while(x>0)
    {
        if(x>10 || x==0)
            cout<<"输入有误，请重新输入！"<<endl<<endl;
        else
        {
            if(x==1)
            {
                cout<<"----------清空顺序表----------"<<endl;
                ClearList(L);
                cout<<"清空成功"<<endl<<endl;
            }
            else if(x==2)
            {
                cout<<"----------判断线性表是否为空----------"<<endl;
                if(isEmpty(L)==1)
                    cout<<"线性表为空"<<endl<<endl;
                else
                    cout<<"线性表不为空"<<endl<<endl;
            }
            else if(x==3)
            {
                cout<<"----------求线性表长度----------"<<endl;
                cout<<"线性表的长度为："<<L.length<<endl<<endl;
            }
            else if(x==4)
            {
                cout<<"----------获取线性表指定位置元素----------"<<endl;
                cout<<"请输入位置：";
                cin>>a;
                if(a<=L.length && a>=1)
                    cout<<L.elem[a-1]<<endl<<endl;
                else
                    cout<<"输入位置有误！"<<endl<<endl;
            }
            else if(x==5)
            {
                cout<<"----------求前驱----------"<<endl;
                cout<<"请输入位置：";
                cin>>a;
                if(a<=L.length && a>1)
                    cout<<L.elem[a-2]<<endl<<endl;
                else
                    cout<<"输入位置有误！"<<endl<<endl;
            }
            else if(x==6)
            {
                cout<<"----------求后继----------"<<endl;
                cout<<"请输入位置：";
                cin>>a;
                if(a<L.length && a>=1)
                    cout<<L.elem[a]<<endl<<endl;
                else
                    cout<<"输入位置有误！"<<endl<<endl;
            }
            else if(x==7)
            {
                cout<<"----------在线性表指定位置插入元素----------"<<endl;
                cout<<"请输入位置：";
                cin>>a;
                cout<<"请输入元素：";
                cin>>e;
                if(ListInsert(L,a,e))
                    cout<<"插入成功"<<endl<<endl;
                else
                    cout<<"插入失败"<<endl<<endl;
            }
            else if(x==8)
            {
                cout<<"----------删除线性表指定位置元素----------"<<endl;
                cout<<"请输入位置：";
                cin>>a;
                if(ListDelete(L,a,e))
                    cout<<"删除成功"<<endl<<endl;
                else
                    cout<<"删除失败"<<endl<<endl;
            }
            else if(x==9)
            {
                for(int i=0;i<L.length;i++)
                    cout<<L.elem[i]<<" ";
                cout<<endl<<endl;
            }
        }
    cout<<"请输入操作码：";
    cin>>x;
    }
    return 0;
}
