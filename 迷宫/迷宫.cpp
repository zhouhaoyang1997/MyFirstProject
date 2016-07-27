#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define right 77
#define left 75
#define down 80
#define up 72
//224
void Read(char ch1[9][24]);
//从文件中读出信息，存在二维数组ch1中，*a,*b,用于记录'★'位置。
//为了减少对文件的访问次数，所以把文件中的信息读到数组中。
void Read1(char ch1[9][24],int *a,int *b);
//从二维数组ch1中读信息，并根据ch1中的各个值输出相应的符号。
int main()
{
	char ch1[9][24];
	int a,b;
	Read(ch1);
	Read1(ch1,&a,&b);
	char m;
	while(!kbhit())
		{
			getch();
			char m=getch();//3是空格  2是人  1是墙 
			switch(m)
			{
				case up:
					{
						if(ch1[a-1][b]==3)
						{
							char t=ch1[a][b];
							ch1[a][b]=ch1[a-1][b];
							ch1[a-1][b]=t;
							system("cls");
							Read1(ch1,&a,&b);
						}
						break;
					}
				case down:
					{
						if(ch1[a+1][b]==3)
						{
							char t=ch1[a][b];
							ch1[a][b]=ch1[a+1][b];
							ch1[a+1][b]=t;
							system("cls");
							Read1(ch1,&a,&b);
						}
						break;
					}
				case left:
					{
						if(ch1[a][b-1]==3)
						{
							char t=ch1[a][b-1];
							ch1[a][b-1]=ch1[a][b];
							ch1[a][b]=t;
							system("cls");
							Read1(ch1,&a,&b);
						}
						break;					
					}	
				case right:
					{
						if(ch1[a][b+1]==3)
							{
								char t=ch1[a][b+1];
								ch1[a][b+1]=ch1[a][b];
								ch1[a][b]=t;
								system("cls");
								Read1(ch1,&a,&b);
							}	
						break;
					}
			}
		}
	return 0;
}
void Read(char ch1[9][24])
{
	int i=0,j=0;
	char c;
	FILE * fp;
	fp=fopen("迷宫.txt","r");
	if(fp==NULL)
	{
		printf("打开失败");
		exit(1);
	}
	c=fgetc(fp);
	for(i=0;i<9;i++)
	{
		for(j=0;j<24;j++)
		{
			if(c=='1')
				{
					ch1[i][j]=1;
					c=fgetc(fp);
				}
			else if(c=='2')
			{
				ch1[i][j]=2;
				c=fgetc(fp);
				
			}
			else if(c=='3')
			{
				ch1[i][j]=3;
				c=fgetc(fp);
			}
			else 
			{
				ch1[i][j]='\n';
				c=fgetc(fp);
			}
		}
	}
	fclose(fp);
}
void Read1(char ch1[9][24],int *a,int *b)
{
	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<24;j++)
		{
			if(ch1[i][j]==1)printf("■");
			if(ch1[i][j]==2)
			{
				printf("☆");
				*a=i;
				*b=j;
			}
			if(ch1[i][j]==3)printf("  ");
		}
		printf("\n");
	}	
}
