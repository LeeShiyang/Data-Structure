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
		root->Ltag = Link;
		root->Rtag = Link;
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
void Prethread(Tree &root)//�ݹ�Ľ���������������
{
	if (root)
	{
		if (!(root->left))//�����Ϊ�գ�����ָ��ָ��ǰ��˳�����һ���ڵ�
		{
			root->left = pre;
			root->Ltag = Thread;
		}
		if ((!pre->right))//��Ϊroot��pre�ĺ�̽ڵ㣬�������pre��������Ϊ�գ���root��ֵ��pre
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
	printf("�����������������#����\n");
	Creattree(root);
	printf("�ݹ�ǰ����������ǣ�\n");
	PreTrave(root);
	temp = Precluet(root);
	printf("\n�ǵݹ�ǰ���������Ϊ��\n");
	preordertravel(temp);
	printf("\nǰ���������������\n");
	Travel(root);
	getchar();
	getchar();
}