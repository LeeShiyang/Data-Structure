#include<stdio.h>
#include<stdlib.h>
#define  Link 0
#define  Thread 1
typedef struct Node{
	char data;
	Node*left;
	Node*right;
	int Rtag, Ltag;
}Node, *Tree;
Node* pre;
Node*post;
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
void Postorder(Tree root)
{
	if (root)
	{
		Postorder(root->left);
		Postorder(root->right);
		printf("%c", root->data);
	}
}
void Postclue(Tree root)
{
	if (root)
	{
			Postclue(root->left);
			Postclue(root->right);
		if (!(root->left))//��������ǰ���ء�
		{
			root->left = pre;
			root->Ltag = Thread;
		}
		if (!(pre->right))//�Ҷ������ҷ���
		{
			pre->right = root;
			pre->Rtag = Thread;
		}
		pre = root;//�ڵ������ڷ��ʵ�һ���ڵ����£��Ա�֤pre��������ϴε�rootֵ
	}
}
void Posttr(Tree&temp, Tree &root)
{
	 temp = new Node;
	temp->right = temp;
	temp->Rtag = Link;
	temp->data = 'N';
	if (root)
	{
		temp->left = root;
		temp->Ltag = Link;
		pre = temp;
		Postclue(root);
		temp->right = pre;//������ڵ㣿
	}
	else
	{
		temp->left = temp;
		temp->Ltag = Link;
	}
}
Tree Findp(Tree Thr, Tree temp)
{
	Tree ss = Thr;
	if (Thr->left == temp)
	{
		return Thr;
	}
	else
	{
		ss = ss->left;
		while (ss->left != temp && ss->right != temp)
		{
			if (ss->Rtag == Link)
			{
				ss = ss->right;
			}
			else
			{
				ss = ss->left;
			}
		}	
	}
	return ss;
}
void Trevll(Tree root,Tree Thr)
{
	Tree temp=Thr->left;
	Tree parent=NULL;
	if (temp == Thr)
	{
		printf("Empty Tree!\n");
	}
	else
	{
		while (true)
		{

			while (temp->Ltag == Link)
			{
				temp = temp->left;
			}
			 if (temp->Rtag == Link)
			{
				temp = temp->right;
			}
			else
			{
				break;
			}
		}
		printf("\n������������Ϊ��\n");
		while (temp != Thr)
		{
			printf("%c", temp->data);
			parent = Findp(Thr, temp);
			if (parent == Thr)
			{
				temp = Thr;
			}
			else if (temp == parent->right || parent->Rtag == Thread)//���Ϊ�Ҷ��ӻ���Ϊû���ֵܵ������ֱ�ӷ��ʸ��ڵ�
			{
				temp = parent;
			}
			else
			{
				while (parent->Rtag == Link)
				{
					parent = parent->right;
					while (parent->Ltag == Link)
					{
						parent = parent->left;
					}
				}
				temp = parent;
			}
		}
	}
}
int main()
{
	Tree root ,Thr;
	Initial(root);
	printf("�����������������#����\n");
	Creattree(root);
	printf("�ݹ������������ǣ�\n");
	Postorder(root);
	Posttr(Thr,root);
	Trevll(root, Thr);
	getchar();
	getchar();
}