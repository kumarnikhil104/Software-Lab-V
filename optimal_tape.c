
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
struct job
{
	int length;
	int job_no;

};
							// Do the memory allcation using heap, 
							//why we have used do while loop and 
							//how we can print only two decimal float value in MRT.
void merge(struct job progm[],int lo,int m,int hi)
{
    int i=0,j=0,k=0;
    int n1=m-lo+1; // because we are also including zero
	int n2=hi-m;
	int temp;
    struct job Sub1[n1],Sub2[n2];
    temp=lo;//-------------
    for(i=0;i<n1;i++,temp++)
    {
        Sub1[i].length= progm[temp].length;
        Sub1[i].job_no= progm[temp].job_no;
    }

    temp=m+1; //------------
    for(i=0;i<n2;i++,temp++)
    {   
        Sub2[i].length=progm[temp].length;
        Sub2[i].job_no=progm[temp].job_no;
    }

    temp=lo;	// bringing back temp to start and i and j to 0
    i=0;
    j=0;
    do
    {
        if(Sub1[i].length<=Sub2[j].length)
        {
            progm[temp].length=Sub1[i].length;
            progm[temp].job_no=Sub1[i].job_no;
            temp++;i++;// incremtting in both ,firstly we are sorting the first sub array
        }
        else		// then we are sorting the 2nd sub aray.
        {
            progm[temp].length=Sub2[j].length;
            progm[temp].job_no=Sub2[j].job_no;
            temp++;j++;
        }
    }while(i<n1&&j<n2);// 

    while(i<n1)// shouldn't we have again made value of i to be zero?????????????????????/// what is happening below this ??
    {
        progm[temp].length=Sub1[i].length;
        progm[temp].job_no=Sub1[i].job_no;
        temp++;i++;
    }
    while(j<n2)
    {
        progm[temp].length=Sub2[j].length;
        progm[temp].job_no=Sub2[j].job_no;
        temp++;j++;
    }
}
void merge_sort(struct job Arr[],int lo,int hi)
{
    if(lo==hi)
        return;
    int m=(hi+lo)/2;
    merge_sort(Arr,lo,m);
    merge_sort(Arr,m+1,hi);
    merge(Arr,lo,m,hi);
}



void main()
{

	int n, sum =0, ans =0;
	printf("\n Enter the No. of job's:\t");
	scanf("%d",&n);
	printf("Enter lengths for the %d jobs:\n",n);

	struct job *progm; // why we are using * here // and in line below where we are typecasting
	progm = (struct job*) malloc (n*sizeof(struct job) );	 
	for(int i=0;i<n;i++)
	{
		scanf("%d",&progm[i].length);
		progm[i].job_no = i+1;
	}

	merge_sort(progm,0,n-1);

	printf("The Optimal Ordering is:\n\n");
	printf(" \tJOb NO------Program No--------Program Length-------Retrival Time \n");

	sum =0;


	for(int i=0;i<n;i++)
	{
		sum+= progm[i].length;
		printf("\t%d\t\t  %d\t\t  %d\t\t  %d\t\n",i+1,progm[i].job_no, progm[i].length,sum);
		ans = ans + sum;		

	}
	printf(" Mean Retrival Time is:\t %.2f \n", (float)ans/n);
	//printf("Mean Retrival Time is:\t %f \n", floorf( (ans/n) * 100 ) /100  );

	free (progm);// freeing the pointer to the memory;
}








