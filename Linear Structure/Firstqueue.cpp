#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#define Min -1000000
typedef struct Node 
{
	int data;
	Node*next;
}Node;
Node* Creatlist()
{
	Node*p = (Node*)malloc(sizeof(Node));
	p->next = NULL;
	p->data = Min;
	return p;
}
int Insert(Node*p, int value)
{
	Node*q = NULL;
	while ((q = p->next) && q->data < value)
	{
		p = q;
	}
	if (q)
	{
		if (q->data == value)
		{
			printf("Data has existed!\n");
			return 0;
		}
	}
	Node* nn = (Node*)malloc(sizeof(Node));
	nn->next = p->next;
	p->next = nn;
	nn->data = value;
	return 1;
}
int Delete(Node*p, int value)
{
	Node*q = NULL;
	while ((q = p->next) && q->data < value)
	{
		p = q;
	}
	if (q)
	{
		if (q->data == value)
		{
			p->next = q->next;
			return 1;
		}
	}
	return 0;

	
}
Node* Search(Node*p, int value)
{
	Node*q = NULL;
	while ((q = p->next) && q->data < value)
	{
		p = q;
	}
	if (q)
	{
		if (q->data == value)
		{
			return q;
		}
	}
	return q;
}
int main()
{
	Node*lis = Creatlist();
	int value;
	int flag;
	Node*Temp = NULL;
	while (1)
	{
		printf("选择你想完成的功能\n");
		printf("查找操作：1\n");
		printf("插入操作：2\n");
		printf("删除操作：3\n");
		printf("退出程序：4\n");
		scanf("%d", &value);
		switch (value)
		{
		case 1:
			printf("输入你想查找的数据：\n");
			scanf("%d", &value);
			Temp = Search(lis, value);
			if (Temp)
			{
				printf("查找成功!\n");
			}
			else
			{
				printf("元素不在该优先队列中！\n");
			}
			break;
		case 2:
			printf("输入你想插入的数据：\n");
			scanf("%d", &value);
			if (flag = Insert(lis, value))
			{
				printf("插入成功!\n");
			}
			else
			{
				printf("插入失败!\n");
			}
			break;
		case 3:
			printf("输入你想删除的数据：\n");
			scanf("%d", &value);
			if (flag = Delete(lis, value))
			{
				printf("删除成功!\n");
			}
			else
			{
				printf("删除失败为空链表或无此元素!\n");
			}
			break;
		case 4:
			exit(0);

		default:
			printf("输入错误!\n");
			break;
		}
	}
}