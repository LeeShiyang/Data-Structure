#pragma warning(disable:4996)
#include<iostream>
#include<queue>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<functional>
#include<vector>
#include<stack>
#define Min -10000
#define N 256 /*叶子树*/
#define  m  2*(N)-1   /*节点总数*/
#define K 5
using namespace std;
typedef struct Node{
	int weight;
	Node*Link=NULL;
	Node*Rlink=NULL;
	Node*next;
	int tag;
	char data;
}Node,*pnode;
typedef struct List{
	List*next;
	Node* value;
}List;
int Content[N];
void Getfile(Node* Hum[], int sum)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < N; i++)
	{
		if (Content[i])
		{
			j++;
			Hum[j] = new Node;
			Hum[j]->data = i;
			Hum[j]->weight = Content[i];
		}
	}

	if (j < sum)
	{
		for (i = j + 1; i <= sum; i++)
		{
			Hum[i] = new Node;
			Hum[i]->data = '&';
			Hum[i]->weight = 0;
		}
	}
}
List* Creatlist(Node*temp)
{
	List*p = (List*)malloc(sizeof(List));
	p->next = NULL;
	p->value = temp;
	p->value->weight = Min;
	return p;
}
int Insert(List*p, Node* value)
{
	List*q = NULL;
	while ((q = p->next) && q->value->weight < value->weight)
	{
		p = q;
	}
	List* nn = (List*)malloc(sizeof(List));
	nn->next = p->next;
	p->next = nn;
	nn->value = value;
	return 1;
}
Node* Delete(List*p)
{
	Node*q = NULL;
	if (p->next == NULL)
	{
		return NULL;
	}
	else
	{
		q = p->next->value;
		p->next = p->next->next;
	}
	return q;
}
Node* Top(List*p)
{
	if (!p->next)
	{
		return NULL;
	}
	return p->next->value;
}
int main()
{
	Node*temp=new Node;
	temp->weight = Min;
	int sum = 0;
	int i;
	char ch;
	FILE*fp = fopen("SOP.txt", "r");
	if (!fp)
	{
		cout << "Fail to open!" << endl;
	}
	for (i = 0; i<N; i++)
	{
		Content[i] = 0;
	}
	do
	{
		ch = fgetc(fp);
		if (ch == EOF)
		{
			break;
		}
		Content[ch]++;
		i++;
	} while (ch != EOF);
	for (i =0 ; i < N; i++)
	{
		if (Content[i])
		{
			sum++;
		}
	}
	cout << "一共"<<sum<<"种字符"<<endl ;
	int kz = (sum - 1) % (K - 1);
	if (kz != 0)
	{
		sum = sum+K - 1 - kz;
	}
	Node* Hum[N];
	Getfile(Hum,sum);
	for (i = 1; i <= sum; i++)
	{
		cout << Hum[i]->weight << Hum[i]->data << endl;
	}
	 List* Qn=Creatlist(temp);
	List* Sn=Creatlist(temp);

	for (i = 1; i <= sum; i++)
	{
		Insert(Qn,Hum[i]);
		Insert(Sn, Hum[i]);
	}
	pnode comban ,x,y;
	//cout << Top(Qn)->weight;
	int add = 0;
	while ( Qn->next->next)
	{
		 comban = new Node;
		 comban->Link  = Top(Qn);
		 add = 0;
		for (i = 1; i <= K; i++)
		{
			x = Top(Qn);//Link指针指向其第一个孩纸
			Delete(Qn);
			y = Top(Qn);
			add = add + x->weight;
			x->tag = K - i;
			if (x->tag == 0)
			{
				x->Rlink = comban;//如果tag==0指向父节点
			}
			else
			{
				x->Rlink = y;//如果tag==0指向父节点
			}
		  }	
		comban->data = '&';
		comban->weight = add;
		comban->tag = -1;
		Insert(Qn, comban);
	}
	stack<int> Code;
	char Let[N];
	int j = 0;
	 i = 1;
	int table[N/4][N/4];
	for (j = 0; j <N/4; j++)
	{
		for (i = 0; i < N/4; i++)
		{
			table[j][i] = -1;
		}
	}
	j = 0;
	i = 1;
	for (j = 1; j <= sum; j++)
	{
		
		x = Delete(Sn);
		Let[j] = x->data;
		cout << x->data;
	    Code.push(x->tag);
		cout << x->tag;
		while (x != comban)
		{
			while (x->tag != 0)
			{
				x = x->Rlink;
			}
			x = x->Rlink;
			if (x == comban)
			{
				break;
			}
			Code.push(x->tag);
			
			cout << x->tag;
		}
		cout << endl;
		while (Code.size() > 0)
		{
			table[j][i] = Code.top();
			Code.pop();
			i++;
		}
		i = 1;
	}
	FILE*fout= fopen("Bianma.txt", "w");
	FILE*fin = fopen("SOP.txt", "r");
	char ab = 1;
	if (!fin)
	{
		cout << "Fail to open!" << endl;
	}
	if (!fout)
	{
		cout << "Fail to open!" << endl;
	}
	while (ab != EOF)
	{
		ab = fgetc(fin);
		cout << endl;
		cout << ab;
		j = 1;
		for (i = 1; i <= sum; i++)
		{
			if (ab == Let[i])
			{
				while (table[i][j] >= 0)
				{
					fprintf(fout,"%d",table[i][j]);
					j++;
				}
			}
		}
		j = 1;
	}
	fclose(fout);
	fclose(fin);
	FILE*ddd = fopen("Bianma.txt", "r");
	if (!ddd)
	{
		cout << "打开错误！\n";
	}
	int num =K;
	Node*p = NULL;
	p = comban;
	int flag = 0;
	while (num != EOF)
	{
		fscanf(ddd, "%1d", &num);
		p = p->Link;
		while (p->tag != num)
		{
			p = p->Rlink;
		}
		if (p->data !='&')
		{
			cout << p->data;
			p = comban;
			flag++;
		}
		if (flag >= add)
		{
			break;
		}
	}
	getchar();
}
