#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
  char name[20];
  int round;  
  int cputime;
  int needtime;
  char state; //Wait  Run  Fnished
  int count;
  struct node *next;
}PCB;
PCB *ready=NULL,*run=NULL,*finish=NULL;
int num;
void GetFirst()
{
  run = ready;

  if(ready!=NULL)
  {
    run ->state = 'R';
    ready = ready ->next;
    run ->next = NULL;
  }
}
void Output()
{
  PCB *p;
  printf("进程名\t轮数\tcpu时间\t需要时间\t进程状态\t计数器\n");
  p = run;
  while(p!=NULL)
  {
    printf("%s\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->round,p->cputime,p->needtime,p->state,p->count);
    p = p->next;
  }
  p = ready;
  while(p!=NULL)
  {
    printf("%s\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->round,p->cputime,p->needtime,p->state,p->count);
    p = p->next;
  }
  p = finish;
  while(p!=NULL)
  {
    printf("%s\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->round,p->cputime,p->needtime,p->state,p->count);
    p = p->next;
  }
}
void InsertTime(PCB *in)
{
  PCB *fst;
  fst = ready;

  if(ready == NULL)
  {
    in->next = ready;
    ready = in;
  }
  else
  {
    while(fst->next != NULL)
    {
      fst = fst->next;
    }
    in ->next = fst ->next;
    fst ->next = in;
  }
}
void InsertFinish(PCB *in)
{
  PCB *fst;
  fst = finish;

  if(finish == NULL)
  {
    in->next = finish;
    finish = in;
  }
  else
  {
    while(fst->next != NULL)
    {
      fst = fst->next;
    }
    in ->next = fst ->next;
    fst ->next = in;
  }
}
void TimeCreate()
{
  PCB *tmp;
  int i;

  printf("输入进程名字和进程时间片所需时间：\n");
  for(i = 0;i < num; i++)
  {
    if((tmp = (PCB *)malloc(sizeof(PCB)))==NULL)
    {
      perror("malloc");
      exit(1);
    }
    scanf("%s",tmp->name);
    getchar();
    scanf("%d",&(tmp->needtime));
    tmp ->cputime = 0;
    tmp ->state ='W';
    tmp ->round = 5;
    tmp ->count = 0;
    InsertTime(tmp);
  }
}
void RoundRun()
{

  int flag = 1;

  GetFirst();
  while(run != NULL)
  {
    Output();
    while(flag)
    {
      run->count++;
      run->cputime++;
      run->needtime--;
      if(run->needtime == 0)
      {
        run ->state = 'F';
        InsertFinish(run);
        flag = 0;
      }
      else if(run->count == run->round)
      {
        run->state = 'W';
        run->count = 0;
        InsertTime(run);
        flag = 0;
      }
    }
    flag = 1;
    GetFirst();
  }
}
int main(void)
{
  char chose;
  printf("请输入要创建的进程数目:\n");
  scanf("%d",&num);
  getchar();
   TimeCreate();
   RoundRun();
   Output();
  return 0;
}
