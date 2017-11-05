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
  printf("������\t����\tcpuʱ��\t��Ҫʱ��\t����״̬\t������\n");
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

  printf("����������ֺͽ���ʱ��Ƭ����ʱ�䣺\n");
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
  printf("������Ҫ�����Ľ�����Ŀ:\n");
  scanf("%d",&num);
  getchar();
   TimeCreate();
   RoundRun();
   Output();
  return 0;
}
