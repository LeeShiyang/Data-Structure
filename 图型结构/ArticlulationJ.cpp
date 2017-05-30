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
	int Parent;
	EdgeNode*first;
	int child = 0;
	int f = 0;
}Vnode;
typedef struct AdjGraph{
	Vnode Edge[NumVer];
	int v, e;
}AdiGraph;
int num = 0;
int dfn[NumVer];
int low[NumVer];
int flag = 0;
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
		in >> s >> k;
		G->Edge[s][k] = 1;
		G->Edge[k][s] = 1;
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
		for (j = (G->v) - 1; j >= 0; j--)//
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
int Min(int x, int y)
{
	if (x > y)
	{
		return y;
	}
	else
	{
		return x;
	}
}
void DFSVisit(AdjGraph*GG, int fa)
{
	dfn[fa] = low[fa] = ++num;
	GG->Edge[fa].color = 'B';
	//cout << GG->Edge[fa].data;
	EdgeNode *pp = GG->Edge[fa].first;
	int next;
	while (pp)
	{
		next = pp->adjvex;
		if (GG->Edge[next].color == 'W')
		{
			GG->Edge[fa].child++;
			GG->Edge[next].Parent = fa;
			DFSVisit(GG,next);
			low[fa] = Min(low[fa], low[next]);		
			if (low[next] >= dfn[fa] && (GG->Edge[fa].Parent != -1) && (GG->Edge[fa].f==0))
			{
				GG->Edge[fa].f++;
				flag++;
				cout << "割点为：" << GG->Edge[fa].data << endl;
			}
			if (GG->Edge[fa].child > 1 && (GG->Edge[fa].Parent == -1) && (GG->Edge[fa].f == 0))
			{
				GG->Edge[fa].f++;
				flag++;
				cout << "割点为：" << GG->Edge[fa].data << endl;
			}
		}
		else if (next != GG->Edge[fa].Parent)
		{
			low[fa] = Min(dfn[next], low[fa]);
		}

		pp = pp->next;
	}
}
void DFS(AdjGraph*GG)
{
	int i = 0;
	for (i = 0; i < GG->v; i++)
	{
		GG->Edge[i].color = 'W';
		GG->Edge[i].Parent = -1;
	}
	for (i = 0; i < GG->v; i++)
	{
		if (GG->Edge[i].color == 'W')
		{
			DFSVisit(GG, i);
		}
		
	}
}
int main()
{
	MTGraph*G = new MTGraph;
	AdiGraph*GG = new AdiGraph;
	CreatMTGraph(G);
	Transpose(GG, G);
	int i;
	for (i = 0; i < G->v; i++)
	{
		dfn[i] = -1;
		low[i] = -1;
	}
	DFS(GG);
	for (i = 0; i < G->v; i++)
	{
		cout<<dfn[i];
		cout<<low[i]<<endl;
	}
	if (flag == 0)
	{
		cout << "无割点！";
	}
	getchar();
}