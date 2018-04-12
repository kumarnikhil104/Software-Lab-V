#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char MOT[][11]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char POT[][7]={"START","END","LTORG","EQU","ORIGIN"};
char reg[][5]={"AREG","BREG","CREG","DREG"};
char decl[][3]={"DC","DS"};

int POOLTAB[10];
int countl=0,counts=0,countp=0;
typedef struct symbol
{
	int s_no;
	char s_name[200];
	int s_add;
}symbol;

typedef struct literal
{
	int l_no;
	char l_name[100];
	int l_add;
}literal;

symbol s[10];
literal l[10];

int search_POT(char token_1[10])
{
	int i,e;
	for(i=0;i<5;i++)
	{
		e=strcmp(token_1,POT[i]);
		if(e==0)
			return (i+1);
	}
	return -1;
}	
int search_MOT(char token_1[10])
{
	int i,e;
	for(i=0;i<11;i++)
	{
		e=strcmp(token_1,MOT[i]);
		if(e==0)
			return (i+1);
	}
	return -1;
}
int search_REG(char token_1[10])
{
	int i,e;
	for(i=0;i<4;i++)
	{
		e=strcmp(token_1,reg[i]);
		if(e==0)
			return (i+1);
	}
	return -1;
}
int search_dl(char token_1[10])
{
	int i,e;
	for(i=0;i<2;i++)
	{
		e=strcmp(token_1,decl[i]);
		if(e==0)
			return (i+1);
	}
	return -1;
}
int search_symbol(char token_3[10],int counts)
{
	int i,e;
	for(i=0;i<=counts;i++)
	{
		e=strcmp(token_3,s[i].s_name);
		if(e==0)
			return i;
	}
	return (-1);
	
}

FILE *fp,*ip,*tp,*tp1,*tp2;

int first_pass()
{	
	int i,lc=0,ch,m,m1,m2,m3,literal=0,ltorg=0,sadd,a=0,m4,m5;
	char buffer[80],token_1[10],token_2[10],token_3[10],tok4[10];
	
	
	while(fgets(buffer,80,fp))
	{
		ch=sscanf(buffer,"%s%s%s%s",token_1,token_2,token_3,tok4);
		switch(ch)
		{
			case 1:
				
				m=search_POT(token_1);
				POOLTAB[countp]=l[a].l_no;
				a=a+literal;
				countp++;
				literal=0;
				if(m==2)
				{
					for(i=POOLTAB[countp-1];i<=countl;i++)
					{
						l[i-1].l_add=lc;
						fprintf(ip,"%d (AD,0%d) (L,%d)\n",lc,m,i);
						lc++;
					}
					
				}
				
				else 
				{
					if(ltorg==0)
					{
						for(i=0;i<countl;i++)
						{
							l[i].l_add=lc;
							
							fprintf(ip,"%d (AD,0%d) (L,%d)\n",lc,m,i+1);
							lc++;
							
						}
					}
					else
					{
						for(i=POOLTAB[countp-1];i<=countl;i++)
						{
							l[i-1].l_add=lc;
							fprintf(ip,"%d (AD,0%d) (L,%d)\n",lc,m,i);
							lc++;
						}
					}
					ltorg++;
				
				}			
				
			break;
			case 2: 
				
				m=search_POT(token_1);
				if(m==1)
				{	
					lc=atoi(token_2);
					fprintf(ip,"    (AD,01) (C,%d)\n",lc);
				}
				else if(m==5)//ORIGIN
				{	
					for(i=0;i<strlen(token_2);i++)
					{
						if(token_2[i]!='+')
						{
							tok4[i]=token_2[i];
							
						}
						else 
							break;
						
					}
						tok4[i]='\0';
						token_3[0]=token_2[i+1];
						m3=atoi(token_3);
						m1=search_symbol(tok4,counts);
						m2=s[m1].s_add;
						int x=lc;
						lc=m2+m3;
						fprintf(ip,"    (AD,0%d) (C,%d)\n",m,lc);
				}			
			break;
			
			case 3:
				
				m=search_MOT(token_1);
				m1=search_REG(token_2);
				m2=search_POT(token_2);
				if(m2==4)
				{
					m3=search_symbol(token_1,counts);
					if(m3==-1)
					{
						s[counts].s_no=counts+1;
						strcpy(s[counts].s_name,token_1);	
					}
					m4=search_symbol(token_3,counts);
					m5=s[m4].s_add;
					s[counts].s_add=m5;
					fprintf(ip,"    (S,%d) (AD,0%d) (S,%d)\n",counts+1,m2,m4+1);
					counts++;
					
					
				}
				if(m>=1)
				{
					if(token_3[1]=='=')
					{
						l[countl].l_no=countl+1;
						strcpy(l[countl].l_name,token_3);
						fprintf(ip,"%d (IS,0%d) %d (L,%d) \n",lc,m,m1,l[countl].l_no);
						lc++;
						literal++;
						countl++;
					}
					else 
					{
						if(counts==0)
						{
							s[counts].s_no=counts+1;
							strcpy(s[counts].s_name,token_3);
						}
						else
						{
							int sym=search_symbol(token_3,counts);
							if(sym==-1)
							{
								s[counts].s_no=counts+1;
								strcpy(s[counts].s_name,token_3);
							}
						}
						
						fprintf(ip,"%d (IS,0%d) %d (S,%d) \n",lc,m,m1,s[counts].s_no);
						lc++;
						counts++;
					}
				}
				else 
				{
					if(strcmp(token_2,"DC")==0)
					{
						m3=search_symbol(token_1,counts);
						s[m3].s_add=lc;
						sadd=atoi(token_3);
						fprintf(ip,"%d (S,%d) (DL,01) (C,%d) \n",lc,m3+1,sadd);
						lc++;
						
					}
					else if(strcmp(token_2,"DS")==0)
					{
						m3=search_symbol(token_1,counts);
						s[m3].s_add=lc;
						sadd=atoi(token_3);
						fprintf(ip,"%d (S,%d) (DL,02) (C,%d) \n",lc,m3+1,sadd);
						lc=lc+sadd-1;
						lc++;
					}
				}
				
				break;
				case 4:
					
					s[counts].s_no=counts+1;
					strcpy(s[counts].s_name,token_1);
					s[counts].s_add=lc;
					counts++;
					m=search_MOT(token_2);
					m1=search_REG(token_3);
					if(m>=1)
					{
						if(tok4[1]=='=')
						{
							l[countl].l_no=countl+1;
							strcpy(l[countl].l_name,tok4);
							
							fprintf(ip,"%d (L,0%d) (IS,0%d) %d (L,%d) \n",lc,l[countl-1].l_no,m,m1,l[countl].l_no);
							lc++;
							literal++;
							countl++;
						}
						else	
						{
							
						int sym=search_symbol(tok4,counts);
						if(sym==-1)
						{
							s[counts].s_no=counts+1;
							strcpy(s[counts].s_name,tok4);
						}
						
						fprintf(ip,"%d (S,%d) (IS,0%d) %d (S,%d) \n",lc,s[counts-1].s_no,m,m1,s[counts].s_no);
						counts++;
						lc++;
						}						
					}
				break;		
		}
	}
	fclose(fp);
	return 0;	
}

void display_symbolTable()
{

	for(int p=0;p<counts;p++)
	{
		  
		  fprintf(tp,"%d\t%s\t%d\t\n",s[p].s_no,s[p].s_name,s[p].s_add);
	}
	
}

void display_literalTable()
{
	
	for(int p=0;p<countl;p++)
	{
		  fprintf(tp1,"%d\t%s\t%d\t\n",l[p].l_no,l[p].l_name,l[p].l_add);
	}
	
}

void display_poolTable()
{	
	for(int p=0;p<countp;p++)
	{
		
		fprintf(tp2,"\t%d\t%d\t\n",(p+1),POOLTAB[p]);
	}
	
}

int main()
{
	
	printf("\nFirst pass completed, Intermediate code generated\n");
	fp=fopen("test_file.asm","r");
	ip=fopen("interm_code.txt","w");
	first_pass();
	fclose(ip);
	tp=fopen("symbol_table.txt","w");
	tp1=fopen("literal_table.txt","w");
	tp2=fopen("pool_table.txt","w");
	display_symbolTable();
	display_literalTable();
	display_poolTable();
	fclose(tp);
	fclose(tp1);
	fclose(tp2);
	
	
	
}
