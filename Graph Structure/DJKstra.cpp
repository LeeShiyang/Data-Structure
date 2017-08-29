#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<iostream>
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
	int parent;
	int flag;
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
	if (q == NULL)
	{
		return -1;
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
void InitialSingleSource(AdjGraph *GG, int s)
{
	
	int i;
	for (i = 0; i < GG->v; i++)
	{
		GG->Edge[i].weight = Max;
		GG->Edge[i].parent = -1;
	}
	GG->Edge[s].weight = 0;
}
void Relax(AdjGraph *GG, int u, int v,MTGraph* G)
{
	if (GG->Edge[v].weight>GG->Edge[u].weight + G->Edge[u][v])
	{
		GG->Edge[v].weight = GG->Edge[u].weight + G->Edge[u][v];
		GG->Edge[v].parent = u;
	}
}
void Print(AdjGraph*GG, int s, int v)
{
	if (GG->Edge[v].parent == -1)
	{
		cout << "No path to go through!" << endl;;
	}
	else if (GG->Edge[v].parent == s)
	{
		cout <<GG->Edge[s].data<<"  ";
		cout << GG->Edge[v].data<<"   ";
	}
	else
	{
		Print(GG, s, GG->Edge[v].parent);
		cout << GG->Edge[v].data<<"  ";
	}
}
int main()
{
	MTGraph*G = new MTGraph;
	AdjGraph*GG = new AdjGraph;
	Vnode*temp = new Vnode;
	CreatMTGraph(G);
	Transpose(GG, G);
	int s;
	int u;
	cout << "输入你需要打印的源节点：";
	cin >> s;
	int Fi = s;
	InitialSingleSource(GG, s);
	List*L = Creatlist(temp);
	for (s = 0; s < GG->v; s++)
	{
		Insert(L, &GG->Edge[s]);
	}
	while (L->next)
	{
		u = Delete(L);
		EdgeNode*p = GG->Edge[u].first;
		while (p)
		{
			Relax(GG,u, p->adjvex, G);
			int s = 0;
			 s =Delete2(L, &GG->Edge[p->adjvex]);
			 if (s != -1)
			 {
				 Insert(L, &GG->Edge[p->adjvex]);
			 }
			
			p=p->next;
		}
	}
	cout << "输入你需要到的目的节点：";
	int Def;
	cin >> Def;
	Print(GG, Fi, Def);
	cout << "最短距离为：" << GG->Edge[Def].weight;
	getchar();
	getchar();
}