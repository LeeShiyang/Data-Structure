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
		printf("ѡ��������ɵĹ���\n");
		printf("���Ҳ�����1\n");
		printf("���������2\n");
		printf("ɾ��������3\n");
		printf("�˳�����4\n");
		scanf("%d", &value);
		switch (value)
		{
		case 1:
			printf("����������ҵ����ݣ�\n");
			scanf("%d", &value);
			Temp = Search(lis, value);
			if (Temp)
			{
				printf("���ҳɹ�!\n");
			}
			else
			{
				printf("Ԫ�ز��ڸ����ȶ����У�\n");
			}
			break;
		case 2:
			printf("���������������ݣ�\n");
			scanf("%d", &value);
			if (flag = Insert(lis, value))
			{
				printf("����ɹ�!\n");
			}
			else
			{
				printf("����ʧ��!\n");
			}
			break;
		case 3:
			printf("��������ɾ�������ݣ�\n");
			scanf("%d", &value);
			if (flag = Delete(lis, value))
			{
				printf("ɾ���ɹ�!\n");
			}
			else
			{
				printf("ɾ��ʧ��Ϊ��������޴�Ԫ��!\n");
			}
			break;
		case 4:
			exit(0);

		default:
			printf("�������!\n");
			break;
		}
	}
}