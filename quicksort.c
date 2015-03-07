#include <stdio.h>
#include <stdlib.h>

void swap ( int* a, int* b )
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[],int l,int h)
{
	int x = arr[h];
	int i = (l-1);
	for(int j=1;j<=h-1;j++)
	{
		if(arr[j] <= x)
		{
			i++;
			swap(&arr[i],&arr[j]);
		}
	}
	swap (&arr[i + 1], &arr[h]);
    return (i + 1);
}

void quicksort(int A[],int l, int h)
{
	if (l < h)
	{
		int p = partition(A,l,h);
		quicksort(A,1,p-1);
		quicksort(A,p+1,h);
	}
}
void main()
{
	int a[5] = {8,2,6,1,9};

//	int size = sizeof(a);
//	printf("The size of array is %d \n",size);

	
		quicksort(a,0,4);
	for(int i=0;i<(sizeof(a)/4);i++)
	{
		printf("The element %d is %d\n",i+1,a[i] );
	}	
}