#include<iostream>
using namespace std;
typedef int key;
typedef struct Node{
	char color;
	int data;
	Node* left;
	Node* right;
	Node* p;
}Node;
typedef Node* Rbtree;
Node* Nil = new Node;
void Leftrotation(Rbtree &root,Rbtree  x)
{
	Node*y = x->right;
	if (y == Nil)
	{
		cout << "左旋中x的右儿子为空无法进行左旋操作！" << endl;
	}
	else{
		x->right = y->left;
		if (y->left != Nil)
		{
			y->left->p = x;
		}
		y->p = x->p;
		if (x->p == Nil)
		{
			root = y;
		}
		else if (x == x->p->left)
		{
			y->p->left = y;
		}
		else
		{
			y->p->right = y;
		}
		y->left = x;
		x->p = y;
	}
}
void Rightrotation(Rbtree&root, Rbtree y)
{
	Rbtree x = y->left;
	if (x == Nil)
	{
		cout << "y的左儿子为空无法进行右旋操作！" << endl;
	}
	else
	{
		y->left = x->right;
		if (x->right != Nil)
		{
			x->right->p = y;
		}
		x->p = y->p;
		if (y->p == Nil)
		{
			root = x;
		}
		else if (y==y->p->left)
		{
			x->p->left=x;
		}
		else
		{
			 x->p->right =x;
		}
		y->p = x;
		x->right = y;
	}
}
void RbInsertAdjust(Rbtree&root, Rbtree z)
{
	Rbtree y;
	while (z->p->color == 'R')
	{
		if (z->p == z->p->p->left)
		{
			y = z->p->p->right;
			if (y->color == 'R')//case 1
			{
				z->p->p->color = 'R';
				z->p->color = 'B';
				y->color = 'B';
				z = z->p->p;
			}
			else 
			{
				if (z == z->p->right)//case 2
				{
					z = z->p;
					Leftrotation(root, z);
				}
				z->p->color = 'B';   //case 3
				z->p->p->color = 'R';
				Rightrotation(root, z->p->p);
				
			}
		}
		else
		{
			y = z->p->p->left;
			if (y->color == 'R')//case 4
			{
				z->p->p->color = 'R';
				z->p->color = 'B';
				y->color = 'B';
				z = z->p->p;
			}
			else if (z == z->p->left)//case 5
			{
				z = z->p;
				Rightrotation(root, z);
			}
			else //case 6
			{
				z->p->color = 'B';
				z->p->p->color = 'R';
				Leftrotation(root, z->p->p);
			}
		}
	}
	root->color = 'B';
}
void RbInsert(Rbtree&root, Rbtree z)
{
	Rbtree y = Nil;
	Rbtree x = root;
	while (x != Nil)//保证了一开始root一开始为Nil时也能直接进行插入
	{
		y = x;
		if (z->data < x->data)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	z->p = y;
	if (y == Nil)
	{
		root = z;
	}
	else if (z->data<y->data)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}
	z->left = Nil;
	z->right = Nil;
	z->color = 'R';
	RbInsertAdjust(root, z);
}
void Travel(Rbtree root)
{
	if (root != Nil)
	{
		cout << root->data << root->color << " ";
		Travel(root->left);
		Travel(root->right);
	}
}
void Travell(Rbtree root)
{
	if (root != Nil)
	{
		Travel(root->left);
		cout << root->data << root->color << " ";
		Travel(root->right);
	}
}
Rbtree  Search(Rbtree root, int data)
{
	if (root == Nil)
	{
		return NULL;
	}
	else
	{
		while (root != Nil)
		{
			if (root->data == data)
			{
				return root;
			}
			else if (root->data < data)
			{
				root = root->right;
			}
			else
			{
				root = root->left;
			}
		}
	}
	return NULL;
}
void  Rbtransplant(Rbtree&root, Rbtree f, Rbtree d)
{
	if (f->p == Nil)
	{
		root = d;
	}
	else if (f==f->p->left)
	{
		 f->p->left=d;
	}
	else
	{
		 f->p->right=d;
	}
	d->p = f->p;
}
Rbtree Minimum(Rbtree u)
{
	while (u->left != Nil)
	{
		u = u->left;
	}
	return u;
}
void RbDeleteAdjust(Rbtree &root,Rbtree x)
{
	Rbtree w;
	while (x != root&&x->color == 'B')
	{
		if (x == x->p->left)
		{
			w = x->p->right;
			if (w->color == 'R')
			{
				x->p->color = 'R';
				w->color = 'B';
				Leftrotation(root, x->p);
				w = x->p->right;
			}
			if (w->left->color == 'B'&&w->right->color == 'B')
			{
				w->color = 'R';
				x = x->p;
			}
			else 
			{
				if (w->right->color == 'B')
				{
					w->left->color = 'B';
					w->color = 'R';
					Rightrotation(root, w);
					w = w->p;//是否会出错
				}
				w->color = x->p->color;
				x->p->color = 'B';
				w->right->color = 'B';
				Leftrotation(root,x->p);
				x = root;
			}	
		}
		else{
			w = x->p->left;
			if (w->color == 'R')
			{
				x->p->color = 'R';
				w->color = 'B';
				Rightrotation(root, x->p);
				w = x->p->left;
			}
			if (w->right->color == 'B'&&w->left->color == 'B')
			{
				w->color = 'R';
				x = x->p;
			}
			else
			{
				if (w->left->color == 'B')
				{
					w->right->color = 'B';
					w->color = 'R';
					Leftrotation(root, w);
					w = w->p;
				}
				w->color = x->p->color;
				x->p->color = 'B';
				w->left->color = 'B';
				Rightrotation(root, x->p);
				x = root;
			}
			
		}
	}
	x->color = 'B';
}
int RbDelete(Rbtree&root, Rbtree z)
{
	Rbtree y = z;
	Rbtree x;
	char original_y = y->color;
	if (z->left == Nil)
	{
		x = z->right;
		Rbtransplant(root, z, z->right);
	}
	else if (z->right == Nil)
	{
		x = z->left;
		Rbtransplant(root, z, z->left);
	}
	else
	{
		y = Minimum(z->right);
		original_y = y->color;
		x = y->right;
		z->data = y->data;
		Rbtransplant(root, y, x);
	}
	if (original_y == 'B')
	{
		RbDeleteAdjust(root, x);
	}	
	return 1;
}
int main()
{
	Nil->color = 'B';
	Nil->data = -1;
	Nil->right = NULL;
	Nil->left = NULL;
	Nil->p = NULL;
    Rbtree root = Nil;
	Rbtree back = NULL;
	int choice;
	int  flag = 0;
	int data;
	Rbtree z;
	while (1)
	{
		cout << "输入你想选择的功能:" << endl;
		cout << "插入数据:1" << endl;
		cout << "查找数据:2" << endl;
		cout << "删除数据:3" << endl;
		cout << "前序遍历：4" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "输入你想插入的数据" << endl;
			cin >> data;
			z = new Node;
			z->data = data;
			RbInsert(root,z);
			break;
		case 2:
			cout << "输入你想查找的数据" << endl;
			cin >> data;			 
			if (Search(root, data))
			{
				cout << "查找到输入数据" << endl;
			}
			else
			{
				cout << "未找到输入数据" << endl;
			}
			break;
		case 3:
			cout << "输入你想要删除的数据" << endl;
			cin >> data;
			back = Search(root, data);
			flag = 0;
			if (back)
			{
				flag = RbDelete(root, back);
			}
			if (flag)
			{
				cout << "已经删除输入数据" << endl;
			}
			else
			{
				cout << "未找到输入数据" << endl;
			}
			break;
		case 4:
			//Travel(root);
			//Travell(root);
			break;
		default:
			cout << "输入错误" << endl;
			break;
		}
	}	
	return 0;
}