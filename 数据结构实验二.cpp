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

//���嵥����Ĵ洢�ṹ
typedef struct LNode
{
    int data;//������
    LNode *next;//ָ����
}LNode,*LinkList;  //LnkListΪָ��LNode���͵�ָ��

//���������ʼ��
Status InitList(LinkList &L)
{
    L=new LNode;
    L->next=NULL;
    return OK;
}

//����Ԫ���ڵ������е�λ��
void LocateElem(LinkList L,int e)
{
    LNode *p=L->next; //��ʼ��һ��ָ��LNode���͵�ָ�룬��ʼֵΪ�������Ԫ���
    int n=1;
    while(p && p->data!=e)
    {
        p=p->next;
        n++;
    }
        if(p)
            cout<<"�ɹ��ҵ�����Ԫ���ǵ�"<<n<<"����";
        else
            cout<<"δ�ҵ���Ԫ�ء�";
}

//��Ԫ�ز��뵽������ĵ�i��λ��
Status ListInsert(LinkList &L,int i,int e)
{
    LNode *p=L;
    int j=0;
    while(p && (j<i-1))
    {//�ҵ���i-1���ڵ��λ��
        p=p->next;
        j++;
    }
    if(!p || (j>i-1))
        //cout<<"�����λ�÷Ƿ�"<<endl; //�������ѭ��ʱpΪ�ջ���j>i-1������ִ���
        return ERROR;
    else
    {
        LNode *s=new LNode; //����һ���½ڵ�
        s->data=e;  //�½ڵ��������ΪҪ�����Ԫ��
        s->next=p->next; //�½ڵ��ָ����Ϊԭ���ĵ�i���ڵ�
        p->next=s;//p��ָ����Ϊ������½ڵ�
        //cout<<"����Ԫ�سɹ�"<<endl;
        return OK;
    }
}

//����������
Status CreataList(LinkList &L)
{
    int x,i=1;
    cout<<"���������ݣ���9999��������";
    cin>>x;
    while(x!=9999)
    {
        ListInsert(L,i,x);
        i++;
        cin>>x;
    }
}


//���������i��λ�õ�Ԫ��ɾ��
Status ListDelete(LinkList &L,int i)
{
    LNode *p=L;
    int j=0;
    while((p->next) && j<i-1)
    {//�ҵ���i-1���ڵ��λ��
        p=p->next;
        j++;
    }
    if(!(p->next) || (j>i-1))
      //  cout<<"�����λ�÷Ƿ�"<<endl;//�������ѭ��ʱp����һ��Ԫ��Ϊ�ջ���j>i-1������ִ���
      return ERROR;
    else
    {
        LNode *s=p->next;//��һ����ʱ�ڵ�s�洢Ҫɾ���Ľڵ�
        p->next=p->next->next;//�ı�p��ָ��
        delete s;//ɾ������ڵ�
        //cout<<"ɾ��Ԫ�سɹ�"<<endl;
        return OK;
    }
}

//���õ�����ṹ���ʵ��������������Ĺ鲢����
Status mergeList(LinkList &La,LinkList &Lb,LinkList &Lc)
{
	LNode *pa = La->next; //pa��pb�ֱ�ָ�����������Ԫ���
	LNode *pb = Lb->next;
	Lc=La;//��ʼʱ��Lc��ͷָ��ָ��La��ָ������La��ͷ���
	LNode *pc=Lc;
	while(pa && pb)
    {//��La��Lb�Ķ�û�е����βʱ
        if(pa->data <= pb->data)
        {//�����Ԫ����Ȼ���La��Ԫ�ؽ�С
            pc->next=pa; //��pa��ָ������ӵ�pc��ָ���֮��
            pc=pa;       //pcָ��pa
            pa=pa->next; //paָ����һ���
        }
        else
        {//�������Lb��ǰ�ڵ�����ݽ�С
            pc->next=pb; //��pb��ָ������ӵ�pc��ָ���֮��
            pc=pb;       //pcָ��pb
            pb=pb->next; //pbָ����һ���
        }
    }
    pc->next=pa?pa:pb;//����ѭ��ʱ���pc->next=pa��˵��La�ǿգ��ͽ�Laʣ�µĲ���������Lc��
    //�������ѭ��ʱpc->next!=pa��˵��Lb�ǿջ��߶��߶�Ϊ�գ��ͽ�Lbʣ�µĲ���������Lc��
    return OK;
}

//��ʾ������
void Display(LinkList &L)
{
    LNode *p=L->next;  //p�ǵ��������Ԫ���
    if(!p)
    {
        cout<<"��ǰ������Ϊ��"<<endl;
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
    cout<<s2<<left<<setw(40)<<"1.���������ǵݼ��ĵ�����"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"2.���ҵ������е�Ԫ��"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"3.�������в���Ԫ��"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"4.�ӵ�������ɾ��Ԫ��"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"5.ʵ������������Ĺ鲢"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"6.��ʾ������"<<s2<<endl;
    cout<<s2<<left<<setw(40)<<"7.�˳�"<<s2<<endl;
    cout<<s1<<endl;
    cout<<"����������ѡ��";
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
                cout<<"������Ҫ���в����ĵ�����a��b����";
                cin>>ch;
                cout<<"������Ҫ���ҵ�Ԫ�أ�";
                int elem;
                cin>>elem;
                if(ch=='a')
                    LocateElem(La,elem);
                else if(ch=='b')
                    LocateElem(Lb,elem);
                else
                    cout<<"���벻�Ϸ���";
                cout<<endl;
                break;
            case 3:
                cout<<"������Ҫ���в����ĵ�����a��b����";
                cin>>ch;
                cout<<"������Ҫ�����Ԫ�غ�Ҫ�����λ�ã�";
                cin>>elem>>locate;
                if(ch=='a')
                {
                    int k=ListInsert(La,locate,elem);
                    if(k==1)
                        cout<<"����ɹ���"<<endl;
                    else
                        cout<<"����ʧ�ܣ�"<<endl;
                }
                else if(ch=='b')
                {
                    int k=ListInsert(Lb,locate,elem);
                    if(k==1)
                        cout<<"����ɹ���"<<endl;
                    else
                        cout<<"����ʧ�ܣ�"<<endl;
                }
                else
                    cout<<"���벻�Ϸ���"<<endl;
                break;
            case 4:
                cout<<"������Ҫ���в����ĵ�����a��b����";
                char ch;
                cin>>ch;
                cout<<"������Ҫɾ����Ԫ�ص�λ�ã�";
                cin>>locate;
                if(ch=='a')
                {
                    int k=ListDelete(La,locate);
                    if(k==1)
                        cout<<"ɾ���ɹ���"<<endl;
                    else
                        cout<<"ɾ��ʧ�ܣ�"<<endl;
                }
                else if(ch=='b')
                {
                    int k=ListDelete(Lb,locate);
                    if(k==1)
                        cout<<"ɾ���ɹ���"<<endl;
                    else
                        cout<<"ɾ��ʧ�ܣ�"<<endl;
                }
                else
                    cout<<"���벻�Ϸ���"<<endl;
                break;
            case 5:
                mergeList(La,Lb,Lc);
                cout<<"������c��Ԫ��Ϊ��";
                Display(Lc);
                cout<<endl;
                break;
            case 6:
                cout<<"������a��Ԫ��Ϊ��";
                Display(La);
                cout<<endl;
                cout<<"������b��Ԫ��Ϊ��";
                Display(Lb);
                cout<<endl;
                break;
            case 7:
                return 0;
            default:
                cout<<"���벻�Ϸ���";
                break;
        }
        cout<<endl;
        cout<<"����������ѡ��";
        cin>>x;
    }
    return 0;
}
