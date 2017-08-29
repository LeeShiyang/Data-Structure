#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<stack>
#include<queue>
#define NumVer 50
#define NumEgde 50
#define Min -10000
#define Max 1000000
using namespace std;
typedef struct{
	char Vet[NumVer];
	int Edge[NumVer][NumVer];
	int v, e;
}MTGraph;
typedef struct EdgeNode{
	int adjvex;
	EdgeNode*next;
}EdgeNode;
typedef struct Vnode{
	int order;
	char data;
	EdgeNode*first;
	int parent ;
	int flag ;
	int weight;
}Vnode;
typedef struct AdjGraph{
	Vnode Edge[NumVer];
	int v, e;
}AdjGraph;
typedef struct List{
	List*next;
	Vnode* value;
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
			if (G->Edge[i][j])
			{
				EdgeNode*temp = new EdgeNode;
				temp->adjvex = j;
				temp->next = GG->Edge[i].first;
				GG->Edge[i].first = temp;
			}
		}
	}
}
List* Creatlist(Vnode*temp)
{
	List*p = (List*)malloc(sizeof(List));
	p->next = NULL;
	p->value = temp;
	p->value->weight = Min;
	return p;
}
int Insert(List*p, Vnode* value)
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
int Delete2(List*p, Vnode* value)
{
	List*q = NULL;
	while ((q = p->next) && q->value->data != value->data)
	{
		p = q;
	}
	p->next = q->next;
	return q->value->weight;
}
int  Delete(List*p)
{
	Vnode*q = NULL;
	if (p->next == NULL)
	{
		return NULL;
	}
	else
	{
		q = p->next->value;
		p->next = p->next->next;
	}
	return q->order;
}
Vnode* Top(List*p)
{
	if (!p->next)
	{
		return NULL;
	}
	return p->next->value;
}
int main()
{
	MTGraph*G = new MTGraph;
	AdjGraph*GG = new AdjGraph;
	Vnode* p = new Vnode;
	CreatMTGraph(G);
	Transpose(GG, G);
	int i = 0;
	for (i = 0; i < G->v; i++)
	{
		GG->Edge[i].order = i;
		GG->Edge[i].flag = 1;
		GG->Edge[i].parent = -1;
		GG->Edge[i].weight = Max;
	}
	GG->Edge[0].weight = 0;
	List*L = Creatlist(p);
	for (i = 0; i < G->v; i++)
	{
		Insert(L, &GG->Edge[i]);
	}

	
	while (L->next)
	{
		i = Delete(L);
		cout <<"->"<< GG->Edge[i].data;
		GG->Edge[i].flag = 0;
		EdgeNode*nn = GG->Edge[i].first;
		while (nn)
		{
			if (GG->Edge[nn->adjvex].flag == 1 &&( G->Edge[i][nn->adjvex] < GG->Edge[nn->adjvex].weight))
			{
				GG->Edge[nn->adjvex].weight = G->Edge[i][nn->adjvex];
				GG->Edge[nn->adjvex].parent = i;
				Delete2(L, &GG->Edge[nn->adjvex]);
				Insert(L, &GG->Edge[nn->adjvex]);
			}			
			nn = nn->next;
		}
	}
	getchar();
}