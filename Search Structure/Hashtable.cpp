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
	NameList[0].py = "chenliang";//����  
	NameList[1].py = "chenyuanhao";//��Ԫ��  
	NameList[2].py = "chengwenliang";//������  
	NameList[3].py = "dinglei";//����  
	NameList[4].py = "fenghanzao";//�뺺��  
	NameList[5].py = "fuzongkai";//���ڿ�  
	NameList[6].py = "hujingbin";//������  
	NameList[7].py = "huangjianwu";//�ƽ���  
	NameList[8].py = "lailaifa";//������  
	NameList[9].py = "lijiahao";//��κ�  
	NameList[10].py = "liangxiaocong";//������  
	NameList[11].py = "linchunhua";//�ִ���  
	NameList[12].py = "liujianhui";//������  
	NameList[13].py = "luzhijian";//¬־��  
	NameList[14].py = "luonan";//���  
	NameList[15].py = "quegaoxiang";//�ڸ���  
	NameList[16].py = "sugan";//����  
	NameList[17].py = "suzhiqiang";//��־ǿ  
	NameList[18].py = "taojiayang";//�ռ���  
	NameList[19].py = "wujiawen";//�����  
	NameList[20].py = "xiaozhuomin";//Ф׿��  
	NameList[21].py = "xujinfeng"; //����  
	NameList[22].py = "yanghaichun";//���  
	NameList[23].py = "yeweixiong";//Ҷά��  
	NameList[24].py = "zengwei";//����  
	NameList[25].py = "zhengyongbin";//֣Ӻ��  
	NameList[26].py = "zhongminghua";//������  
	NameList[27].py = "chenliyan";//������  
	NameList[28].py = "liuxiaohui";//������  
	NameList[29].py = "panjinmei";//�˽�÷  
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
		Insert(Hashtable[j], NameList[i]);//������Ԫ�ز����ϣ��
	}
	while (1)
	{
		cout <<"ѡ��������еĹ���" << endl;
		cout << "���빦�ܣ�1" << endl;
		cout << "ɾ�����ܣ�2" << endl;
		cout << "���ҹ��ܣ�3" << endl;
		cout << "�˳����ܣ�4" << endl;
		int chioce;
		cin >> chioce;
		switch (chioce)
		{
		case 1:
			for (i = 0; i < 20; i++)
			{
				name[i] = 0;
			}
			cout << "��������";
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
				cout << "����ɹ���" << endl;
			}
			else
			{
				cout << "����ʧ�ܣ�" << endl;
			}
			break;
		case 2:
			for (i = 0; i < 20; i++)
			{
				name[i] = 0;
			}
			cout << "��������";
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
				cout << "ɾ���ɹ���" << endl;
			}
			else
			{
				cout << "ɾ��ʧ��" << endl;
			}
			break;
		case 3:
			for (i = 0; i < 20; i++)
			{
				name[i] = 0;
			}
			cout << "��������";
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
				cout << "���ҵ���Ԫ�أ�" << endl;
			}
			else
			{
				cout << "δ���ҵ���Ԫ�أ�" << endl;
			}
			break;
		case 4:
			exit(0);
		default:
			cout << "�������" << endl;
			break;
		}

	}
}

