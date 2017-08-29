#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<stack>
#include<queue>
#define NumVer 50
#define NumEgde 50
#define Min 10000
using namespace std;
typedef struct{
	char Vet[NumVer];
	int Edge[NumVer][NumVer];
	int v, e;
}MTGraph;
typedef struct Edge{
	int fir;
	int end;
	int weight;
}Edge;
typedef struct EdgeNode{
	int adjvex;
	EdgeNode*next;
}EdgeNode;
typedef struct Vnode{
	int order;
	char data;
	EdgeNode*first;
	int Set[NumVer];
	int i = 1;
}Vnode;
typedef struct AdjGraph{
	Vnode Edge[NumVer];
	int v, e;
}AdjGraph;
typedef struct List{
	List*next;
	Edge* value;
}List;
void CreatMTGraph(MTGraph* G)
{
	int i, j, s, k;
	ifstream in("Graph.txt");
	if (!in)
	{
		cout << "fail to open the file !" << endl;
	}
	in >> G->v >> G->e;
	for (i = 0; i < G->v; i++)
	{
		for (j = 0; j < G->v; j++)
		{
			G->Edge[i][j] = 0;
		}
	}
	for (i = 0; i < G->v; i++)
	{
		in >> G->Vet[i];
	}
	for (i = 0; i < G->e; i++)
	{
		in >> s >> k >> j;
		G->Edge[s][k] = j;
		G->Edge[k][s] = j;
	}
}
void Transpose(AdjGraph* GG, MTGraph*G)
{
	int i, j;
	GG->e = G->e;
	GG->v = G->v;
	for (i = 0; i < G->v; i++)
	{
		GG->Edge[i].data = G->Vet[i];
		GG->Edge[i].order = i;
		GG->Edge[i].first = NULL;
	}
	for (i = 0; i < G->v; i++)
	{
		for (j = (G->v) - 1; j >= 0; j--)//结果是否一样？
		{
			if (G->Edge[i][j] == 1)
			{
				EdgeNode*temp = new EdgeNode;
				temp->adjvex = j;
				temp->next = GG->Edge[i].first;
				GG->Edge[i].first = temp;
			}
		}
	}
}
List* Creatlist(Edge*temp)
{
	List*p = (List*)malloc(sizeof(List));
	p->next = NULL;
	p->value = temp;
	p->value->weight = Min;
	return p;
}
int Insert(List*p, Edge* value)
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
Edge* Delete(List*p)
{
	Edge*q = NULL;
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
Edge* Top(List*p)
{
	if (!p->next)
	{
		return NULL;
	}
	return p->next->value;
}
List* Edgesort(MTGraph*G)
{
	int i, j;
	Edge*temp = new Edge;
	List* L=Creatlist(temp);
	for (i = 0; i < G->v; i++)
	{
		for (j = 0; j < G->v; j++)
		{
			if ((G->Edge[i][j]>0)&&(i<j))
			{
				Edge*p = new Edge;
				p->fir = i;
				p->end = j;
				p->weight =G->Edge[i][j];
				Insert(L, p);
			}
		}
	}
	return L;
}
void Union(Vnode* temp1, Vnode* temp2,AdjGraph*GG)
{
	int j = 0;
	int k = 0;
	int sum [NumVer];
	int sum2[NumVer];
	for (j = 0; j < NumVer; j++)
	{
		sum[j] = 0;
		sum2[j] = 0;
	}
	for (j = 0; j < temp2->i; j++)
	{
	    for (k = 0; k < temp1->i; k++)
	     {	
			GG->Edge[temp2->Set[j]].Set[temp2->i + sum[j]] = GG->Edge[temp1->Set[0]].Set[k];
			sum[j]++;
		}
	}
	for (j = 0; j < temp1->i; j++)
	{
	    for (k = 0; k < temp2->i; k++)
		{
			GG->Edge[temp1->Set[j]].Set[temp1->i + sum2[j]] = GG->Edge[temp2->Set[0]].Set[k];
			sum2[j]++;
		}
	}
	
	for (k = 0; k < temp1->i; k++)
	{
		GG->Edge[temp2->Set[k]].i = GG->Edge[temp2->Set[k]].i + sum[k];
	}
	for (k = 0; k < temp2->i; k++)
	{
		GG->Edge[temp1->Set[k]].i = GG->Edge[temp1->Set[k]].i + sum2[k];
	}	
}
int Find(Vnode* temp1, Vnode* temp2)
{
	int i, j;
	for (i = 0; i < temp1->i; i++)
	{
		for (j = 0; j < temp2->i; j++)
		{
			if (temp1->Set[i] == temp2->Set[j])
			{
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	int i = 0;
	MTGraph* G = new MTGraph;
	AdjGraph*GG = new AdjGraph;
	Edge*temp=NULL;
	CreatMTGraph(G);
	Transpose(GG, G);
	List*L=Edgesort(G);
	for (i = 0; i < G->e; i++)
	{
		GG->Edge[i].Set[0] = i;
		GG->Edge[i].i = 1;
	}
	int flag = 0;
	for (i = 0; i < G->e; i++)
	{
		temp = Delete(L);
		flag = Find(&GG->Edge[temp->fir], &GG->Edge[temp->end]);
		if (!flag)
		{
			cout << "Edge:";
			cout << temp->fir << temp->end<<endl;
			Union(&GG->Edge[temp->fir], &GG->Edge[temp->end], GG);
		}

	}
	getchar();
}
