#pragma warning(disable :4996)
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<time.h>
#define K 1000//区间在0-k之间的整数
#define Max 5000000//
#define D 7//整数
using namespace std;
int repete = 0;
int c[K + 1];
void count_sort(int b[],int arr[])
{
	int i;
	for (i = 0; i <= K; i++)
	{
		c[i] = 0;
	}
	for (i = 0; i < Max; i++)
	{
		c[arr[i]] = c[arr[i]]++;
	}
	for (i = 0; i < K; i++)
	{
		c[i + 1] = c[i] + c[i + 1];
	}
	for (i = Max - 1; i >= 0; i--)
	{
		b[c[arr[i]]-1] = arr[i];
		c[arr[i]] = c[arr[i]] - 1;
	}
}
vector<float> B[Max];
vector<float>::iterator it;
void Bucket_sort(float A[Max])
{
	int i;
	for (i = 0; i < Max; i++)
	{
		B[i].clear();
	}
	for (i = 0; i < Max; i++)
	{
		int k = (int)A[i] * Max;
		B[k].push_back(A[i]);
	}
	for (i = 0; i < Max; i++)
	{
		sort(B[i].begin(), B[i].end());
	}
}
void Bubblesort(int A[Max])
{
	int i, j;
	for (i = 0; i <= Max - 1; i++)
	{
		for (j = 0; j < Max - 1 - i; j++)
		{
			if (A[j]>A[j+1])
			{
				swap(A[j], A[j + 1]);
			}
		}
	}
	for (i = 0; i < Max; i++)
	{
		cout << A[i] << " ";
	}
}
void Insertsort(int A[Max],int low ,int high)
{
	int i, j,temp;
	for (i = low+1; i <= high; i++)
	{
		j = i;
		temp = A[i];
		while ((j>=0)&&temp<A[j - 1])
		{
			A[j] = A[j - 1];
			j--;
		}
		swap(A[j], temp);
	}
	/*for (i = 0; i < Max; i++)
	{
		cout << A[i] << " ";
	}*/
}
void Cmpsort(int A[Max])
{
	int i, j;
	for (i = 0; i < Max; i++)
	{
		for (j = i; j < Max; j++)
		{
			if (A[i]>A[j])
			{
				swap(A[i], A[j]);
			}
		}
	}
	for (i = 0; i < Max; i++)
	{
		cout << A[i] << " ";
	}
}
int Getkvalue(int data, int d)
{
	int a[] = { 1, 1, 10, 100,1000,10000,100000,1000000,10000000 };
	return (data / a[d]) % 10;
}
int Bucket[Max];
void Lsdradix(int* arr, int d)
{
	int k;
	int radix = 10;
	int count[10];
	int i,j;
	for (k = 1; k <= d; k++)
	{
		for (i = 0; i < radix; i++)
		{
			count[i] = 0;
		}
		for (i = 0; i < Max; i++)
		{
			int value = Getkvalue(arr[i], k);
			count[value]++;
		}
		for (i = 0; i < radix-1; i++)
		{
			count[i + 1] = count[i] + count[i + 1];
		}
		for (i = Max - 1; i >= 0; i--)
		{
			int value = Getkvalue(arr[i], k);
			Bucket[count[value] - 1] = arr[i];
			count[value]--;
		}
		for (i = 0, j = 0; i < Max; i++, j++)
		{
			arr[i] = Bucket[j];
		}
	}
}
int Pivot(int arr[], int low, int high)//快排优化三个随机选取中值法是的有序数组能够快速完成快排
{
	int mid = low + (high - low) / 2;
	if (arr[mid] > arr[high])//确保arr[high]大于等于mid
	{
		swap(arr[mid], arr[high]);
	}
	if (arr[low] > arr[high])
	{
		swap(arr[low], arr[mid]);
	}
	if (arr[low] > arr[mid])//至此三个数排序完毕
	{
		swap(arr[low], arr[mid]);
	}
	swap(arr[mid], arr[high]);
	return arr[high];
}
int Pation(int* arr, int low, int high)//处理大量重复出现的情况
{
	int pivot = Pivot(arr,low,high);
	int i = low-1;
	int j = low;
	repete = 0;
	for (j = low; j < high; j++)
	{
		if (arr[j] <= pivot)
		{
			if (arr[j] == pivot)
			{
				repete++;
			}
			i++;
			swap(arr[j], arr[i]);
		}
	}
		swap(arr[i+1], arr[j]);
		int judge = i;
		for (j = i ;j>=low; j--)
		{
			if (arr[j] == pivot)
			{
				swap(arr[j], arr[judge]);
				judge--;
			}
		}
	    return i+1;
}
void Qsort(int *arr, int low, int high)
{
	if (high > low)
	{
			int flag = Pation(arr, low, high);
			Qsort(arr, low, flag - 1-repete);
			Qsort(arr, flag + 1, high);
	}
}
void Print(int arr1[])
{
	int i;
	cout << endl;
	for (i = 0; i < Max; i++)
	{
		cout << arr1[i] << " ";
	}
}
int arr1[Max];
int b[Max];
float A[Max] ;
int main()
{
	//freopen("sort.out", "w", stdout);
	int i,j;
	int k;
	srand(time(NULL));
	for (i = 0; i < Max; i++)
	{
		
		arr1[i] = rand();//A[i] =0.1; //rand() % K;///;(rand() % K)*1.0 / K;//
	}
	clock_t fir, end;
	fir = clock();
	Qsort(arr1, 0, Max - 1);
	 // Lsdradix(arr1, D);
	//Insertsort(arr,0,Max-1);
	//Cmpsort(arr);
	//Bubblesort(arr);
	// Bucket_sort(A);
	//count_sort(b,arr1);
	 end = clock();
	double time = (double)(end - fir) / CLOCKS_PER_SEC;
	printf("Cost time %.6lf", time);
	//Print(arr1);
	getchar();
}