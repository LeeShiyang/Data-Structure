#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#define Max 1000
typedef struct {
	int i, j;
	int element;
}Node;
typedef struct{
	Node data[Max+1];
	int row, col, sum;

}Matrix;
int Transpose(Matrix mm, Matrix *s)
{
	int a, b,k,count=1;
	   (*s).col = mm.row;
      (*s).row = mm.col;
	  (*s).sum = mm.sum;
	  for (k = 1; k <= mm.col; k++)
	  {

	        for (a = 1; a<= mm.sum ;a++)
			{
		          if (mm.data[a].j == k)
			  {

					  (*s).data[count].i = k;
					  (*s).data[count].j = mm.data[a].i;
					  (*s).data[count].element = mm.data[a].element;
					  count++;
			  }
		    }
		
	  }
	  return 1;
	
}
int main()
{
	Matrix mm;
	Matrix after;
	int k = 1;
	int number;
	mm.col = 0;
	mm.row = 0;
	mm.sum = 0;
	int value;
	printf("����������Ϣ��(������-1����)\n");
	for (;; k++)
	{
		printf("�����У�\n");
		scanf("%d", &value);
		if (value <= 0)
			break;
		if (value > mm.row)
		{
			mm.row = value;
		}
		mm.data[k].i = value;
		printf("�����У�\n");
		scanf("%d", &value);
		if (value <= 0)
			break;
		if (value > mm.col)
		{
			mm.col = value;
		}
		mm.data[k].j = value;
		printf("������ֵ��\n");
		scanf("%d", &value);
		mm.data[k].element = value;
		mm.sum++;
	}
	if (Transpose(mm,&after))
	{
		printf("ת�óɹ���\n");
		getchar();
	}
	printf("ԭʼ����\n");
	for (k = 1; k <= mm.sum; k++)
	{
		printf("%d  %d  %d\n", mm.data[k].i, mm.data[k].j, mm.data[k].element);
	}
	printf("ת�þ���\n");
	for (k = 1; k <= after.sum; k++)
	{;
		printf("%d  %d  %d\n", after.data[k].i, after.data[k].j, after.data[k].element);
	}
	getchar();
		



	
}