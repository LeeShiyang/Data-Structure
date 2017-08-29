#pragma warning(disable:4996)
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#define Max 30
#define HashLength 5
#define Mod 5
using namespace std;
typedef struct Node{
	int number;
	char* content;
	Node*next;
	Node*front;
}Node;
typedef struct Name{
	char*py;
	int number;
}Name;
void Initial(Name NameList[Max], Node* Hashtable[HashLength])
{
	char*s;
	int i = 0,j;
	int sum = 0;
	NameList[0].py = "chenliang";//陈亮  
	NameList[1].py = "chenyuanhao";//陈元浩  
	NameList[2].py = "chengwenliang";//程文亮  
	NameList[3].py = "dinglei";//丁磊  
	NameList[4].py = "fenghanzao";//冯汉枣  
	NameList[5].py = "fuzongkai";//付宗楷  
	NameList[6].py = "hujingbin";//胡劲斌  
	NameList[7].py = "huangjianwu";//黄建武  
	NameList[8].py = "lailaifa";//赖来发  
	NameList[9].py = "lijiahao";//李嘉豪  
	NameList[10].py = "liangxiaocong";//梁晓聪  
	NameList[11].py = "linchunhua";//林春华  
	NameList[12].py = "liujianhui";//刘建辉  
	NameList[13].py = "luzhijian";//卢志健  
	NameList[14].py = "luonan";//罗楠  
	NameList[15].py = "quegaoxiang";//阙高翔  
	NameList[16].py = "sugan";//苏淦  
	NameList[17].py = "suzhiqiang";//苏志强  
	NameList[18].py = "taojiayang";//陶嘉阳  
	NameList[19].py = "wujiawen";//吴嘉文  
	NameList[20].py = "xiaozhuomin";//肖卓明  
	NameList[21].py = "xujinfeng"; //许金峰  
	NameList[22].py = "yanghaichun";//杨海春  
	NameList[23].py = "yeweixiong";//叶维雄  
	NameList[24].py = "zengwei";//曾玮  
	NameList[25].py = "zhengyongbin";//郑雍斌  
	NameList[26].py = "zhongminghua";//钟明华  
	NameList[27].py = "chenliyan";//陈利燕  
	NameList[28].py = "liuxiaohui";//刘晓慧  
	NameList[29].py = "panjinmei";//潘金梅  
	for (i = 0; i < Max; i++)
	{
		sum = 0;
		s = NameList[i].py;
		for (j = 0; s[j] != '\0'; j++)
		{
			sum = sum + s[j];
		}
		NameList[i].number=sum;
	}
	for (i = 0; i < HashLength; i++)
	{
		Hashtable[i] = new Node;
		Hashtable[i]->next = NULL;
	}
}
int HashFunction(int s)
{
	int data = s%Mod;
	return data;
}
int Insert(Node* L,Name S)
{
	Node*temp;
	Node* New = new Node;
	if (!L->next)
	{
		New->next = L->next;
		L->next = New;
		New->front = L;
	}
	else
	{
		New->next = L->next;
		L->next->front = New;
		L->next = New;
		New->front = L;
	}
	New->content = S.py;
	New->number = S.number;
	return 1;
}
int Find(Node*L, Name S)
{
	int flag = 0;
	Node*temp = L->next;
	while (temp)
	{
		if (temp->content!=S.py)
		{
			temp = temp->next;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}
int Delete(Node*L, Name S)
{
	int flag = 0;
	Node*temp = L;
	Node*G;
	while (temp->next)
	{
		if (temp->next->content!= S.py)
		{
			temp = temp->next;
		}
		else if (temp->next->next)
		{
			G = temp->next;
			temp->next = G->next;
			G->next->front = temp;
			flag = 1;
			return flag;
		}
		else
		{
			temp->next = temp->next->next;
			flag = 1;
			return flag;
		}
	}
	return flag;
}
int main()
{
	Name NameList[Max];
	Node* Hashtable[HashLength];
	Name Temp;
	Initial(NameList, Hashtable);
	char name[20] = { 0 };
	int i;
	int j = 0;
	int sum = 0;
	int Hashvalue;
	for (i = 0; i < Max; i++)
	{
		j = HashFunction(NameList[i].number);
		Insert(Hashtable[j], NameList[i]);//将所有元素插入哈希表
	}
	while (1)
	{
		cout <<"选择你想进行的功能" << endl;
		cout << "插入功能：1" << endl;
		cout << "删除功能：2" << endl;
		cout << "查找功能：3" << endl;
		cout << "退出功能：4" << endl;
		int chioce;
		cin >> chioce;
		switch (chioce)
		{
		case 1:
			for (i = 0; i < 20; i++)
			{
				name[i] = 0;
			}
			cout << "输入姓名";
			scanf("%s", name);
			 sum = 0;
			for (i = 0; i < 20; i++)
			{
				sum = sum + name[i];
			}
			Temp.number = sum;
			Temp.py = name;
			Hashvalue = HashFunction(Temp.number);
			if (Insert(Hashtable[Hashvalue], Temp))
			{
				cout << "插入成功！" << endl;
			}
			else
			{
				cout << "插入失败！" << endl;
			}
			break;
		case 2:
			for (i = 0; i < 20; i++)
			{
				name[i] = 0;
			}
			cout << "输入姓名";
			scanf("%s", name);
			sum = 0;
			for (i = 0; i < 20; i++)
			{
				sum = sum + name[i];
			}
			Temp.number = sum;
			Temp.py = name;
			Hashvalue = HashFunction(Temp.number);
			if (Delete(Hashtable[Hashvalue], Temp))
			{
				cout << "删除成功！" << endl;
			}
			else
			{
				cout << "删除失败" << endl;
			}
			break;
		case 3:
			for (i = 0; i < 20; i++)
			{
				name[i] = 0;
			}
			cout << "输入姓名";
			scanf("%s", name);
			sum = 0;
			for (i = 0; i < 20; i++)
			{
				sum = sum + name[i];
			}
			Temp.number = sum;
			Temp.py = name;
			Hashvalue = HashFunction(Temp.number);
			if (Find(Hashtable[Hashvalue], Temp))
			{
				cout << "查找到该元素！" << endl;
			}
			else
			{
				cout << "未查找到改元素！" << endl;
			}
			break;
		case 4:
			exit(0);
		default:
			cout << "输入错误！" << endl;
			break;
		}

	}
}

