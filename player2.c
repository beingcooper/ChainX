# include<unistd.h>
# include<stdio.h>
# include<string.h>
# include<sys/shm.h>
# include<stdlib.h>
struct game
{
int count[8][8];
int temp[8][8];
char disp[8][8];
int turn[3];
int pos[3];
int i;
int j;

struct game *next;
}*ptr;


int p,x,ck=0,q,pl=0,flag=0;
char ch;

int brk11(int,int);
int add(int,int);
int table();

int brk11(int c,int d)
{
   if(((c%(7)==0)&&(d%(7)==0))&&(ptr->count[c][d]>1))
   {
       
       ptr->count[c][d]=0;
       ptr->temp[c][d]=0;
       if(c==0)
       {
	 if(d==0)
	 {
	 add(c,d+1);
	 add(c+1,d);
	 }
	 else
	 { add(c,d-1);
	   add(c+1,d);
	 }
      }
       else
       {
	 if(d==0)
	 {
	 add(c-1,d);
	 add(c,d+1);
	 }
	 else
	 {
	 add(c-1,d);
	 add(c,d-1);
	 }
       }
   }

   else if(((c%(7)==0)||(d%(7)==0))&&(ptr->count[c][d]>2))
   {
     
    
     ptr->count[c][d]=0;
     ptr->temp[c][d]=0;
     if(c==0)
     {
     add(c,d-1);
     add(c,d+1);
     add(c+1,d);
     }
     else if(c==7)
     {
     add(c,d-1);
     add(c,d+1);
     add(c-1,d);
     }
     else if( d==0)
     {
     add(c+1,d);
     add(c-1,d);
     add(c,d+1);
     }
     else
     {
     add(c+1,d);
     add(c-1,d);
     add(c,d-1);
     }
   }

   else if(ptr->count[c][d]>3)
   {
   
  
   ptr->count[c][d]=0;
   ptr->temp[c][d]=0;
   add(c-1,d);
   add(c,d+1);
   add(c+1,d);
   add(c,d-1);
   }

   
return 0;
}
int add(int a,int b)
{
  ptr->disp[a][b]=ch;
  ptr->temp[a][b]=2;
  ptr->count[a][b]++;
  table();
  sleep(1);
  system("clear");
  brk11(a,b);

return 0;
}

int table()
{ 
  printf("\n\n");
  for(p=0;p<8;p++)
  {   printf("\t");
  for(q=0;q<8;q++)
  {
       
       if(ptr->temp[p][q]==0)
       { printf(" (%d,%d) ",p,q); goto st1;} 

       printf("  ");
       for(x=0;x<ptr->count[p][q];x++)
       {
       printf("%c",ptr->disp[p][q]);
       }
       for(x=0;x<(5-(ptr->count[p][q]));x++)
       {
       printf(" ");
       }
       st1:
       printf("|");
  }

  printf("\n");
 
 }

return 0;
}

int check()
{  flag=0;

 for(p=0;p<8;p++)
  {
   for(q=0;q<8;q++)
   {
      if((ptr->temp[p][q]!=2)&&(ptr->temp[p][q]!=0))
      { flag=1;
	break;

      }
   }
 }

if(flag==1)
{ 
return 0;
}
else { ptr->pos[1]=2;return 1;
}
}

int main()
{


int shmid;

ptr=(struct game*)malloc(sizeof(struct game));
shmid=shmget((key_t)1234 , sizeof(struct game) , 0666 | IPC_CREAT);
ptr = shmat(shmid, (void *)0, 0);

ptr->next=NULL;

for(p=0;p<8;p++)
{
for(q=0;q<8;q++)
{
ptr->disp[p][q]='_';
}
}

for(p=0;p<3;p++)
{
ptr->turn[p]=0;
ptr->pos[p]=0;
}

for(p=0;p<8;p++)
{
for(q=0;q<8;q++)
{
ptr->count[p][q]=0;
ptr->temp[p][q]=0;
}
}

system("clear");
printf("\n\t\t\t\ttHiS iS cHaInX\n");
printf("\t\t\t\t--------------");
table();

printf("\nWelcome Player 2 \n");
printf("Wait for player 1 to play the move\n");
while(1)
{

if(ptr->turn[1]==1)
{


beg:

printf("Enter the number of row and column( separated by a space ),\nwhere you want to place your symbol \n");
scanf("%d %d",&ptr->i,&ptr->j);

if((ptr->temp[ptr->i][ptr->j]==0) || (ptr->temp[ptr->i][ptr->j]==2) )
goto end;
else
{ printf("Position unavailable......enter again!\n");
  goto beg;
}
end:
ptr->temp[ptr->i][ptr->j]=2;

ch='#';

add(ptr->i,ptr->j);

table();

if(pl>=1)
{
ck=check();


if(ck==1)
{

printf("\nYou have won the game.\n");
printf("Game ends here.....\n");

exit(0);
}
}


ptr->pos[1]=1;
ptr->turn[1]=0;
printf(" Wait for player 3 to play the move\n");
sleep(5);
ptr->turn[2]=1;
pl++;
}


if(ptr->pos[0]==1)
{
system("clear");
printf("Player 1 has chosen i=%d and j=%d\n",ptr->i,ptr->j);
table();
sleep(2);
ptr->pos[0]=0;
}


if(ptr->pos[2]==1)
{
system("clear");
printf("Player 3 has chosen i=%d and j=%d\n",ptr->i,ptr->j);
table();
printf("Wait for player 1 to play the move\n");
sleep(2);
ptr->pos[2]=0;
}


if(ptr->pos[0]==2)
{system("clear"); 
printf("\nPlayer 1 has won the game\nGame ends here.....\n");
table();
exit(0);
}

if(ptr->pos[2]==2)
{system("clear"); 
printf("\nPlayer 3 has won the game\nGame ends here.....\n");
table();
exit(0);
}
}





return 0;
}









