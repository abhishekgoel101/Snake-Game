#include <stdio.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

#define M 20
#define N 50
#define P 4
#define S 10
#define A 7		//A should be greater than or equal to 1
#define B 4     //B  should be always greater than or equal to 3

int score=0;

struct snake{
  int x;
  int y;
  char val;
 struct snake *next;

};

struct hash{
	struct snake* head;
	struct snake* tail;
	int count;
}h[S];

struct food{
  int x;
  int y;
  char val;
};


enum colors{ BLACK,BLUE,GREEN,AQUA,RED,PURPLE,YELLOW,WHITE,GRAY,
LIGHT_BLUE,LIGHT_GREEN,LIGHT_AQUA,LIGHT_RED,
LIGHT_PURPLE,LIGHT_YELLOW,BRIGHT_WHITE
};


void gotoxy(int x, int y) 
{ 
	x=x+A;
	y=y+B;
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void font()
{
	CONSOLE_FONT_INFOEX cfi;

cfi.cbSize = sizeof(cfi);
cfi.nFont = 0;
cfi.dwFontSize.X = 20;                  // Width of each character in the font
cfi.dwFontSize.Y = 24;                  // Height
cfi.FontFamily = FF_DONTCARE;
cfi.FontWeight = FW_NORMAL;
wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void setcolor(int color)
{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
SetConsoleTextAttribute(hStdOut,color);
	
}

int startGame()
{
	FILE *fp;int i=1,n;
	fp=fopen("snakeG.txt","r");
	setcolor(LIGHT_GREEN);
	printf("\nSNAKE GAME\n\n");
	setcolor(WHITE);
	printf("%d.New Game\n",i);
	i++;
	if(fp!=NULL)
	{printf("%d.Load Game\n",i);
	i++;
	}
	printf("%d.Exit Game\n",i);
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

int indexH(int x,int y)
{
	return (x+y)%S;
}

int checkH(int x,int y)
{
	int p=indexH(x,y);

	struct snake *ptr=h[p].head;
	while(ptr!=NULL)
	{
		if(ptr->x==x && ptr->y==y)
		return 1;
		
		ptr=ptr->next;
	}
	return 0;	

}

int countH(int x,int y)
{
	int c=0;
	int p=indexH(x,y);

	struct snake *ptr=h[p].head;
	while(ptr!=NULL)
	{
		if(ptr->x==x && ptr->y==y)
		c++;

		ptr=ptr->next;
	}
	return c;	

}
void insertH(struct snake* n)
{
	struct snake *temp,*ptr;
	temp=(struct snake*)malloc(sizeof(struct snake));
	*temp=*n;
	temp->next=NULL;
	int p=indexH(n->x,n->y);
	
	if(h[p].head==NULL)
	{
		h[p].head=temp;
		h[p].tail=temp;
		h[p].count++;
	}
	else
	{
	/*	
	//to insert at last	
	h[p].tail->next=temp;	
	h[p].tail=temp;	
	h[p].count++;
	*/
		
	//to insert at start
	ptr=h[p].head;
	h[p].head=temp;
	temp->next=ptr;	
	h[p].count++;
		
	}
	
}

int checkFreq(int x,int y,struct food f[],int s)
{
	if(checkH(x,y))
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

setcolor(LIGHT_RED);
gotoxy(f[s].y,f[s].x);
printf("Q");

}

struct snake* start(struct snake *head,struct food f[])
{
 if(head==NULL)
 {struct snake* ptr,*temp;
	int i;
	score=0;
	  
  for(i=0;i<S;i++)
  {
  	h[i].head=NULL;
  	h[i].tail=NULL;
  	h[i].count=0;
  }
  
  //1st node aka head
  temp=(struct snake*)malloc(sizeof(struct snake));
   temp->next=NULL;
  temp->x=5;
   temp->y=5;
  temp->val='O';
  head=temp;
  ptr=head;
 	insertH(temp);
 
  
  
  //2nd node aka body
  temp=(struct snake*)malloc(sizeof(struct snake));
   temp->next=NULL;
  temp->x=6;
   temp->y=5;
  temp->val='#';
  ptr->next=temp;
  ptr=ptr->next;
  insertH(temp);
  
  //3rd node aka tail
  temp=(struct snake*)malloc(sizeof(struct snake));
   temp->next=NULL;
  temp->x=7;
   temp->y=5;
  temp->val='*';
  ptr->next=temp;
  ptr=ptr->next;
  insertH(temp);
  
  //initialize food
	srand(time(0));

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
	insertH(temp);
	
	while(ptr->next!=NULL)
	{
	ptr=ptr->next;
	}
	ptr->next=temp;	
	ptr->val='#';
	
	int p=indexH(ptr->x,ptr->y);
	if(h[p].head!=NULL)
	{
		struct snake* ptr1=h[p].head;
		while(ptr1!=NULL) 
		{
		if(ptr1->x==ptr->x && ptr1->y==ptr->y)
		{
			ptr1->val='#';
			break;
		}
			ptr1=ptr1->next;	
		}
	}
	
	
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

void gameOver(struct snake* head)
{
	int flag=1;
	if(head!=NULL)
	{
	int x=head->x;
	int y=head->y;	
	
	if(countH(x,y)==1)
	{
		flag=0;
	}
	
	}
	if(flag)
	{
		system("cls");
		setcolor(RED);
		printf("\n GAME OVER         \n\n Better luck next time\n");
		setcolor(WHITE);
		exit(0);
	}
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
	struct snake *ptr=head,*ptr1=NULL;
	int t1=x,t2=y;
	int lx,ly,p;

				
		//for making head as 1st body part in hash
		p=indexH(head->x,head->y);
		ptr=h[p].head;
		while(ptr!=NULL)
		{
			if(ptr->x==head->x && ptr->y==head->y && ptr->val==head->val)
			{
				ptr->val='#';
				break;
			}
			ptr=ptr->next;
		}
		
		
		ptr=head;
		
		while(ptr!=NULL)
		{
			swap(&t1,&(ptr->x));
			swap(&t2,&(ptr->y));
			lx=ptr->x;
			ly=ptr->y;
			ptr=ptr->next;
		}

		
	//for making previous tail as head in hash by first removing it then making head
		p=indexH(t1,t2);
		ptr1=NULL;
		ptr=h[p].head;
		if(ptr!=NULL)
		{
		if(ptr->x==t1 && ptr->y==t2 && ptr->val=='*')
		{
			ptr1=ptr;
			h[p].head=h[p].head->next;
			h[p].count--;
			if(h[p].head==NULL)
			{h[p].tail=NULL;}
			
		}
		else
		{
			while(ptr->next!=NULL)
			{
				if(ptr->next->x==t1 && ptr->next->y==t2 && ptr->next->val=='*')
				{
				ptr1=ptr->next;
				ptr->next=ptr->next->next;
				if(ptr->next==NULL)
				{
					h[p].tail=ptr;
				}
				h[p].count--;
				break;
				}		
				ptr=ptr->next;
			}			
		}

		if(ptr1!=NULL)	
		{
		ptr1->x=x;	
		ptr1->y=y;
		ptr1->val='O';
		p=indexH(x,y);
		if(h[p].head==NULL)
		{
			h[p].tail=ptr1;
		}
		ptr1->next=h[p].head;
		h[p].head=ptr1;	
		h[p].count++;
		}
				
		}
		
		//for making last body part as tail in hash
		p=indexH(lx,ly);
		ptr=h[p].head;
		while(ptr!=NULL)
		{
			if(ptr->x==lx && ptr->y==ly && ptr->val=='#')
			{
				ptr->val='*';
				break;
			}
			ptr=ptr->next;
		}
		
	gameOver(head);	
	
	setcolor(LIGHT_GREEN);

	gotoxy(head->next->y,head->next->x);
	printf("#");
	gotoxy(ly,lx);
	printf("*");
	gotoxy(t2,t1);
	printf(" ");
	gotoxy(head->y,head->x);
	printf("O");	
		
		int s=checkFood(head,f);
		if(s!=-1)
		{
		head=insertL(head,t1,t2);
		gotoxy(ly,lx);
		printf("#");
		gotoxy(t2,t1);
		printf("*");
		
		getFood(f,s);	
		
		score++;
		setcolor(BRIGHT_WHITE);
		gotoxy(7+(-1),-3);  //length of "SCORE: " =7
		printf("%d",score);
		
		}
	

			
	return head;
}


void saveGame(struct snake* head,struct food f[])
{
	system("cls");
	char choice;
	setcolor(WHITE);
	printf("Do you wish to save the game (y/n)\n");
	
	scanf(" %c",&choice);
	while((getchar())!='\n');
	
	if(choice=='y')
	{
		FILE *fp;
		fp=fopen("snakeG.txt","w");
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
		fprintf(fp,"/%d",score);		
			fclose(fp);
		}
		
			
	}
		exit(0);
	
}
struct snake* loadGame(struct snake* head,struct food f[])
{
	FILE *fp=fopen("snakeG.txt","r");
	if(fp!=NULL)
	{
	char s[5000];
	int i,j,k=0; 
	fgets(s,5000,fp);
	head=NULL;
	struct snake* ptr;
	int x,y;
	char del,ch;

	for(i=0;i<S;i++)
	{
  		h[i].head=NULL;
  		h[i].tail=NULL;
  		h[i].count=0;
  	}
  	
  	
	for(i=0;s[i]!='\0';i++)
	{
	del=s[i];
	x=0;y=0;

	if(del=='/')
	{
		for(j=i+1;s[j]!='\0' && s[j]!='+' && s[j]!='-';j++)
		{
		x=x*10+(s[j]-'0');	
		}
		score=x;
		i=j-1;
		continue;
	}
	
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
		insertH(temp);
		
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

	gotoxy(-A,M+2);
	delay(1000);
	
	printf("                    ");
	gotoxy(-A,M+2);
	
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
	
	else if('A'<=mov && mov <='Z')  //for caps keys
	{
	mov=mov+32;
	}
	else if(mov==-32)    //for arrow key.while pressing arrow key it takes -32
	{mov=getch(); 	 // and arrow key.so hack to avoid it.
				
	if(mov==72)
	{mov='w';}
	else if(mov==80)
	{mov='s';}
	else if(mov==75)
	{mov='a';}
	else if(mov==77)
	{mov='d';}	
		
	} 
	
	}
	else
	{
	mov=getDir(head);	
	}
	if(validMove(head,mov))
	{}
	else
	{
		gotoxy(-A,M+2);
		setcolor(BLUE);
		printf("Enter a valid Move");
		mov=getDir(head);		
		
	}
	
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
	setcolor(BRIGHT_WHITE);
	int i,j;	
	gotoxy(-1,-3);
	printf("SCORE: ");  //length of this string is 7
//	gotoxy(7+(-1),-3);
	printf("%d",score);
	
	setcolor(BRIGHT_WHITE);
	gotoxy(-1,-1);
	for(i=0;i<n+2;i++)
	{printf("!");}
	printf("\n");
	for(i=0;i<m;i++)
	{	
		gotoxy(-1,i);
		printf("!");
		for(j=0;j<n;j++)
		{
		if(a[i][j]==' ')
		{}
		else if(a[i][j]=='Q')
		{setcolor(LIGHT_RED);}
		else
		{setcolor(LIGHT_GREEN);}
				
		printf("%c",a[i][j]);
		}
		
		setcolor(BRIGHT_WHITE);
		printf("!\n");
	}
	gotoxy(-1,m);
	for(i=0;i<n+2;i++)
	{printf("!");
	}
	printf("\n\n");
	
	
}

void printGame(struct snake* head,struct food f[])
{
	setcolor(BRIGHT_WHITE);
	int i,j;	
	gotoxy(-1,-3);
	printf("SCORE: ");  //length of this string is 7
//	gotoxy(7+(-1),-3);
	printf("%d",score);
	
	setcolor(BRIGHT_WHITE);
	gotoxy(-1,-1);
	for(i=0;i<N+2;i++)
	{printf("!");}

	for(i=0;i<M;i++)
	{
		gotoxy(-1,i);
		printf("!");
		gotoxy(N,i);
		printf("!");
	}

	gotoxy(-1,M);
	for(i=0;i<N+2;i++)
	{
		printf("!");
	}
	
	setcolor(LIGHT_GREEN);
	struct snake *ptr=head;
	
	if(head!=NULL)
	{
		while(ptr!=NULL)
		{
			gotoxy(ptr->y,ptr->x);
			printf("%c",ptr->val);
			ptr=ptr->next;
		}
		
	}
	setcolor(LIGHT_RED);
	
	for(i=0;i<P;i++)
	{
		gotoxy(f[i].y,f[i].x);
		printf("%c",f[i].val);	
	
	}
	
	setcolor(BRIGHT_WHITE);	

}


void printH()
{
	int i;
	printf("Hash is \n");
	for(i=0;i<S;i++)
	{
		printf("Index-%d count-%d -- ",i,h[i].count);
		struct snake *ptr=h[i].head;
		while(ptr!=NULL)
		{
		printf("x-%d y-%d val-%c  ",ptr->x,ptr->y,ptr->val);
		ptr=ptr->next;	
		}
		if(h[i].head!=NULL)
		printf("Tail is x-%d y-%d val-%c  ",h[i].tail->x,h[i].tail->y,h[i].tail->val);		
	printf("\n");
	}
	
}


int main()
{
struct snake *head=NULL;
  struct food f[P];
  char board[M][N];
  int c;

  font();
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


printGame(head,f);  //No use of board 2d matrix in this case

/*
//or
  setB(board,M,N,head,f);
  printB(board,M,N);
*/


  while(1)
  {

  head=move(head,f);
 
}

return 0;
}     
