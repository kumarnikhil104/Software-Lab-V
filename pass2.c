#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

char MOT[][11]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char POT[][7]={"START","END","LTORG","EQU","ORIGIN"};
char reg[][5]={"AREG","BREG","CREG","DREG"};
char decl[][3]={"DC","DS"};

int POOLTAB[10];
int countl=0,counts=0,countp=0; // what are therse three counters

typedef struct symbol
{
	int s_no;
	char s_name[200];
	int s_add;
}symbol;
typedef struct litral
{
	int l_no;
	char l_name[100];
	int l_add;
}litral;

  symbol s[10];
  litral l[10];


// above this every thing is inside "header.h"

void replace_symbol() // 1st function
{
	int i=0;
	char buffer[1000],tok1[100],tok2[100],tok3[100];
	FILE *fp;
	fp=fopen("symbol_table.txt","r");
	while(fgets(buffer,80,fp))
	{
		sscanf(buffer,"%s%s%s",tok1,tok2,tok3);
		strcpy(s[i].s_name,tok2); 
		s[i].s_add=atoi(tok3);
		i++;
	}
	fclose(fp);
}
// what is sscanf

void replace_literal() // 2nd function
{
	int i=0;
	char buffer[1000],tok1[100],tok2[100],tok3[100];
	FILE *fp;
	fp=fopen("litral_table.txt","r");
	while(fgets(buffer,80,fp))
	{
		sscanf(buffer,"%s%s%s",tok1,tok2,tok3);
		strcpy(l[i].l_name,tok2);
		l[i].l_add=atoi(tok3);
		i++;
	}
	fclose(fp);
}
void replace_PT()		// 3rd function
{
	int i=0;
	char buffer[1000],tok1[100],tok2[100];
	FILE *fp;
	fp=fopen("pool_table.txt","r");
	while(fgets(buffer,80,fp))
	{
		sscanf(buffer,"%s%s",tok1,tok2);
		POOLTAB[i]=atoi(tok2);
		i++;
	}
	fclose(fp);
}

int main()
{
	FILE *f1,*f2;
	char * buff=NULL,tok1[100],tok2[100],tok3[100],tok4[100],tok5[100],s1;// don't forget s1
	int len=20,ch,lc=0,r,add,i=0,j=0;// whar are add, ch , r are for?
	// r is register, ch is token count from sscanf, 
// lc is location counter 
	f1=fopen("interm_code.txt","r");
	f2=fopen("machine_code.txt","w");
// we call the above three function here , why?
	replace_symbol();
	replace_literal();
	replace_PT();

	if(f1==NULL)
	{
		printf("FILE not exist");
	}
	else
	{		
		while(getline(&buff,&len,f1)!= -1)///explain the condition a bit here
		{
			ch=sscanf(buff,"%s%s%s%s%s",tok1,tok2,tok3,tok4,tok5); //ch is integer type? what is happening
			if(buff[0]=='(' && buff[1]=='A') // what is this condition buff[l] ==  'A'
				continue;
			else
			{
				if(ch==4&&tok2[1]=='I')
				{
					lc=atoi(tok1);
					r=atoi(tok3); // what is r?
					s1=tok2[5];
					if(tok4[1]=='S')
					{
						char t=tok4[3];
						i=t-'0'; // so that we can consier it in interger because t is in ASCII vlues

						printf("%d 0%c %d %d\n",lc,s1,r,s[i-1].s_add); // writing on the console
						fprintf(f2,"%d 0%c %d %d\n",lc,s1,r,s[i-1].s_add);// writing to the file (i-1 because it is getting stord from 0
					}
					if(tok4[1]=='L')
					{
						char t=tok4[3];
						i=t-'0';
						printf("%d 0%c %d %d\n",lc,s1,r,l[i-1].l_add);
						fprintf(f2,"%d 0%c %d %d\n",lc,s1,r,l[i-1].l_add);
					}
					
					
				}
				if(ch==5&&tok3[1]=='I')
				{
					lc=atoi(tok1);
					r=atoi(tok4);
					s1=tok3[5];
					char t=tok2[3];
					char t1=tok5[3];
					i=t-'0';
					j=t1-'0';
					printf("%d %d 0%c %d %d\n",lc,s[i-1].s_add,s1,r,s[j-1].s_add);
					fprintf(f2,"%d %d 0%c %d %d\n",lc,s[i-1].s_add,s1,r,s[j-1].s_add);
				}
				if(ch==3&&tok2[1]=='A')
					continue;
				if(ch==4&&tok3[1]=='D')
				{
					lc=atoi(tok1);
					char t=tok4[3];
					i=t-'0';	
					if(tok3[5]=='2')
					{
						
						for(int k=0;k<i;k++)
						{
							printf("%d \n",lc);
							fprintf(f2,"%d \n",lc);
							lc++;
						}
					}
					if(tok3[5]=='1')
					{
						
							printf("%d  0000000%c\n",lc,tok4[3]);
							fprintf(f2,"%d  0000000%c\n",lc,tok4[3]);
						
					}
					
				}
					
			}
		}
	}
	
	fclose(f1);
	fclose(f2);
	
	return 0;
	
		
}