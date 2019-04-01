#include<stdio.h>
int n;
int process[10][7];
int readyQueue[20],readyQueue1[20],burst[10],arrivalTime[10];
int front=0,rear=-1,max=-1,cpuTime=0,flag=0,from;
/*
1 arrival
2 burst
3 completion
*/
void Enqueue(int a)
{
rear=rear+1;
readyQueue[rear]=a;
}
int Dequeue(){
int a=readyQueue[front];
process[a-1][3]=cpuTime+1;
front=front+1;
flag=1;
from=a;
return a;
}
int IsAllExecuted()
{
int i;
for(i=0;i<2;i++){
if(process[i][2]>0)
break;
}
if(i<2)
return 1;
return 0;
}
int sortReadyQueue()
{
if(readyQueue[front]<=0)
return -1;
else if(readyQueue[front+1]<=0)
return readyQueue[front]-1;
else
{
int a=readyQueue[front]-1;
int b=readyQueue[front+1]-1;
if(process[a][2]<process[b][2])
return a;
readyQueue[front]=b+1;
readyQueue[rear]=a+1;
return readyQueue[front]-1;
}
}
void roundRobin()
{
int count=0,check=0;
int cpuIdle=1;
int i,id;
int r=-1,f=0;
for(i=2;i<n;i++)
{
r=r+1;
readyQueue1[r]=i+1;
}
if(cpuIdle==1)
id=readyQueue1[f]-1;
while(check==0)
{
if(cpuTime<=4)
{
//
}
if(count==2)
{
int a=readyQueue1[f];
f=f+1;
r=r+1;
readyQueue1[r]=a;
id=readyQueue1[f]-1;
if(id!=-1)
{
cpuIdle=0;
}
else
check=1;
count=0;
}
cpuTime++;
process[id][2]=process[id][2]-1;
count++;
if(process[id][2]<=0)
{
f=f+1;
process[id][3]=cpuTime+1;
id=readyQueue1[f]-1;
count=0;
if(id==-1)
check=1;
}
}
}
void scheduler()
{
int id,i,count=0;
while(IsAllExecuted())
{
if(cpuTime<2)
for(i=0;i<n;i++)
if(cpuTime==arrivalTime[i])
Enqueue(i+1);
id=sortReadyQueue();
if(id!=-1)
{
process[id][2]=process[id][2]-1;
count++;
if(process[id][2]<=0)
{
Dequeue();
}
}
else
{
break;
}
cpuTime++;
}
roundRobin();
}
void calculateWaitingTime()
{
int i,wait_avg=0;
printf("\n==================================================================\n\n");
printf("Process\t\tWaitingTime\n");
printf("------------------------------------\n");
for(i=0;i<n;i++)
{
process[i][5]=process[i][4]-burst[i];
wait_avg+=process[i][5];
printf(" P[%d]\t\t%d\n",i+1,process[i][5]);
}
printf("\nThe Average Waiting Time is %d\n",wait_avg/n);
}
void calculateTurnAroundTime()
{
int i,turn_avg=0;
printf("\n==================================================================\n\n");
printf("Process\t\tTurnAroundTime\n");
printf("------------------------------------\n");
for(i=0;i<n;i++)
{
process[i][4]=process[i][3]-process[i][1];
turn_avg+=process[i][4];
printf(" P[%d]\t\t%d\n",i+1,process[i][4]);
}
printf("\nThe Average TurnAround Time is %d\n",turn_avg/n);
}
int main()
{
int i;
printf("\n===============Welcome To The Scheduler Design Software===============\n");
printf("\n Please Read the following Details and Enter The Details Carefully \n");
printf("\n Enter no of Processes n : ");
scanf("%d",&n);
for(i=0;i<n;i++)
{
printf("Enter ArrivalTime of P[%d] :: ",i+1);
scanf("%d",&arrivalTime[i]);
printf("Enter BurstTime of P[%d] :: ",i+1);
scanf("%d",&burst[i]);
process[i][1]=arrivalTime[i];
process[i][2]=burst[i];
}
printf("\n\n");
scheduler();
printf("\n");
calculateTurnAroundTime();
calculateWaitingTime();
return 0;
}
