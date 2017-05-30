#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;
typedef struct node{
	int bf;
	node*lchild;
	node*rchild;
	int data;
}node;
typedef node* Tree;
int unbalance = false;
int change = false;
void Leftrotation(Tree&T)
{
	Tree lc, gc;
	lc = T->lchild;
	if (lc->bf == 1)//LL Rotation
	{
		T->lchild = lc->rchild;
		lc->rchild = T;
		T->bf = 0;
		T = lc;
	}
	else//LR Rotation
	{
		gc = lc->rchild;
		T->lchild = gc->rchild;
		lc->rchild = gc->lchild;
		gc->lchild = lc;
		gc->rchild = T;
		switch (gc->bf)
		{
		case -1:
			T->bf = 0;
			lc->bf = 1;
			break;
		case 0:
		    T->bf = lc->bf = 0;
			break;
		case 1:
			T->bf = -1;
			lc->bf = 0;
			break;
		default:
			break;
		}
		T = gc;
	}
	T->bf = 0;
	unbalance = false;
}
void Rightrotation(Tree&T)
{
	Tree lc, gc;
	lc = T->rchild;
	if (lc->bf == -1)
	{
		T->rchild = lc->lchild;
		lc->lchild = T;
		T->bf = 0;
		T = lc;
	}
	else
	{
		gc = lc->lchild;
		T->rchild = gc->lchild;
		lc->lchild = gc->rchild;
		gc->lchild = T;
		gc->rchild = lc;
		switch (gc->bf)
		{
		case 1:
			T->bf = 0;
			lc->bf = -1;
			break;
		case 0:
			T->bf = 0;
			lc->bf = 0;
			break;
		case -1:
			T->bf = 1;
			lc->bf = 0;
			break;
		default:
			break;
		}
		T = gc;
	}
	T->bf = 0;
	unbalance = false;
}
void Insert(Tree &T,int data)
{
	if (!T)
	{
		T = new node;
		T->bf = 0;
		T->data = data;
		T->lchild = NULL;
		T->rchild = NULL;
		unbalance = true;
		cout << "插入成功" << endl;
	}
	if (data < T->data)
	{
		Insert(T->lchild, data);
		if (unbalance)
		{
			switch (T->bf)
			{
			case -1:
				T->bf = 0;
				unbalance = false;
				break;
			case 0:
				T->bf = 1;
				break;
			case 1:
				Leftrotation(T);
				break;
			default:
				break;
			}
		}
	}
	else if (data > T->data)
	{
		Insert(T->rchild,data);
		if (unbalance)
		{
			switch (T->bf)
			{
			case -1:
				Rightrotation(T);
				break;
			case 0:
				T->bf = -1;
				break;
			case 1:
				T->bf = 0;
				unbalance = false;
				break;
			default:
				break;
			}
		}
	}
}
int  Search(Tree T, int data)
{
	if (T == NULL)
	{
		return 0;
	}
	else
	{
		while (T)
		{
			if (T->data == data)
			{
				return 1;
			}
			else if (T->data < data)
			{
				T = T->rchild;
			}
			else
			{
				T = T->lchild;
			}
		}
	}
	return 0;
}
void R_rote(Tree& T)
{
	Tree lc;
	lc = T->lchild;
	T->lchild = lc->rchild;
	lc->rchild = T;
	T = lc;

}
void L_rote(Tree&T)
{
	Tree lc, gc;
	lc = T->rchild;
	T->rchild = lc->lchild;
	lc->lchild = T;
	T = lc;
}
void Leftbalance(Tree &T)
{
	Tree lc, gc;
	lc = T->lchild;
	switch (lc->bf)
	{
	case -1:
		gc = lc->rchild;
		switch (gc->bf)
		{
		case -1:
			T->bf = 0;
			lc->bf = 1;
			break;
		case 0:
			T->bf = lc->bf = 0;
			break;
		case 1:
			T->bf = -1;
			lc->bf = 0;
			break;
		}
		gc->bf = 0;
		T->lchild = gc->rchild;
		lc->rchild = gc->lchild;
		gc->lchild = lc;
		gc->rchild = T;
		T = gc;
		break;
	case 0:
		change = false;//外加部分测试
		lc->bf = -1;
		T->bf = 1;
		R_rote(T);
		break;
	case 1:
		lc->bf = 0;
		T->bf = 0;
		R_rote(T);
		break;
	}
		
}
void Rightbalance(Tree &T)
{
	Tree lc, gc;
	lc = T->rchild;
	switch (lc->bf)
	{
	case -1:
		lc->bf = 0;
		T->bf = 0;
		L_rote(T);
		break;
	case 0:
		lc->bf = 1;
		T->bf = -1;
		change = false;//外加部分测试
		L_rote(T);
		break;
	case 1:
		gc = lc->lchild;
		switch (gc->bf)
		{
		case 1:
			T->bf = 0;
			lc->bf = -1;
			break;
		case 0:
			T->bf = 0;
			lc->bf = 0;
			break;
		case -1:
			T->bf = 1;
			lc->bf = 0;
			break;
		}
		gc->bf = 0;
		gc = lc->lchild;
		T->rchild = gc->lchild;
		lc->lchild = gc->rchild;
		gc->lchild = T;
		gc->rchild = lc;
		T = gc;
		break;
	}
}
int Delete(Tree&T, int data)
{
	Tree L1, L2;
	int flag = 0;
	int tag;
	if (T == NULL)
	{
		flag = 0;
		return  flag;
	}
	if (T->data == data)
	{
		change = true;
		if (!T->rchild)
		{
			L1 = T;
			T=T->lchild;
			free(L1);
			return  1;
		}
		else
		{
			L2 = T->rchild;
			while (L2->lchild)
			{
				L2 = L2->lchild;
			}
			T->data = L2->data;
		  flag=	Delete(T->rchild, L2->data);
		  tag = 1;
		}
	}
	else if (T->data<data)
	{
		flag = Delete(T->rchild, data);
		tag = 1;
	}
	else
	{
		flag = Delete(T->lchild, data);
		tag = -1;
	}
	if (change)
	{
		if (tag == 1)//删除的右子树
		{
			switch (T->bf)
			{
			case -1:
				T->bf = 0;
				change = true;
				break;
			case 0:
				T->bf = 1;
				change =false;
				break;
			case 1:
				Leftbalance(T);
				break;
			default:
				break;
			}
		}
		else//删除左子树
		{
			switch (T->bf)
			{
			case -1:
				change = true;
				Rightbalance(T);
				break;
			case 0:
				change = false;
				T->bf = -1;
				break;
			case 1:
				T->bf = 0;
				change = true;
				break;
			default:
				break;
			}

		}		
	}
	return flag;
}
void Travel(Tree T)
{
	if (T)
	{
		cout << T->data<<" " <<T->bf<< " ";
		Travel(T->lchild);
		Travel(T->rchild);
	}
}
int main()
{
	int data;
	Tree T = NULL;
	int choice;
	int  flag = 0;
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
			Insert(T, data);
			break;
		case 2:
			cout << "输入你想查找的数据" << endl;
			cin >> data;
			flag = Search(T,data);
			if (flag)
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
			flag = Delete(T, data);
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
			Travel(T);
			break;
		default:
			cout << "输入错误" << endl;
			break;
		}
	}		
}