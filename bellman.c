#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

struct Edge{ int src,dest,wt;};
//semicolon at the end of the struct or union

int check(struct Edge *edge,int src,int dest,int e)
{	// we don't have to take this Struct Edge *edge[]  xxxxx
	for(int i=0;i<e;i++)
		if(edge[i].src == src && edge[i].dest == edge)
			return 1;
	
	return 0;
}
// same as above we don't have to take array of edge
// in bellman we have to also pass the source we decided/selected
// int src then no. of vertices and then no. of edges
void bellman(struct Edge *edge,int src,int v,int e)
{
	int i,j,x; // ?????????/ what purpose does here, x is solving
	// the size of dist is equal to no. of vertices. whY????
	
	int *dist = malloc(v*sizeof(int));//*****************

	for(i=0;i<v;i++)
		dist[i] = INT_MAX;


	dist[src] =0; // distance of the source to itself would be 0

	for(i=1;i<v;i++)// why starting i here from 1
	{
		x=0; // why this is zero here??????????
		for(j=0;j<e;j++)
		{
			int u =edge[j].src;
			int v= edge[j].dest;
			int w = edge[j].wt;

			if( dist[u] != INT_MAX && dist[u]+w < dist[v] )
			  {	dist[v] = dist[u]+w;
				x = 1; // why we have done this??
			  }			
		}

			if(x==0)
				break;
	}

	if(x==1)
	{
		for(i=0;i<e;i++)
		{
			int u =edge[j].src;
			int v= edge[j].dest;
			int w = edge[j].wt;

			if( dist[u] != INT_MAX && dist[u]+w < dist[v] )
			  {	
				printf("Graph contains negative cycles !!!");

				free(dist) ; // before returning
				return ;
			  }
		 }	
	}
// what is this no. of iterations
	//printf("\nNumber of iteration : %d",i);
	printf("\nVertex \t Distance from %d vertex \n",src+1);
	for(i=0;i<v;i++)
	{
		if(dist[i] == INT_MAX)
			printf("%d\t No path \n",i+1);
		else if(i!=src)
			printf("%d \t %d \n",i+1,dist[i]);
	}

free(dist);
}



int main()
{
	int v,e,i;

	printf("How many vertices are there :  ");
	scanf("%d",&v);
	printf("\nHow man y edges are there :  ");
	scanf("%d",&e);

	if( e> v*(v-1) || v<=0 || e<=0)
		printf("Graph is not possible.\n");
	else
	{
		struct Edge *edge;
		edge = malloc(sizeof(struct Edge[e]));// see how we allocate
// we have done this instead of (e*sizeof(struct eEdge));

		printf("Enter:   SOURCE     DEST     Wt. for all edges :\n");
		
		for(i=0;i<e;i++)
		{
			printf("Edge:%d\n",i+1);			
			int src,dest,wt;
			scanf("%d%d%d",&src,&dest,&wt);
		//
			src--;// we are reductin so that if source entered is 3 but it's actually vertex 2 in array.
			dest--;

		//
			if(src == dest)
			{printf("Self Loop !!! Enter Again..\n");
			  i--;				
			}
	// this condition is not clear
			else if( src<0||src>=v  || dest<0||dest>=v )
				{
					printf("Edge not possible--- !!! Enter Again..\n");
					i--;				
				}
			else if( check(edge,src,dest,e) )// also pass no. of edge so that for loop can work /iterate to check
				{
					printf("Dupliacate edge, Enter again ..\n");
					i--;
				}
			else
				{
					edge[i].src = src;
					edge[i].dest = dest;
					edge[i].wt = wt;

				}			
		   } // end of for loop.

//		now we will decide our source vertex.


	int src;
	printf("\nEnter your source vertex: ");
	scanf("%d",&src);
 	src--;


	bellman(edge,src,v,e);

free(edge);	
	}

return 0;
}



















