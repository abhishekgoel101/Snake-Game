#include <stdio.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

#define M 20
#define N 40
#define P 4


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


int startGame()
{
	FILE *fp;int i=1,n;
	fp=fopen("snakeMF.txt","r");
	printf("SNAKE GAME\n");
	printf("%d. New Game\n",i);
	i++;
	if(fp!=NULL)
	{printf("%d. Load Game\n",i);
	i++;
	}
	printf("%d. Exit Game\n",i);
	printf("Enter your choice ");
	scanf("%d",&n);
	if(fp==NULL && n>1)
	{n++;}
	
	while(n!=1 && n!=2 && n!=3)
	{
		printf("Enter valid choice ");
		scanf("%d",&n);
		if(fp==NULL && n>1)
		{n++;}
	
	}
	fclose(fp);
	system("cls");
	return n;
}

int checkFreq(int x,int y,struct food f[],int s)
{
	if(freq[x][y]>=1)
	return 1;
	
	int i;
	for(i=0;i<P;i++)
	{
	if(i==s)
	continue;
		
	if(f[i].x==-1 || f[i].y==-1)
	continue;
		
	if(f[i].x==x && f[i].y==y)
	return 1;	
	}
	return 0;
	
}

void getFood(struct food *f,int s)
{
int x,y;
do{
x=(rand()%(M));	
y=(rand()%(N));
}while(checkFreq(x,y,f,s));

f[s].x=x;
f[s].y=y;
f[s].val='Q';

}

struct snake* start(struct snake *head,struct food f[])
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
	int i;
	for( i=0;i<P;i++)
	{
	f[i].x=-1;
	f[i].y=-1;
	}
	
	for(i=0;i<P;i++)
	{
	getFood(f,i);
	}
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

void delay(int ms)
{
	clock_t stime=clock();
	while(clock()<stime+ms)
	{if(kbhit())
	break;
	}

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

int checkFood(struct snake* head,struct food f[])
{
	int i;
	for(i=0;i<P;i++)
	{
	if(head->x==f[i].x && head->y==f[i].y)
	{
		return i;			
	}	
	
	}
	
	return -1;
}
struct snake* shift(struct snake* head,int x,int y,struct food f[])
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
		int s=checkFood(head,f);
		if(s!=-1)
		{
		head=insertL(head,t1,t2);

		getFood(f,s);	
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
void saveGame(struct snake* head,struct food f[])
{
	system("cls");
	char choice;
	printf("Do you wish to save the game (y/n)\n");
	
	scanf(" %c",&choice);
	while((getchar())!='\n');
	
	if(choice=='y')
	{
		FILE *fp;
		fp=fopen("snakeMF.txt","w");
		if(fp!=NULL)
		{
		
		struct snake *ptr=head;
		char ch;
		int x,y;
		while(ptr!=NULL)
		{
		x=ptr->x;
		y=ptr->y;
		ch=ptr->val;	

		fprintf(fp,"+%d,%d,%c",x,y,ch);	
		ptr=ptr->next;	
		}
		int i;
		for(i=0;i<P;i++)
		{	
		x=f[i].x;
		y=f[i].y;
		ch=f[i].val;
		
		fprintf(fp,"-%d,%d,%c",x,y,ch);		
		}
				
			fclose(fp);
		}
		
			
	}
		exit(0);
	
}
struct snake* loadGame(struct snake* head,struct food f[])
{
	FILE *fp=fopen("snakeMF.txt","r");
	if(fp!=NULL)
	{
	char s[500];
	int i,j,k=0; 
	fgets(s,500,fp);
	head=NULL;
	struct snake* ptr;
	int x,y;
	char del,ch;
	
	for(i=0;s[i]!='\0';i++)
	{
	del=s[i];
	x=0;y=0;
	
		for(j=i+1;s[j]!=',';j++)
		{
		x=x*10+(s[j]-'0');	
		}
		
		for(j=j+1;s[j]!=',';j++)
		{
		y=y*10+(s[j]-'0');	
		}
		ch=s[j+1];
		
		if(del=='+')
		{	
		struct snake* temp;
		temp=(struct snake*)malloc(sizeof(struct snake));
		temp->x=x;
		temp->y=y;
		temp->val=ch;
		temp->next=NULL;
		if(head==NULL)
		{
			head=temp;
			ptr=head;
		}
		else
		{
		ptr->next=temp;	
		ptr=temp;
		}		
		freq[x][y]=1;	
		}
		else if(del=='-')
		{
		f[k].x=x;
		f[k].y=y;
		f[k].val=ch;
		k++;
		}
		i=j+1;
		
	
	}
			
	
	}

	return head;
}


struct snake* move(struct snake* head,struct food f[])
{
	char mov;
	printf("Make a move ");
	delay(1000);
	if(kbhit())
	{
		mov=getch();
	/*scanf(" %c",&mov);
	while((getchar())!='\n');
	*/
	if(mov==27)
	{
	saveGame(head,f);
	}
	
	}
	else
	{
	mov=getDir(head);	
	}
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

void setB(char a[M][N],int m,int n,struct snake* head,struct food f[])
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
	for(i=0;i<P;i++)
	{
	a[f[i].x][f[i].y]=f[i].val;	
	}
	
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
  struct food f[P];
  char board[M][N];
  int c;
  c=startGame();
  if(c==1)
{
    head=start(head,f);
}
else if(c==2)
{
	head=loadGame(head,f);	
	
}
else
{
	exit(0);
}
  while(1)
  {
  setB(board,M,N,head,f);
  printB(board,M,N);
  head=move(head,f);
  system("cls");

}
return 0;

}     
