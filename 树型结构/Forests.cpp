#include<stdio.h>
#include<stdlib.h>
#define  Link 0
#define  Thread 1
typedef struct Node{
	char data;
	Node*left;
	Node*right;
}Node, *Tree;
typedef struct TNode{
	char data;
	TNode*lmost;
	TNode*rsib;
}TNode,*Ftree;
void Initial(Tree&root)
{
	root = NULL;
	printf("��ʼ���ɹ���\n");

}
void Creattree(Tree &root)//�ݹ�Ľ���������������˳��Ϊ�и�˳��
{
	char let;
	let = getchar();
	if (let != '#')
	{
		root = (Tree)malloc(sizeof(Node));
		root->data = let;
		root->left = NULL;
		root->right = NULL;
		Creattree(root->left);
		Creattree(root->right);
	}

}
void PreTrave(Tree &root)//ǰ��˳��ݹ�ķ��ʶ�����
{
	if (root)
	{
		printf("%c", root->data);
		PreTrave(root->left);
		PreTrave(root->right);
	}
}
void Creattree2(Ftree &root)//�ݹ�Ľ���������������˳��Ϊ�и�˳��
{
	char let;
	let = getchar();
	if (let != '#')
	{
		root = (Ftree)malloc(sizeof(TNode));
		root->data = let;
		root->lmost = NULL;
		root->rsib = NULL;
		Creattree2(root->lmost);
		Creattree2(root->rsib);
	}
}
void Trave(Ftree &root)//ǰ��˳��ݹ�ķ��ʶ�����
{
	if (root)
	{
		printf("%c", root->data);
		Trave(root->lmost);
		Trave(root->rsib);
	}
}
void Transpose(Ftree&tree, Tree&root)
{
	if (tree)
	{
		root = (Tree)malloc(sizeof(Node));
		root = (Tree)malloc(sizeof(Node));
		root->data = tree->data;
		root->left = NULL;
		root->right = NULL;
		Transpose(tree->lmost,root->left);
		Transpose(tree->rsib,root->right);
	}
}
void Transpose1(Ftree&tree, Tree&root)
{
	if (root)
	{
		tree = (Ftree)malloc(sizeof(TNode));
		tree->data = root->data;
		tree->lmost = NULL;
		tree->rsib = NULL;
		Transpose1(tree->lmost, root->left);
		Transpose1(tree->rsib, root->right);
	}
}
int main()
{
	Ftree Forest,Forest1;
	Tree root;
	printf("������Ӧɭ�֣�������˳�����루����#��ʾ����\n");
	Creattree2(Forest);
	printf("ɭ����������˳��Ϊ��\n");
	Trave(Forest);
	Transpose(Forest, root);
	printf("\n��������������˳��Ϊ��\n");
	PreTrave(root);
	Transpose1(Forest1, root);
	printf("\nɭ����������˳��Ϊ��\n");
	Trave(Forest1);
	getchar();
	getchar();

}