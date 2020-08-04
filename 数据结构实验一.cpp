#include <iostream>
#include <cmath>
#include <cstdlib>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
using namespace std;
//����˳���Ĵ洢�ṹ
typedef struct
{
    int *elem;
    int length;
}SqList;

//��˳����ʼ��
Status InitList(SqList &L)
{
    L.elem=new int[MAXSIZE];//Ϊ˳������һ��MAXSIZE��С������ռ�
    if(!L.elem)  exit(OVERFLOW);//����洢�����Ƿ����ɹ�������ʧ�ܾ��˳�
    L.length=0; //��ʼ��˳���ʱ�ձ���Ϊ0
    return OK;
}
//����˳���
Status CreateList(SqList &L)
{
    int a,i=0;
    cin>>a;//����Ԫ��
    while(a!=-1)
    {
        if(L.length==MAXSIZE)//������Ա�ĳ����Ѿ��ﵽ���ֵ���ͷ���error
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
//˳�������
void ClearList(SqList &L)
{
    L.length=0;//������0����
}
//˳��������
void DestoryList(SqList &L)
{
    if(L.elem) delete []L.elem;//ɾ��˳��������ռ�
    L.length=0;//˳����ÿ�
    L.elem=NULL;//�洢�ռ����ַ�ÿ�
}

//�ж�˳����Ƿ�Ϊ��
Status isEmpty(SqList L)
{
    if(L.length==0)
        return OK;//Ϊ�շ���1
    else
        return ERROR;//��Ϊ�շ���0
}

//��˳���ָ��λ�ò���Ԫ��
Status ListInsert(SqList &L,int i ,int e)
{
    if(i>L.length+1 || i<1) return ERROR;//����λ�ò��Ϸ�
    if(L.length==MAXSIZE) return ERROR;//��ǰ����ռ�����
    for(int j=L.length-1;j>=i-1;j--)
    {//��i��λ��֮���Ԫ����������ƶ�
        L.elem[j+1]=L.elem[j];
    }
    L.elem[i-1]=e;//�ڵ�i��λ���ϲ���Ԫ��
    L.length++;//���ȼ�һ
    return OK;
}

//ɾ��˳���ָ��λ��Ԫ��
Status ListDelete(SqList &L,int i,int e)
{
    if(i>L.length||i<1) return ERROR;//����λ�ò��Ϸ�
    if(L.length==0) return ERROR;//��ǰ�ǿձ�
    for(int j=i;j<=L.length-1;j++)
    {//iλ��֮���Ԫ��������ǰ�ƶ�
        L.elem[j-1]=L.elem[j];
    }
    --L.length;//���ȼ�һ
    return OK;
}

//���������ϵĽ���
void Listintersection(SqList &La,SqList &Lb,SqList &Lc)
{
    int i,j,k=0;
    for(i=0;i<La.length;i++)
    {
        j=0;
        while(La.elem[i]!=Lb.elem[j] && j<Lb.length)
        //�ñ�a�е�ĳ��Ԫ�غͱ�b�е�ÿ��Ԫ�����αȽϣ�����Ԫ�ز���ʱ����a�е����Ԫ�غ�b�е���һ��Ԫ�رȽ�
            j++;
        if(j<Lb.length)
        {//�������whileѭ��ʱj<Lb.length��˵����ǰa��Ԫ�غ�b��Ԫ�����
            Lc.elem[k]=Lb.elem[j];
            k++;
        }
    }
    Lc.length=k;//���ѭ��������c��ĳ��Ⱦ���k
}

//���������ϵĲ���
void mergeList(SqList &La,SqList &Lb,SqList &Lc)
{
    int i,j,k;
    for(i=0;i<La.length;i++)
    //�Ƚ�a�е�����Ԫ�ظ�����c
        Lc.elem[i]=La.elem[i];

    k=La.length;//kΪLc�ĳ�ʼ����

    for(i=0;i<Lb.length;i++)
    {
        j=0;
        while(Lb.elem[i]!=La.elem[j] && j<La.length)
        //��b�е�ĳ��Ԫ�غͱ�a�е�ÿ��Ԫ�����αȽϣ�����Ԫ�ز����ʱ��
        //��b�е����Ԫ�غ�a�е���һ��Ԫ�رȽ�
            j++;
        if(j==La.length)
        //�������whileѭ��ʱi==La.length��˵����ǰb�е����Ԫ�غ�a�е��κ�һ���������
            Lc.elem[k++]=Lb.elem[i];
    }
    Lc.length=k;//���ѭ��������c��ĳ��Ⱦ���k
}

//���������ϵĲ
void subtract(SqList &La,SqList &Lb,SqList &Lc)
{
    int i,j,k=0;
    for(i=0;i<La.length;i++)
    {
        j=0;
        while(La.elem[i]!=Lb.elem[j] && j<Lb.length)
        //�ñ�a�е�ĳ��Ԫ�غͱ�b�е�ÿ��Ԫ�����αȽϣ�����Ԫ�ز����ʱ��
        //��a�е����Ԫ�غ�b�е���һ��Ԫ�رȽ�
            j++;
        if(j==Lb.length)
        //�������whileѭ��ʱj==Lb.length��˵����ǰa�е����Ԫ�ز���b��
            Lc.elem[k++]=La.elem[i];
    }
    Lc.length=k;//���ѭ��������c��ĳ��Ⱦ���k
}

void show()
{
    cout<<"1----������Ա�"<<endl;
    cout<<"2----�ж����Ա��Ƿ�Ϊ��"<<endl;
    cout<<"3----�����Ա���"<<endl;
    cout<<"4----��ȡ���Ա�ָ��λ��Ԫ��"<<endl;
    cout<<"5----��ǰ��"<<endl;
    cout<<"6----����"<<endl;
    cout<<"7----�����Ա�ָ��λ�ò���Ԫ��"<<endl;
    cout<<"8----ɾ�����Ա�ָ��λ��Ԫ��"<<endl;
    cout<<"9----��ʾ���Ա�"<<endl;
    cout<<"     �˳�������һ��������"<<endl;
    cout<<"����������룺";
}
int main()
{
/*
//-------------���ϵ�����------------------------
    SqList L1,L2,L3;
//--------------L1---------------------
    if(InitList(L1)==1)//��ʼ��
        cout<<"��ʼ���ɹ���"<<endl<<endl;
    else
    {
        cout<<"��ʼ��ʧ��"<<endl<<endl;
        return 0;
    }
    cout<<"���������Ա��е�Ԫ�أ���-1��������"<<endl;
    if(CreateList(L1)==1)//�������Ա�
        cout<<"�����ɹ�"<<endl<<endl;
    else
    {
        cout<<"����ʧ��"<<endl<<endl;
        return 0;
    }

//----------------L2----------------------------
    if(InitList(L2)==1)//��ʼ��
        cout<<"��ʼ���ɹ���"<<endl<<endl;
    else
    {
        cout<<"��ʼ��ʧ��"<<endl<<endl;
        return 0;
    }
    cout<<"���������Ա��е�Ԫ�أ���-1��������"<<endl;
    if(CreateList(L2)==1)//�������Ա�
        cout<<"�����ɹ�"<<endl<<endl;
    else
    {
        cout<<"����ʧ��"<<endl<<endl;
        return 0;
    }

//--------------L3------------------------------
    if(InitList(L3)==1)//��ʼ��
        cout<<"��ʼ���ɹ���"<<endl<<endl;
    else
    {
        cout<<"��ʼ��ʧ��"<<endl<<endl;
        return 0;
    }

    cout<<"������";
    Listintersection(L1,L2,L3);
    for(int i=0;i<L3.length;i++)
        cout<<L3.elem[i]<<" ";
    cout<<endl<<endl;

    cout<<"������";
    mergeList(L1,L2,L3);
    for(int i=0;i<L3.length;i++)
        cout<<L3.elem[i]<<" ";
    cout<<endl<<endl;

    cout<<"���";
    subtract(L1,L2,L3);
    for(int i=0;i<L3.length;i++)
        cout<<L3.elem[i]<<" ";
    cout<<endl<<endl;
*/
    int x;//������
    int a;//���Ա��ĳһλ��
    int e;//Ԫ��
    SqList L;

    cout<<"----------����˳���----------"<<endl;
    if(InitList(L)==1)//��ʼ��
        cout<<"��ʼ���ɹ���"<<endl<<endl;
    else
    {
        cout<<"��ʼ��ʧ��"<<endl<<endl;
        return 0;
    }
    cout<<"���������Ա��е�Ԫ�أ���-1��������"<<endl;
    if(CreateList(L)==1)//�������Ա�
        cout<<"�����ɹ�"<<endl<<endl;
    else
    {
        cout<<"����ʧ��"<<endl<<endl;
        return 0;
    }
    show();
    cin>>x;
    while(x>0)
    {
        if(x>10 || x==0)
            cout<<"�����������������룡"<<endl<<endl;
        else
        {
            if(x==1)
            {
                cout<<"----------���˳���----------"<<endl;
                ClearList(L);
                cout<<"��ճɹ�"<<endl<<endl;
            }
            else if(x==2)
            {
                cout<<"----------�ж����Ա��Ƿ�Ϊ��----------"<<endl;
                if(isEmpty(L)==1)
                    cout<<"���Ա�Ϊ��"<<endl<<endl;
                else
                    cout<<"���Ա�Ϊ��"<<endl<<endl;
            }
            else if(x==3)
            {
                cout<<"----------�����Ա���----------"<<endl;
                cout<<"���Ա�ĳ���Ϊ��"<<L.length<<endl<<endl;
            }
            else if(x==4)
            {
                cout<<"----------��ȡ���Ա�ָ��λ��Ԫ��----------"<<endl;
                cout<<"������λ�ã�";
                cin>>a;
                if(a<=L.length && a>=1)
                    cout<<L.elem[a-1]<<endl<<endl;
                else
                    cout<<"����λ������"<<endl<<endl;
            }
            else if(x==5)
            {
                cout<<"----------��ǰ��----------"<<endl;
                cout<<"������λ�ã�";
                cin>>a;
                if(a<=L.length && a>1)
                    cout<<L.elem[a-2]<<endl<<endl;
                else
                    cout<<"����λ������"<<endl<<endl;
            }
            else if(x==6)
            {
                cout<<"----------����----------"<<endl;
                cout<<"������λ�ã�";
                cin>>a;
                if(a<L.length && a>=1)
                    cout<<L.elem[a]<<endl<<endl;
                else
                    cout<<"����λ������"<<endl<<endl;
            }
            else if(x==7)
            {
                cout<<"----------�����Ա�ָ��λ�ò���Ԫ��----------"<<endl;
                cout<<"������λ�ã�";
                cin>>a;
                cout<<"������Ԫ�أ�";
                cin>>e;
                if(ListInsert(L,a,e))
                    cout<<"����ɹ�"<<endl<<endl;
                else
                    cout<<"����ʧ��"<<endl<<endl;
            }
            else if(x==8)
            {
                cout<<"----------ɾ�����Ա�ָ��λ��Ԫ��----------"<<endl;
                cout<<"������λ�ã�";
                cin>>a;
                if(ListDelete(L,a,e))
                    cout<<"ɾ���ɹ�"<<endl<<endl;
                else
                    cout<<"ɾ��ʧ��"<<endl<<endl;
            }
            else if(x==9)
            {
                for(int i=0;i<L.length;i++)
                    cout<<L.elem[i]<<" ";
                cout<<endl<<endl;
            }
        }
    cout<<"����������룺";
    cin>>x;
    }
    return 0;
}
