#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<iostream>
#define NumVer 50
#define NumEgde 50
#define Max 10000
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
	char data;
	char color;
	Vnode*Parent;
	EdgeNode*first;
	int d = 0;
	int f = 0;
}Vnode;
typedef struct AdjGraph{
	Vnode Edge [NumVer];
	int v, e;
}AdiGraph;
typedef struct List{
	List*next;
	Vnode* value;
}List;
void CreatMTGraph(MTGraph* G)
{
	int i, j,s,k;
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
			in >> s >> k;
			G->Edge[s][k] = 1;
	}
	/*for (i = 0; i < G->v; i++)
	{
		cout << G->Vet[i];
		for (j = 0; j < G->v; j++)
		{
			if (G->Edge[i][j])
				cout << i << j << endl;
		}
	}*/
}
int time = 0;
void DFSVisit(AdjGraph*GG, int i)
{
	time++;
	GG->Edge[i].d = time;
	cout << GG->Edge[i].data;
	GG->Edge[i].color = 'B';
	EdgeNode*pp = GG->Edge[i].first;
	int next;
	while (pp)
	{
		next = pp->adjvex;
		if (GG->Edge[next].color == 'W')
		{
			DFSVisit(GG, next);
		}		
			pp = pp->next;		
		
	}
	time++;
	GG->Edge[i].f = time;
}
void DFS(AdjGraph* GG)
{
	int i;
	for (i = 0; i < GG->v; i++)
	{
		GG->Edge[i].color = 'W';
		GG->Edge[i].Parent = NULL;
	}
	for (i = 0; i < GG->v; i++)
	{
		if (GG->Edge[i].color == 'W')
		{
			DFSVisit(GG, i);
		}
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
		GG->Edge[i].first = NULL;
	}
	for (i = 0; i < G->v; i++)
	{
		for (j =( G->v)-1; j >=0; j--)//结果是否一样？
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
void MatrixTs(MTGraph* G, MTGraph* GT)
{
	int i, j;
	GT->e = G->e;
	GT->v = G->v;
	for (i = 0; i < G->v; i++)
	{
		for (j = 0; j < G->v; j++)
		{
			GT->Edge[i][j] = 0;
		}
	}
	for (i = 0; i < GT->v; i++)
	{
		GT->Vet[i] = G->Vet[i];
	}
	for (i = 0; i < G->v; i++)
	{
		for (j = 0; j < G->v; j++)
		{
			if (G->Edge[i][j])
			{
				GT->Edge[j][i] = 1;
			}
			
		}
	}

}

List* Creatlist(Vnode*temp)
{
	List*p = (List*)malloc(sizeof(List));
	p->next = NULL;
	p->value = temp;
	p->value->f = Max;
	return p;
}
int Insert(List*p, Vnode* value)
{
	List*q = NULL;
	while ((q = p->next) && q->value->f > value->f)
	{
		p = q;
	}
	List* nn = (List*)malloc(sizeof(List));
	nn->next = p->next;
	p->next = nn;
	nn->value = value;
	return 1;
}
Vnode* Delete(List*p)
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
	return q;
}
Vnode* Top(List*p)
{
	if (!p->next)
	{
		return NULL;
	}
	return p->next->value;
}
void DFSVisit2(AdjGraph*GG, int i,List*p)
{
	cout << GG->Edge[i].data;
	Delete(p);
	GG->Edge[i].color = 'B';
	EdgeNode*pp = GG->Edge[i].first;
	int next;
	while (pp)
	{
		next = pp->adjvex;
		if (GG->Edge[next].color == 'W')
		{
			DFSVisit2(GG, next,p);
		}
		pp = pp->next;

	}
}
void DFS2(AdjGraph* GG,List*p)
{
	int i,next;
	Vnode* visit = Top(p);
	EdgeNode*temp = NULL;
	temp = visit->first;
	for (i = 0; i < GG->v; i++)
	{
		GG->Edge[i].color = 'W';
		GG->Edge[i].Parent = NULL;
	}
	while (Top(p))
	{
		visit = Top(p);
		for (i = 0; i < GG->v; i++)
		{
			if (visit->data == GG->Edge[i].data)
			{
				break;
			}
		}
		DFSVisit2(GG, i,p);
		cout << endl;
	}
}

int main()
{
	int i,j;
	MTGraph* G = new MTGraph;
	MTGraph* GT = new MTGraph;
	AdjGraph*GG = new AdjGraph;
	AdjGraph*GTT = new AdjGraph;
	Vnode*temp = new Vnode;
	CreatMTGraph(G);
	Transpose(GG, G);
	DFS(GG);
	MatrixTs(G, GT);	
	Transpose(GTT, GT);
	for (i = 0; i < G->v; i++)
	{
		for (j = 0; j < G->v; j++)
		{
			if (GG->Edge[i].data == GTT->Edge[j].data)
			{
				GTT->Edge[j].f = GG->Edge[i].f;
			}
		}
	}
	cout << endl;
	List* p = Creatlist(temp);
	for (i = 0; i < G->v; i++)
	{
		Insert(p, &(GTT->Edge[i]));
	}
	DFS2(GTT, p);
	getchar();
	getchar();
}
