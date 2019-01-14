#include <stdio.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

#define M 30
#define N 50

int fx=0;
int fy=0;

int ff[3][3]={{9,15,20},{11,25,1},{18,27,3}};

int freq[M][N]={0};

struct snake{
  int x;
  int y;
  char val;
 struct snake *next;

};


struct food{
  int x;
  int y;
  char val;
};

void getFood(struct food *f)
{
int x,y;
do{
x=(rand()%(M));	
y=(rand()%(N));
}while(freq[x][y]>=1);

f->x=x;
f->y=y;
f->val='Q';

}

struct snake* start(struct snake *head,struct food *f)
{
 if(head==NULL)
 {struct snake* ptr,*temp;
  
  //1st node aka head
  temp=(struct snake*)malloc(sizeof(struct snake));
   temp->next=NULL;
  temp->x=5;
   temp->y=5;
  temp->val='O';
  head=temp;
  ptr=head;
   freq[temp->x][temp->y]=1;
  
  //2nd node aka body
  temp=(struct snake*)malloc(sizeof(struct snake));
   temp->next=NULL;
  temp->x=6;
   temp->y=5;
  temp->val='#';
  ptr->next=temp;
  ptr=ptr->next;
  freq[temp->x][temp->y]=1;
  
  //3rd node aka tail
  temp=(struct snake*)malloc(sizeof(struct snake));
   temp->next=NULL;
  temp->x=7;
   temp->y=5;
  temp->val='*';
  ptr->next=temp;
  ptr=ptr->next;
  freq[temp->x][temp->y]=1;
  
  
  //initialize food
	srand(time(0));
	getFood(f);
  /*f->x=10;
  f->y=10;
  f->val='Q';
  */
    
 }
  return head;
 
} 

struct snake* insertL(struct snake* head,int x,int y)
{
	if(head!=NULL)
	{
	struct snake *ptr=head,*temp;
	temp=(struct snake*)malloc(sizeof(struct snake));
	temp->next=NULL;
	temp->x=x;
	temp->y=y;
	temp->val='*';
	freq[temp->x][temp->y]=1;
	
	while(ptr->next!=NULL)
	{
	ptr=ptr->next;
	}
	ptr->next=temp;	
	ptr->val='#';
	
	}
	return head;
}

char getDir(struct snake* head)
{
	int x1,x2,y1,y2;char c='0';
	if(head!=NULL && head->next!=NULL)
	{
		x1=head->x;
		y1=head->y;
		x2=head->next->x;
		y2=head->next->y;
		if(x1==x2)
		{
		if(abs(y1-y2)!=1)
		{
		if(y1==0 && y2==N-1)	
		{y2=-1;
		}
		else if(y1==N-1 && y2==0)
		{
			y2=N;
		}
		}
		if(y1>y2)
		{c='d';
		}
		else
		{c='a';
			}	
		}
		else if(y1==y2)
		{
			
		if(abs(x1-x2)!=1)
		{
		if(x1==0 && x2==M-1)	
		{x2=-1;
		}
		else if(x1==M-1 && x2==0)
		{
			x2=M;
		}
		}
		
		if(x1>x2)
		{c='s';
		}
		else
		{c='w';
			}
		}
	}
	return c;
}

int validMove(struct snake* head,char mov)
{
	if(head!=NULL)
	{
		if(mov!='w' && mov!='a' && mov!='s' && mov!='d')
		{return 0;}
		
		char c=getDir(head);
		if(c=='w' && mov!='s')
		return 1;
		
		if(c=='s' && mov!='w')
		return 1;
		
		if(c=='a' && mov!='d')
		return 1;
		
		if(c=='d' && mov!='a')
		return 1;
	}
	return 0;
}

void swap(int *a,int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}

int checkFood(struct snake* head,struct food *f)
{
	if(head->x==f->x && head->y==f->y)
	return 1;
	else 
	return 0;
}
struct snake* shift(struct snake* head,int x,int y,struct food *f)
{
	struct snake *ptr=head;
	int t1=x,t2=y;
		freq[t1][t2]++;
		while(ptr!=NULL)
		{
			swap(&t1,&(ptr->x));
			swap(&t2,&(ptr->y));
			ptr=ptr->next;
		}
		freq[t1][t2]--;
		if(checkFood(head,f))
		{
		head=insertL(head,t1,t2);
		/*f->x=ff[fx][fy];
		f->y=f[fy][fx];
		*/
		getFood(f);	
		}
		
	return head;
}

void gameOver(struct snake* head)
{
	int flag=1;
	if(head!=NULL)
	{
	int x=head->x;
	int y=head->y;	
	
	if(freq[x][y]==1)
	{
		flag=0;
	}
	
	}
	if(flag)
	{
		printf("..............Game  Over..................\nBetter luck next time.......\n");
		exit(0);
	}
}

struct snake* move(struct snake* head,struct food *f)
{
	char mov;
	printf("Make a move ");
	scanf("%c",&mov);
	while((getchar())!='\n');

	if(validMove(head,mov))
	{
	int x=0,y=0;
	x=head->x;
	y=head->y;
	if(mov=='w')
	{
	x--;
	if(x<0)
	{
		x=M-1;
	}
	}
	else if(mov=='a')
	{
		y--;
	if(y<0)
	{
		y=N-1;
	}
	}	
	else if(mov=='s')
	{
		x++;
	if(x>=M)
	{
		x=0;
	}
	}	
	else if(mov=='d')
	{
		y++;
	if(y>=N)
	{
		y=0;
	}
	}	
	head=shift(head,x,y,f);
	
	gameOver(head);
	
	}
	else{
		printf("Enter a valid Move\n");
		head=move(head,f);
	}
	return head;
}
void print(struct snake* head)
{
  struct snake* ptr=head;
  while(ptr!=NULL)
  {
    printf("%c  x=%d,y=%d\n",ptr->val,ptr->x,ptr->y);
    ptr=ptr->next;
  }
}

void setB(char a[M][N],int m,int n,struct snake* head,struct food f)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			a[i][j]=' ';
		}
	}
	struct snake *ptr=head;
	if(head!=NULL)
	{
		while(ptr!=NULL)
		{
			a[ptr->x][ptr->y]=ptr->val;
			ptr=ptr->next;
		}
		
	}
	a[f.x][f.y]=f.val;
	
}

void printB(char a[M][N],int m,int n)
{
	int i,j;
	for(i=0;i<n+2;i++)
	{printf("!");
	}
	printf("\n");
	for(i=0;i<m;i++)
	{
		printf("!");
		for(j=0;j<n;j++)
		{printf("%c",a[i][j]);
		}
		printf("!\n");
	}
	for(i=0;i<n+2;i++)
	{printf("!");
	}
	printf("\n");
	
	
}

int main()
{
struct snake *head=NULL;
  struct food f;
 head=start(head,&f);
  
  char board[M][N];
  while(1)
  {
  setB(board,M,N,head,f);
  printB(board,M,N);
  head=move(head,&f);
  system("cls");

}
return 0;

}     
