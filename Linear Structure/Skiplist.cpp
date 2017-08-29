#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#define Maxlevel 16
#define newnode(n) ((Node*)malloc(sizeof(Node)+n*sizeof(Node*)))
#define min -1000000000
#define max 1000000000
typedef struct node{
	int data;
  struct node* next[1];
}Node;

typedef struct {
	int level;
	Node* head;
}skiplist;
Node*Creatnode(int level,int value)// Make Node
{
	Node*p = newnode(level);
	if (!p)
	{
		return NULL;
	}
	p->data = value;
	return p;
}
skiplist* creathead()//Make Skiplist
{
	skiplist* fir = (skiplist*)malloc(sizeof(skiplist));
	if (!fir)
	{
		return NULL;
	}
	
	Node *ss = Creatnode(Maxlevel-1, min);//At first , Make a minimum flag to make code much easier
	if (!ss)
	{
		free(fir);
		return NULL;
	}
	fir->level = 0;   //In the very beginning,the skiplist'level is 0
	fir->head = ss;
	int i = 0;
	for (i = 0; i < Maxlevel;i++)
	{
		ss->next[i] = NULL;
	}
	return fir;
}
int randomlevel()//To form a random number
{
	int level = 1;
	while (rand() % 2)
	{
		level++;
	}
	if (level > Maxlevel)
	{
		level = Maxlevel;
	}
	return level;
}
int insert(skiplist*sl, int value)
{
	Node*update[Maxlevel];
	int i = 0;
	Node*p =sl->head ;
	Node*q =NULL;
	Node*temp = NULL;
	i = sl->level - 1;
	for (; i >= 0; i--)//从最高层开始找出每一层插入位置的前驱位置并且将其指针更新到update数组里面
	{
		while (  (q = p->next[i]) && value > q->data)
		{
			p = q;
		}
		update[i] = p;
	}
	if (q&&q->data == value)
	{
		printf("This element has existed ！\n");
		return NULL;
	}
	int level = randomlevel();
	temp = Creatnode(level-1, value);
	if (level > sl->level)
	{
		for ( i = sl->level; i < level; i++)
		{
			update[i] = sl->head;        //如果新增层高于原来skiplist的level，则需要将update的在level 和sl->level之间的值指向head
		}
		sl->level=level;//更新level的值
	}
	for (i = level - 1; i >= 0; i--)
	{
		temp->next[i] = update[i]->next[i];//将新的节点进行插入进行插入
		update[i]->next[i] = temp;
	}
	return 1;
}
Node* Search(skiplist*ls ,int value)//搜索函数，返回指针
{
	
	Node*p = ls->head;
	Node*q = NULL;
    int i = ls->level-1;//自顶而下搜索
	for (; i >= 0; i--)
	{
		while ( (q = p->next[i]) && q->data < value)
		{
			p = q;//保存q的前驱元素同时在同一层继续寻找，直到为空或者遇到data>value
		}
		if (q)
		{
			if (q->data == value)
			{
				return(q);
			}
		}
		
	}
	return NULL;
	
}
int Delete(skiplist*ls, int value)
{
	Node*update[Maxlevel];
	Node*p = ls->head;
	Node*q = NULL;
	int i = ls->level - 1;
	int sum = 0;
	for (; i>=0; i--)
	{
		while ((q = p->next[i]) && q->data < value)
		{
			p = q;
		}
		update[i] = p;//保存q的前驱元素同时在同一层继续寻找，直到为空或者遇到data>value，将此值保存在update[i]中
		if (q)
		{
			if (q->data == value)
			{
				sum++;
			}
		}
	}
	if (sum == 0)
	{
		return 0;  
	}
	for (i = ls->level - 1; i >= 0; i--)//开始自顶而下寻找data所在的最高层 ，进行链表删除操作
	{
		if (update[i]->next[i]==q)
		{
			update[i]->next[i] = q->next[i];
			if (ls->head->next[i] == NULL)//删除后如果ls->head后面元素为空说明为最高层此时i--
			{
				ls->level--;
			}
		}
	}
}
int main()
{
	int value;
	int flag;
	skiplist* lis = creathead();
	Node*p = NULL;
	int choice;
	while (1)
	{
		printf("选择你需要的功能：\n");
		printf("插入操作：1\n");
		printf("查找操作：2\n");
		printf("删除操作：3\n");
		printf("退出程序：4\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("输入插入的数据：");
			scanf("%d", &value);
			flag = insert(lis, value);
			if (flag)
			{
				printf("Insert successfully!\n");
			}
			break;
		case 2:
			printf("输入查找的数据：");
			scanf("%d", &value);
		    p=	Search(lis, value);
			if (p)
			{
				printf("Search Successfully!\n");
			}
			else
			{
				printf("This element doesn't exist!\n");
			}
				break;
		case 3:
			printf("输入删除的数据：");
			scanf("%d", &value);
			flag = Delete(lis, value);
			if (flag)
			{
				printf("Delete Successfully!\n");
			}
			else
			{
				printf("Doesn't exist!\n");
			}
			break;
		case 4:
			exit(0);
			break;
		default:
			printf("Input error!\n");
			break;
		}
		
	}
}