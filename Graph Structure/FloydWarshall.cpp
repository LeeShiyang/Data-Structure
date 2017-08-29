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
			G->Edge[i][j] = Max;
		}
	}
	for (i = 0; i < G->v; i++)
	{
		in >> G->Vet[i];
		G->Edge[i][i] = 0;
	}
	for (i = 0; i < G->e; i++)
	{
		in >> s >> k >> j;
		G->Edge[s][k] = j;
	}
}
void Print(int Pre1[NumVer][NumVer], int i, int j,MTGraph*G)
{
	if (i == j)
	{
		cout <<G->Vet[i]<<" ->";
	}
	else if (Pre1[i][j] == -1)
	{
		cout << "No path to go!";
	}
	else
	{
		Print(Pre1,i,Pre1[i][j] ,G);
		cout <<G->Vet[j]<<" ->";
	}
}
int main()
{
	MTGraph*G = new MTGraph;
	CreatMTGraph(G);
	int row = G->v;
	int S1[NumVer][NumVer][NumVer];
	int Pre1[NumVer][NumVer][NumVer];
	int i, j, k;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < row; j++)
		{
			S1[0][i][j] = G->Edge[i][j];
			if (G->Edge[i][j] < Max&& i != j)
			{
				Pre1[0][i][j] = i;
			}
			else
			{
				Pre1[0][i][j] = -1;
			}
		}
	}
	for (k = 1; k < row; k++)
	{
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < row; j++)
			{
				if (S1[k - 1][i][j]>S1[k - 1][i][k] + S1[k - 1][k][j])
				{
					S1[k][i][j] = S1[k - 1][i][k] + S1[k - 1][k][j];
					Pre1[k][i][j] = Pre1[k-1][k][j];
				}
				else
				{
					S1[k][i][j] = S1[k - 1][i][j];
					Pre1[k][i][j] = Pre1[k-1][i][j];
				}
			}
		}
	}
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < row; j++)
		{
			cout << S1[row - 1][i][j]<<" ";
		}
		cout << endl;
	}
	cout << endl;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < row; j++)
		{
			cout << Pre1[row-1][i][j] << " ";
		}
		cout << endl;
	}
	int Fi, Def;
	cout << "输入源节点和目的节点"<<endl;
		cin >> Fi >> Def;
		if (Fi < row&&Fi >= 0 && Def >= 0 && Def < row)
		{
			Print(Pre1[row - 1], Fi, Def,G);
		}
		else
		{
			cout << "输入错误！";
		}
	getchar();
	getchar();
}