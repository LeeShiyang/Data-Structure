#include<stdio.h>
#include<stdlib.h>
#define  Link 0
#define  Thread 1
typedef struct Node{
	char data;
	Node*left;
	Node*right;
	int Rtag, Ltag;
}Node,*Tree;
Node* pre;
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
		root->Ltag = Link;
		root->Rtag = Link;
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
void Prethread(Tree &root)//递归的建立二叉树的线索
{
	if (root)
	{
		if (!(root->left))//左儿子为空，将左指针指向前序顺序的上一个节点
		{
			root->left = pre;
			root->Ltag = Thread;
		}
		if ((!pre->right))//因为root是pre的后继节点，所以如果pre的右子树为空，则将root赋值给pre
		{
			pre->right = root;
			pre->Rtag = Thread;
		}
		pre = root;
		if (root->Ltag == Link)
		{
			Prethread(root->left);
		}
		if (root->Rtag == Link)
		{
			Prethread(root->right);
		}
	}
}
void Travel(Tree root)
{
	if (root)
	{
		if (root->Ltag == Link)
		{
			Travel(root->left);
		}
		printf("%c", root->data);
		if (root->Rtag == Link)
		{
			Travel(root->right);
		}
	}
}
Tree Precluet(Tree &root)
{
	Tree temp = (Tree)malloc(sizeof(Node));

	temp->right = temp;
	temp->Ltag = Link;
	temp->Rtag = Thread;
	if (root)
	{
		temp->left = root;
		pre = temp;
		Prethread(root);
		pre->right = temp;
		pre->Rtag = Thread;
		temp->right = pre;
	}
	else
	{
		temp->left = temp;
	}
	return temp;
}



void preordertravel(Tree &temp)
{
	Tree p = temp->left;
	while (p != temp)
	{
		printf("%c", p->data);
		if (p->Ltag == Link)
		{
			p=p->left;
		}
		else
		{
			p = p->right;
		}
	}
	

	
}
int main()
{
	Tree temp;
	Tree root;
	Initial(root);
	printf("输入二叉树，空置以#代表\n");
	Creattree(root);
	printf("递归前序遍历序列是：\n");
	PreTrave(root);
	temp = Precluet(root);
	printf("\n非递归前序访问序列为：\n");
	preordertravel(temp);
	printf("\n前序线索中序遍历：\n");
	Travel(root);
	getchar();
	getchar();
}