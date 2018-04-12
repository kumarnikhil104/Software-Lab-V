#include<stdio.h>
#include<stdlib.h>



int can_be_placed(int r, int c, int *ptr)
{
	int r1,c1;
	for(r1=0;r1<r;r1++)
	{
		c1 = ptr[r1];
		if(c1== c || abs(r1-r) == abs(c1-c) )
			return 0;
	}
// if safe to place then we return true.

	return 1;
}
//-----------------------------------------------------------------

void print_chess(int n,int *ptr)
{
	int i,j,k;

	for(i=0;i<2*n+1;i++)
		printf("-");
	printf("\n");	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("|");
			if( j==ptr[i])
				printf("Q");
			else
				printf(" ");
		}
		printf("|\n");
		for(k=0;k<2*n+1;k++)
			printf("-");
		printf("\n");
	}

}

//----------------------------------------------------------------
void recursive(int n,int sol,int *ptr,int *p,int r) // what is r for here --->>> row no. 
// and c --->>> column no.
{
	int i,j,c;
	static int d; 		// what this d is for?
	
// checing can we place it in that column
	for(c =0;c<n;c++)
	{
		if(can_be_placed(r,c, ptr) )// (row_no, colum_no,ptr to solu vector);
		{
			ptr[r] = c; // saving colum in that row slot.
			
			if(r== n-1) // when we have reached the last row.
			{
				// we have reached the last row and placed a queen means we have a solution so , we are going to increase the count to one.
				(*p)++;
				printf("Solution no.: %d\n",*p);
				printf("1234\n");
				print_chess(n,ptr);

				if(sol == 1)
				{
					d == 1;
					return ;				
				}
			}
			else
			{
				recursive(n,sol,ptr,p,r+1); // going to next row
			}
		}
		if(d==1)
			return;
	}
}
//---------------------------------------------------------------------
int main()
{
	int n;
	int p; // for counting the no. of solutions possible.
	int *ptr; // pointer to ??? solution vector 
	printf("How many queens to place: ");
	scanf("%d",&n);
	if(n<4)
		{printf("No solution exist..!!!");
			return 0;
		}

	else
	{
		p = 0; // currently zero solution.
		ptr= (int*) malloc(sizeof(int)*n);// n slot soution vector.

		//recursive(n,0,ptr,&p,0);
	//(int n,int sol,int *ptr,int *p,int r)

		recursive(n,1,ptr,&p,0);  // when you have to print only one solution
	
	  printf("The total no. of solution in %d Queen Problem is : %d \n ",n,p)	;
	  free(ptr);
	}
return 0;
}
