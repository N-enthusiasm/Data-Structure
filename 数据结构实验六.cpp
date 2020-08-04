#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int Status;
using namespace std;
int m=0; //用来记录二叉排序树的查找次数
int k=-1;//二叉排序树的初始化计数
typedef struct
{
    int key;
}ElemType;

//-----------------折半查找---------------------
//顺序表
typedef struct
{
    ElemType *R;       //存储空间基地址
    int length;   //当前长度
}SSTable;

//创建顺序表
void CreateList(SSTable &ST)
{
    ST.R=new ElemType[MAXSIZE];
    if(!ST.R)
        exit(OVERFLOW);
    ST.length=12;
    int a[12]={1,15,20,26,30,37,45,52,61,68,79,81};
    cout<<"有序线性表创建成功，其数值为:";
    for(int i=1;i<=ST.length;i++)    //0号单元空出，从下标1开始存储
    {
        ST.R[i].key=a[i-1];    //设置初始顺序表数值
        cout<<ST.R[i].key<<" ";
    }
    cout<<endl;
}

//在有序表ST中查找元素key的位置
void Search_Bin(SSTable ST,int key)
{
    int low=1,high=ST.length,mid;  //0号单元不使用，low从1开始
    int n=0;//查找次数
    bool isHave=false;//用来记录是否查找到
    while(low<=high)
    {
        mid=(low+high)/2;
        n++;
        if(key==ST.R[mid].key)
        {
            cout<<"元素"<<key<<"为第"<<mid<<"个元素,共查找了"<<n<<"次"<<endl;
            isHave=true;
            break;
        }
        else if(key<ST.R[mid].key)
            high=mid-1;
        else
            low=mid+1;
    }
    if(!isHave)
        cout<<"元素"<<key<<"不在有序表中，共查找了"<<n<<"次"<<endl;
}
//----------------二叉排序树------------------
//二叉链表存储表示
typedef struct
{
    string key;
    int position;   //结点位置
}ElemType1;

typedef struct BSTNode
{
    ElemType1 data;           //数据域
    struct BSTNode *lchild,*rchild;  //左右孩子指针
}BSTNode,*BSTree;


//创建二叉排序树
void CreateBST(BSTree &T)
{
    string ch[13]={"46","22","12","#","#","35","#","#","50","#","90","#","#"};
    k+=1;
    if(ch[k]=="#")
        T=NULL;
    else
    {
        T=new BSTNode;
        T->data.key=ch[k];
        CreateBST(T->lchild);    //递归创建左子树
        CreateBST(T->rchild);    //递归创建右子树
    }
}

//中序遍历
void InOrderTraverse(BSTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild); //中序遍历左子树
        cout<<T->data.key<<" ";     //访问根节点
        T->data.position=m;         //遍历过后能为结点的position赋初值
        m++;
        InOrderTraverse(T->rchild); //中序遍历右子树
    }
}

//在根指针T所指二叉排序树中递归的查找某关键字等于key的元素，
//查找成功则返回指向该数据元素节点的指针，否则返回空指针
BSTree SearchBST(BSTree T,string key)
{
    m++;
    if((!T)|| key==T->data.key)
        return T;
    else if(key<T->data.key)
        return SearchBST(T->lchild,key);
    else
        return SearchBST(T->rchild,key);
}

//------------------顺序查找-----------------------
void Search_Seq(SSTable ST,int key)
{
    bool isHave=false;//用来记录是否查找到
    for(int i=ST.length;i>=1;i--)
    {
        if(ST.R[i].key==key)
        {
            cout<<"元素"<<key<<"为第"<<i<<"个元素,共查找了"<<i<<"次"<<endl;
            isHave=true;
            break;
        }
    }
    if(!isHave)
        cout<<"元素"<<key<<"不在有序表中,共查找了"<<ST.length<<"次"<<endl;
}

//------------------分块查找----------------------
//创建块间有序块内无序的顺序表
void CreateList1(SSTable &ST)
{
    ST.R=new ElemType[MAXSIZE];
    if(!ST.R)
        exit(OVERFLOW);
    ST.length=18;
    int a[18]={22,12,13,8,9,20,33,42,44,38,24,48,60,58,74,49,86,53};
    cout<<"有序线性表创建成功，其数值为:";
    for(int i=1;i<=ST.length;i++)    //0号单元空出，从下标1开始存储
    {
        ST.R[i].key=a[i-1];    //设置初始顺序表数值
        cout<<ST.R[i].key<<" ";
    }
    cout<<endl;
}

//索引表
typedef struct IndexType
{
    int key;
    int link;       //指向分块的起始下标
}IDX[MAXSIZE];

void IdxSearch(IDX I,int m,SSTable ST,int key)    //分块查找算法
{//m是块个数，n是顺序表的长度
    int n=ST.length;

    //count1为累计在索引表中的比较次数，count2为累计在顺序表对应块中的比较次数
    int low=0,high=m-1,mid,i,count1=0,count2=0;

    int b=n/m;              //b为块大小

    //在索引表中进行折半查找,找到的位置存放在low中
    while(low<=high)
    {
        mid=(low+high)/2;
        count1++;
        if(I[mid].key>=key)
            high=mid-1;
        else
            low=mid+1;
    }
    if(low<m)              //在索引表中查找成功后,再在线性表中进行顺序查找
    {
        i=I[low].link;
        while(i<=I[low].link+b-1 && ST.R[i].key!=key)
        {
            i++;
            count2++;
        }
        if (i<=I[low].link+b-1)
        {
            cout<<"元素"<<key<<"为第"<<i<<"个元素,共查找了"<<count1+count2<<"次"<<endl;
        }
        else
            cout<<"元素"<<key<<"不在有序表中,共查找了"<<count1+count2<<"次"<<endl;
    }
    else
        cout<<"元素"<<key<<"不在有序表中,共查找了"<<count1+count2<<"次"<<endl;
}

void show()
{
    string s1(80,'*');
    string s2(20,'*');
    cout<<s1<<endl;
    cout<<s2<<left<<setw(40)<<"1.创建有序线性表"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"2.创建块间有序块内无序的线性表"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"3.创建二叉排序树"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"4.折半查找"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"5.二叉排序树查找"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"6.分块查找"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"7.顺序查找"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"8.退出"<<s2<<endl;
    cout<<s1<<endl;
    cout<<"请输入您的选择：";

}
int main()
{
    SSTable ST,ST1; //顺序表
    BSTree T;  //二叉排序树
    IDX I;
    int key;
    string key1;

    show();
    int x;
    cin>>x;
    while(1)
    {
        switch(x)
        {
            case 1:
                CreateList(ST);
                cout<<endl;
                break;
            case 2:
                CreateList1(ST1);
                cout<<endl;
                break;
            case 3:
                CreateBST(T);
                cout<<"创建成功！"<<endl;
                cout<<"中序遍历结果为：";
                InOrderTraverse(T);
                cout<<endl;
                break;
            case 4:
                cout<<"请输入要查找的元素：";
                cin>>key;
                Search_Bin(ST,key);
                cout<<endl;
                break;
            case 5:
                cout<<"请输入要查找的元素：";
                cin>>key1;
                m=0;
                if(!SearchBST(T,key1))
                    cout<<"元素"<<key1<<"不在有序表中，共查找了"<<m<<"次"<<endl;
                else
                    cout<<"按照中序遍历的顺序排序后，元素"<<key1<<"为第"<<SearchBST(T,key1)->data.position+1<<"个元素，共查找了"<<m<<"次"<<endl;
                cout<<endl;
                break;
            case 6:
                cout<<"请输入要查找的元素：";
                cin>>key;
                I[0].key=22;I[0].link=1;
                I[1].key=48;I[1].link=7;
                I[2].key=86;I[2].link=13;
                IdxSearch(I,3,ST1,key);
                cout<<endl;
                break;
            case 7:
                cout<<"请输入要查找的元素：";
                cin>>key;
                Search_Seq(ST,key);
                cout<<endl;
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
