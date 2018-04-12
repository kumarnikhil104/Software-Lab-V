#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* 
Provided grammar is :

S -> A1B
A -> 0A | 2
B -> 0B | 1B | 3

*/

// we will define all the function before because any func.can call any function 


int S(char *, int *, int );
int A(char *, int *, int );
int B(char *, int *, int );

//----------------Now declaring the functions-------------
//S -> A1B
int S(char *s, int *id, int n)
{

	if(A(s,id,n))	
	{
		(*id)++;
		if( s[(*id)]=='1')
		{
			(*id)++;
			if( B(s,id,n) )	
			{
				return 1;
			}
			else 
				return 0;
		}
		else
			return 0;
	}

	else
		return 0;
}

//A -> 0A | 2
int A(char *s,int *id, int n)
{
	if( s[(*id)] =='0')
	{
		(*id)++;
		if( A(s,id,n) )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if( s[(*id)] =='2')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}	
//B -> 0B | 1B | 3
int B(char *s, int *id, int n)
{
	if( s[(*id)] =='0')
	{
		(*id)++;
		if( B(s,id,n) )
			return 1;
		else 
			return 0;
	}

	else if( s[(*id)] =='1')
	{
		(*id)++;
		if( B(s,id,n) )
			return 1;
		else 
			return 0;
	}
	else if( s[(*id)] =='3' && (*id)==n-1) // most importatnt part
		return 1;
  
	else
		return 0;
}

int main()
{
	char s[100];
	printf("Enter the expression :  ");
	scanf("%s",s); // when there is characer array we can take it as a '%s' in scanf
	int id=0;

	if( S(s,&id,strlen(s)) )
			printf("Expression Accepted");
	else
		printf("Expression rejected");

return 0;
}




















