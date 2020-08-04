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
int m=0; //������¼�����������Ĳ��Ҵ���
int k=-1;//�����������ĳ�ʼ������
typedef struct
{
    int key;
}ElemType;

//-----------------�۰����---------------------
//˳���
typedef struct
{
    ElemType *R;       //�洢�ռ����ַ
    int length;   //��ǰ����
}SSTable;

//����˳���
void CreateList(SSTable &ST)
{
    ST.R=new ElemType[MAXSIZE];
    if(!ST.R)
        exit(OVERFLOW);
    ST.length=12;
    int a[12]={1,15,20,26,30,37,45,52,61,68,79,81};
    cout<<"�������Ա����ɹ�������ֵΪ:";
    for(int i=1;i<=ST.length;i++)    //0�ŵ�Ԫ�ճ������±�1��ʼ�洢
    {
        ST.R[i].key=a[i-1];    //���ó�ʼ˳�����ֵ
        cout<<ST.R[i].key<<" ";
    }
    cout<<endl;
}

//�������ST�в���Ԫ��key��λ��
void Search_Bin(SSTable ST,int key)
{
    int low=1,high=ST.length,mid;  //0�ŵ�Ԫ��ʹ�ã�low��1��ʼ
    int n=0;//���Ҵ���
    bool isHave=false;//������¼�Ƿ���ҵ�
    while(low<=high)
    {
        mid=(low+high)/2;
        n++;
        if(key==ST.R[mid].key)
        {
            cout<<"Ԫ��"<<key<<"Ϊ��"<<mid<<"��Ԫ��,��������"<<n<<"��"<<endl;
            isHave=true;
            break;
        }
        else if(key<ST.R[mid].key)
            high=mid-1;
        else
            low=mid+1;
    }
    if(!isHave)
        cout<<"Ԫ��"<<key<<"����������У���������"<<n<<"��"<<endl;
}
//----------------����������------------------
//��������洢��ʾ
typedef struct
{
    string key;
    int position;   //���λ��
}ElemType1;

typedef struct BSTNode
{
    ElemType1 data;           //������
    struct BSTNode *lchild,*rchild;  //���Һ���ָ��
}BSTNode,*BSTree;


//��������������
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
        CreateBST(T->lchild);    //�ݹ鴴��������
        CreateBST(T->rchild);    //�ݹ鴴��������
    }
}

//�������
void InOrderTraverse(BSTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild); //�������������
        cout<<T->data.key<<" ";     //���ʸ��ڵ�
        T->data.position=m;         //����������Ϊ����position����ֵ
        m++;
        InOrderTraverse(T->rchild); //�������������
    }
}

//�ڸ�ָ��T��ָ�����������еݹ�Ĳ���ĳ�ؼ��ֵ���key��Ԫ�أ�
//���ҳɹ��򷵻�ָ�������Ԫ�ؽڵ��ָ�룬���򷵻ؿ�ָ��
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

//------------------˳�����-----------------------
void Search_Seq(SSTable ST,int key)
{
    bool isHave=false;//������¼�Ƿ���ҵ�
    for(int i=ST.length;i>=1;i--)
    {
        if(ST.R[i].key==key)
        {
            cout<<"Ԫ��"<<key<<"Ϊ��"<<i<<"��Ԫ��,��������"<<i<<"��"<<endl;
            isHave=true;
            break;
        }
    }
    if(!isHave)
        cout<<"Ԫ��"<<key<<"�����������,��������"<<ST.length<<"��"<<endl;
}

//------------------�ֿ����----------------------
//�������������������˳���
void CreateList1(SSTable &ST)
{
    ST.R=new ElemType[MAXSIZE];
    if(!ST.R)
        exit(OVERFLOW);
    ST.length=18;
    int a[18]={22,12,13,8,9,20,33,42,44,38,24,48,60,58,74,49,86,53};
    cout<<"�������Ա����ɹ�������ֵΪ:";
    for(int i=1;i<=ST.length;i++)    //0�ŵ�Ԫ�ճ������±�1��ʼ�洢
    {
        ST.R[i].key=a[i-1];    //���ó�ʼ˳�����ֵ
        cout<<ST.R[i].key<<" ";
    }
    cout<<endl;
}

//������
typedef struct IndexType
{
    int key;
    int link;       //ָ��ֿ����ʼ�±�
}IDX[MAXSIZE];

void IdxSearch(IDX I,int m,SSTable ST,int key)    //�ֿ�����㷨
{//m�ǿ������n��˳���ĳ���
    int n=ST.length;

    //count1Ϊ�ۼ����������еıȽϴ�����count2Ϊ�ۼ���˳����Ӧ���еıȽϴ���
    int low=0,high=m-1,mid,i,count1=0,count2=0;

    int b=n/m;              //bΪ���С

    //���������н����۰����,�ҵ���λ�ô����low��
    while(low<=high)
    {
        mid=(low+high)/2;
        count1++;
        if(I[mid].key>=key)
            high=mid-1;
        else
            low=mid+1;
    }
    if(low<m)              //���������в��ҳɹ���,�������Ա��н���˳�����
    {
        i=I[low].link;
        while(i<=I[low].link+b-1 && ST.R[i].key!=key)
        {
            i++;
            count2++;
        }
        if (i<=I[low].link+b-1)
        {
            cout<<"Ԫ��"<<key<<"Ϊ��"<<i<<"��Ԫ��,��������"<<count1+count2<<"��"<<endl;
        }
        else
            cout<<"Ԫ��"<<key<<"�����������,��������"<<count1+count2<<"��"<<endl;
    }
    else
        cout<<"Ԫ��"<<key<<"�����������,��������"<<count1+count2<<"��"<<endl;
}

void show()
{
    string s1(80,'*');
    string s2(20,'*');
    cout<<s1<<endl;
    cout<<s2<<left<<setw(40)<<"1.�����������Ա�"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"2.����������������������Ա�"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"3.��������������"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"4.�۰����"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"5.��������������"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"6.�ֿ����"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"7.˳�����"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"8.�˳�"<<s2<<endl;
    cout<<s1<<endl;
    cout<<"����������ѡ��";

}
int main()
{
    SSTable ST,ST1; //˳���
    BSTree T;  //����������
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
                cout<<"�����ɹ���"<<endl;
                cout<<"����������Ϊ��";
                InOrderTraverse(T);
                cout<<endl;
                break;
            case 4:
                cout<<"������Ҫ���ҵ�Ԫ�أ�";
                cin>>key;
                Search_Bin(ST,key);
                cout<<endl;
                break;
            case 5:
                cout<<"������Ҫ���ҵ�Ԫ�أ�";
                cin>>key1;
                m=0;
                if(!SearchBST(T,key1))
                    cout<<"Ԫ��"<<key1<<"����������У���������"<<m<<"��"<<endl;
                else
                    cout<<"�������������˳�������Ԫ��"<<key1<<"Ϊ��"<<SearchBST(T,key1)->data.position+1<<"��Ԫ�أ���������"<<m<<"��"<<endl;
                cout<<endl;
                break;
            case 6:
                cout<<"������Ҫ���ҵ�Ԫ�أ�";
                cin>>key;
                I[0].key=22;I[0].link=1;
                I[1].key=48;I[1].link=7;
                I[2].key=86;I[2].link=13;
                IdxSearch(I,3,ST1,key);
                cout<<endl;
                break;
            case 7:
                cout<<"������Ҫ���ҵ�Ԫ�أ�";
                cin>>key;
                Search_Seq(ST,key);
                cout<<endl;
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
