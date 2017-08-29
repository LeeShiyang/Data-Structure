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
	printf("初始化成功！\n");

}
void Creattree(Tree &root)//递归的建立二叉树，输入顺序为中根顺序
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
void PreTrave(Tree &root)//前序顺序递归的访问二叉树
{
	if (root)
	{
		printf("%c", root->data);
		PreTrave(root->left);
		PreTrave(root->right);
	}
}
void Creattree2(Ftree &root)//递归的建立二叉树，输入顺序为中根顺序
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
void Trave(Ftree &root)//前序顺序递归的访问二叉树
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
	printf("输入相应森林（以先序顺序输入（空用#表示））\n");
	Creattree2(Forest);
	printf("森林先序输入顺序为：\n");
	Trave(Forest);
	Transpose(Forest, root);
	printf("\n二叉树先序输入顺序为：\n");
	PreTrave(root);
	Transpose1(Forest1, root);
	printf("\n森林先序输入顺序为：\n");
	Trave(Forest1);
	getchar();
	getchar();

}