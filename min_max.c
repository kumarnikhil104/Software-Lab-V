#include<stdio.h>
#include<stdlib.h>

void min_max(int a[],int low,int high, int *min,int *max)
{
	if(low<high)
	{
		int mid = (low+high)/2;
		min_max(a,low,mid,min,max);
		min_max(a,mid+1,high,min,max);
	}
	else
	{
		if(*min > a[low])
			*min = a[low];
		if(*max< a[low])
			*max = a[low];
	}
}

int main()
{
	int n;
	int min, max;
	printf("How many no. to enter: ");
	scanf("%d",&n);
	
	int *a;
	a = (int*) malloc(sizeof(int)*n);
	printf("Enter %d numbers:\n",n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}

	min = a[0];
	max = a[0];

	min_max(a,0,n-1, &min, &max);

	printf("\nMaximum is : %d",max);
	printf("\nMinimum is : %d\n",min);

free(a);

return 0;
}

