#include <iostream>
#include<stdlib.h>
#include <stack>
#include <iomanip>
#include <string.h>
#include <stdio.h>
using namespace std;

typedef struct
{
	int weight; //Ȩֵ
	int parent, lchild, rchild;//˫�׽�㡢���Һ��ӽ��
}HTNode, *HuffmanTree;

//�ҳ���С������ֵ,������С��ֵ���±�ֱ��Ϊs1 s2
void Select(HuffmanTree &HT, int end, int &s1, int &s2)
{
	int min1=10000, min2=10000;
	for(int i=1;i<=end;i++)//�ҵ�һ�����
	{
		if(HT[i].parent==0 && HT[i].weight<min1)
		{//���û��˫�׽�㲢��ȨֵС��min1
			min1= HT[i].weight;
			s1=i;
		}
	}
	for(int i=1;i<=end;i++)//�ҵڶ������
	{
		if(HT[i].parent==0 && HT[i].weight<min2 && s1!=i)
		{
			min2=HT[i].weight;
			s2=i;
		}
	}
}

//�������������͹���������
void HuffmanCoding(HuffmanTree &HT, char ** &HC, int *w, int n)
{//w�Ǽ�¼Ȩֵ�����飬n�����鳤��
	int i,s1,s2;
	HuffmanTree p;
	if(n<=1)//�������С�ڵ���һ���Ͳ�������
	return ;
	int m=2*n-1;
	HT=(HuffmanTree)malloc((m + 1)*sizeof(HTNode));
	for(p=HT+1,i=1;i<=n;i++,p++,w++)
	{
		*p= {*w,0,0,0};
	}
	 for(; i<=m;i++,p++)
	 *p = {0, 0, 0, 0};
	 for(i=n+1;i<=m;i++)
	 {
	 	Select(HT, i-1, s1, s2);
	 	HT[i].weight = HT[s1].weight + HT[s2].weight;
	 	HT[s1].parent = i;
	 	HT[s2].parent = i;
	 	HT[i].lchild = s1;
	 	HT[i].rchild = s2;
	 }

	 //��Ҷ�ӵ���������ÿ���ַ��Ĺ�����������
	 stack<char> s;
	 for(i =1;i<=n;i++)
	{
		int temp=i,p,k=0;
	 	p=HT[temp].parent;
	 	while(p)
	 	{
	 		if(HT[p].lchild == temp)
			s.push('0');
			if(HT[p].rchild == temp)
			s.push('1');
			temp = p;
			p = HT[temp].parent;
			k++;
	 	}
	 	int j = 0;
	 	while(!s.empty())
		{
			HC[i][++j] = s.top();
			s.pop();
		}
		HC[i][0] = j;
	 }
}

//�������������
void showHuffmanCode(char ** HC)
{
	char x;
	for(int i=1;i<=27;i++){
		if(i!=27)
		 {
		 	x=i+'A'-1;
		 	cout<<x<<"�Ĺ����������ǣ�";
		 }
		else
			cout<<"�ո�Ĺ����������ǣ�";
		for(int j=1;j<= HC[i][0];j++)
		{
			cout<<HC[i][j];
		}
		cout<<endl;
	}
}

//���ַ�ת��Ϊ����������
void TranserString(char ** HC,string s)
{
	string ss;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]>='A' && s[i]<='Z')//��дתСд��ͳһ
			s[i]+=32;
		if(s[i]==' ')
			s[i]='z' + 1;
	}
	for(int i=0;i<s.length();i++)
	{
		for(int j=1;j<=HC[s[i]-'a'+1][0];j++)
		ss+=HC[s[i]-'a'+1][j];
	}
	cout<<ss<<endl;
}

//����������ת��Ϊ�ַ�
void TranserHuffmanCode(char ** HC,string s)
{
	string ss="", s1="";
	string t[27];
	for(int i=0;i<27;i++)
	{
		t[i]="";
		for(int k=1;k<=HC[i + 1][0];k++)
			t[i]+=HC[i+1][k];
	}
	for(int i=0;i<s.size();i++)
	{
		ss+=s[i];
		for(int j=0;j<27;j++)
		{
			if(ss==t[j])
			{
				ss="";
				if(j!=26)
				{
					s1+=j+'a' ;
				}
				else if(j==26)
				{
					s1+=' ';
				}
			}
		}
	}
	cout << s1 << endl;
}
int main ()
{
	HuffmanTree HT;
	char **HC;//�����洢����
	string s;
	int p[27]={64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1,168};

	HC = (char**) malloc ((27+1) * sizeof(char *));
	for(int i=1;i<=28;i++)
	    HC[i] = (char *)malloc((27+1) * sizeof(char));

	int choice;
    string s1(80,'*');
    string s2(15,'*');
    cout<<s1<<endl;
    cout<<s2<<setw(50)<<left<<"1.����HuffmanTree�Ĳ���."<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"2.��ʼ��HuffmanTree����.������26��ĸ���ո�"<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"3.����HuffmanTree�ͱ����."<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"4.��������."<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"5.������룬������Ϊ�ַ�."<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"6.�����ַ�����ʵ��ת��."<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"7.�˳�."<<s2<<endl;
    cout<<s1<<endl;
    cout<<"������ѡ��";
    cin>>choice;
	while(1)
	{
		if(choice==1)
		{
			HuffmanCoding(HT,HC,p,27);
			cout << "�����ɹ���1,2,3����ɣ���������2,3" << endl;
		}
		else if(choice == 4)
		{
			showHuffmanCode(HC);
		}
		else if(choice == 5)
		{
			getchar();
			cout << "������HuffmanCode��";
			getline(cin,s);
			TranserHuffmanCode(HC,s);
		}
		else if(choice == 6)
		{
			getchar();
			cout << "�������ַ���";
			getline(cin,s);
			TranserString(HC,s);
		}
		else if(choice == 7)
			break;
		else
			cout << "������Ч����������" << endl;

        cout<<s1<<endl;
        cout<<s2<<setw(50)<<left<<"1.����HuffmanTree�Ĳ���."<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"2.��ʼ��HuffmanTree����.������26��ĸ���ո�"<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"3.����HuffmanTree�ͱ����."<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"4.��������."<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"5.������룬������Ϊ�ַ�."<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"6.�����ַ�����ʵ��ת��."<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"7.�˳�."<<s2<<endl;
        cout<<s1<<endl;
        cout<<"������ѡ��";
        cin>>choice;
	}
	return 0;
}
