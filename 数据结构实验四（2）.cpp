#include <iostream>
#include<stdlib.h>
#include <stack>
#include <iomanip>
#include <string.h>
#include <stdio.h>
using namespace std;

typedef struct
{
	int weight; //权值
	int parent, lchild, rchild;//双亲结点、左右孩子结点
}HTNode, *HuffmanTree;

//找出最小的两个值,两个最小的值的下标分别记为s1 s2
void Select(HuffmanTree &HT, int end, int &s1, int &s2)
{
	int min1=10000, min2=10000;
	for(int i=1;i<=end;i++)//找第一个结点
	{
		if(HT[i].parent==0 && HT[i].weight<min1)
		{//如果没有双亲结点并且权值小于min1
			min1= HT[i].weight;
			s1=i;
		}
	}
	for(int i=1;i<=end;i++)//找第二个结点
	{
		if(HT[i].parent==0 && HT[i].weight<min2 && s1!=i)
		{
			min2=HT[i].weight;
			s2=i;
		}
	}
}

//创建哈夫曼树和哈夫曼编码
void HuffmanCoding(HuffmanTree &HT, char ** &HC, int *w, int n)
{//w是记录权值的数组，n是数组长度
	int i,s1,s2;
	HuffmanTree p;
	if(n<=1)//如果长度小于等于一，就不用排序
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

	 //从叶子到根逆向求每个字符的哈夫曼树编码
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

//输出哈夫曼编码
void showHuffmanCode(char ** HC)
{
	char x;
	for(int i=1;i<=27;i++){
		if(i!=27)
		 {
		 	x=i+'A'-1;
		 	cout<<x<<"的哈夫曼编码是：";
		 }
		else
			cout<<"空格的哈夫曼编码是：";
		for(int j=1;j<= HC[i][0];j++)
		{
			cout<<HC[i][j];
		}
		cout<<endl;
	}
}

//将字符转化为哈夫曼编码
void TranserString(char ** HC,string s)
{
	string ss;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]>='A' && s[i]<='Z')//大写转小写，统一
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

//将哈夫曼码转换为字符
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
	char **HC;//用来存储编码
	string s;
	int p[27]={64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1,168};

	HC = (char**) malloc ((27+1) * sizeof(char *));
	for(int i=1;i<=28;i++)
	    HC[i] = (char *)malloc((27+1) * sizeof(char));

	int choice;
    string s1(80,'*');
    string s2(15,'*');
    cout<<s1<<endl;
    cout<<s2<<setw(50)<<left<<"1.输入HuffmanTree的参数."<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"2.初始化HuffmanTree参数.（含有26字母及空格）"<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"3.创建HuffmanTree和编码表."<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"4.输出编码表."<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"5.输入编码，并翻译为字符."<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"6.输入字符，并实现转码."<<s2<<endl;
    cout<<s2<<setw(50)<<left<<"7.退出."<<s2<<endl;
    cout<<s1<<endl;
    cout<<"请输入选择：";
    cin>>choice;
	while(1)
	{
		if(choice==1)
		{
			HuffmanCoding(HT,HC,p,27);
			cout << "创建成功，1,2,3已完成，无需输入2,3" << endl;
		}
		else if(choice == 4)
		{
			showHuffmanCode(HC);
		}
		else if(choice == 5)
		{
			getchar();
			cout << "请输入HuffmanCode：";
			getline(cin,s);
			TranserHuffmanCode(HC,s);
		}
		else if(choice == 6)
		{
			getchar();
			cout << "请输入字符：";
			getline(cin,s);
			TranserString(HC,s);
		}
		else if(choice == 7)
			break;
		else
			cout << "输入无效请重新输入" << endl;

        cout<<s1<<endl;
        cout<<s2<<setw(50)<<left<<"1.输入HuffmanTree的参数."<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"2.初始化HuffmanTree参数.（含有26字母及空格）"<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"3.创建HuffmanTree和编码表."<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"4.输出编码表."<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"5.输入编码，并翻译为字符."<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"6.输入字符，并实现转码."<<s2<<endl;
        cout<<s2<<setw(50)<<left<<"7.退出."<<s2<<endl;
        cout<<s1<<endl;
        cout<<"请输入选择：";
        cin>>choice;
	}
	return 0;
}
