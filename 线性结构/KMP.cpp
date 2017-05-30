#pragma warning(disable:4996)
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define Max 1000
int*  ComputeF(char p[])
{
	int m = strlen(p);
	int* pai = (int*)malloc((m+1)*sizeof(int));
	if (!pai)
	{
		printf("申请空间失败！");
		return NULL;
	}
	pai[1] = 0;
	int q;
	int k = 0;
	for (q = 2; q < m; q++)
	{
		while (k >0 && (p[k + 1] != p[q]))
		{
			k = pai[k];
		}
		if (p[k + 1] == p[q])
		{
			k++;
		}
		pai[q] = k;
	}
	return pai;
}
int KMP(char text[],char p[])
{
	int m = strlen(text);
	m--;
	int n = strlen(p);
	n--;
	int i = 0;
	int k = 0;
	int*pai = ComputeF(p);
	int flag = 0;
	for (i = 1; i <= m; i++)
	{
		while (k > 0 && (p[k + 1] != text[i]))
		{
			k = pai[k];
		}
		if (p[k + 1] == text[i])
		{
			k++;
		}
		if (k == n)
		{
			printf("在%d处找到了字符串\n",i-n+1);
			flag = 1;
		}
	}
	return flag;
}
int Copy(char*s1, char*s2)
{
	int i=0;
	while (s1[i] != '\0')
	{
		s2[i + 1] = s1[i];
		i++;
	}
	s2[i + 1] = '\0';
	return 1;
}
int main()
{
	char string1[Max];
	char string2[Max];
	char string3[Max];
	char string4[Max];
	string1[0] = 'a';
	string2[0] = 'b';
	int i = 1;
	printf("输入模式字符串：\n");
	scanf("%s", string3);
	Copy(string3, string1);
	printf("输入文本字符串：\n");
	scanf("%s", string4);
	Copy(string4, string2);
	if (!KMP(string2, string1))
	{
		printf("未能查找到模式字符串\n");
	}
	getchar();
	getchar();
	getchar();

}