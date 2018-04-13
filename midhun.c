#include<conio.h>
#include<stdio.h>
#include<iostream>
using namespace std;
int main()
{
	int temp;                 //temporary variable
	int n;                   //number of processes
	int p[10];               //process
	int pp[10];              //process priority
	int Btime[10];          //burst time
	int w[10];             //waitimg time
	int t[10];            //turnaroundtime
	int Atime[10];        //arrival time
	int awt,atat,i,tq;    //awt is average waiting time, atat is average turn around time, tq is time quantum
	
	cout<<"enter the number of processes";
	cin>>n;
	cout<<"Enter time quantum";
     cin>>tq;
	 cout<<"\n\t Enter burst time  time priority   Arrival time  \n";
	 cout<<"/n/t enter time priority"
	 cout<<"enter arrival time"
	 for(i=0;i<n;i++)
    {
      cout<<"\nProcess["<<i+1<<"]:";
      cin>>Btime[i]>>pp[i]>>Atime[i];
      p[i]=i+1;
    }

      //sorting done on the basis of priority 
    for(i=0;i<n-1;i++)
     {
      for(int j=i+1;j<n;j++)
      {
       if(pp[i]<pp[j])
       {
     temp=pp[i];
     pp[i]=pp[j];
     pp[j]=temp;
     temp=Btime[i];
     Btime[i]=Btime[j];
     Btime[j]=temp;
     temp=p[i];
     p[i]=p[j];
     p[j]=temp;
      }
   }
}
w[0]=0;
awt=0;
t[0]=Btime[0];
atat=t[0];
for(i=1;i<n;i++)
 {
 	if(tq<n || tq>n) 
	 {
	 
     w[i]=t[i-1];
     awt+=w[i];
     t[i]=w[i]+Btime[i];
     atat+=t[i];
	 }
 }
 for(i=0;i<n;i++)
 {
 	cout<<"P"<<p[i]<<" ";
 }
//to display all the process
 
cout<<"\n\nProcess \t Burst Time \tArrival time  \t Wait Time \t Turn Around Time   Priority \t \n";
for(i=0;i<n;i++)
cout<<"\n   "<<p[i]<<"\t\t   "<<Atime[i]<<"\t\t  "<<Atime[i]<<"\t\t  "<<w[i]<<"\t\t     "<<t[i]<<"\t\t     "<<pp[i]<<"\n";
awt=awt/n;
atat=atat/n;
cout<<"\n Average Waiting Time : "<<awt;
cout<<"\n Average Turn Around Time : "<<atat;
getch();
}

















#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>
struct Process {
	int priority,time,Atime,Btime;
	clock_t arrival;
	int flag,completed,p;
	sem_t se;
	struct Process *next;
};
int i=0,z=1;
float WT=0,TAT=0;
clock_t start;
struct Process *front=NULL,*temp,*rear=NULL;
typedef struct Process node;
void *processor(node *S) {
	int x=0,y=0;
	clock_t count;
	while(1) {
		sem_wait(&S->se);
		if((S->Atime<=(clock()-start)/CLOCKS_PER_SEC && S->p==1) || y==1) {
			printf("\nCount Inputed");
			S->p=0;
			y=0;
			count=clock();
		} 
		if(S->flag==1) {
			printf("\n%d %d",S->priority,(clock()-start)/CLOCKS_PER_SEC);
			S->flag=0;
			S->arrival=clock();
		}
		if((clock()-count)/CLOCKS_PER_SEC==1) {
			x=0;
			count=clock();
			printf("\n%d",(clock()-start)/CLOCKS_PER_SEC);
			S->time-=1;
			if(S->time==0) {
				TAT+=(clock()-S->arrival)/CLOCKS_PER_SEC;
				WT+=((clock()-S->arrival)/CLOCKS_PER_SEC)-S->Btime;
				if(rear->next!=NULL) {
					printf("*");
				if(rear->Atime==(clock()-start)/CLOCKS_PER_SEC){
					rear->next=rear->next->next;
				}
				else {
					rear=rear->next;
				}
				sem_post(&rear->se);
				}
				S->completed=7;
				printf("\nProcess Completed next Process is :%d",rear->priority);
			}
			else if(rear!=S) {
				printf("\nProcess Context Switched to :%d",rear->priority);
				y=1;
				sem_post(&rear->se);
				sem_wait(&S->se);
			}
		}
		if(S->completed==7) {
			break;
		}
		sem_post(&S->se);
	}
}

void pop() {
	node *start=rear;
	printf("\nArrival Time :%d",start->next->Atime);
}
void rpush(node *temp) {
	node *start=rear;
	if(rear==NULL) {
		rear=temp;
		rear->next=NULL;
	}
	else{
	int p=temp->priority;
	if (start->priority > p) {
        	temp->next = rear;
        	rear=temp;
    	}
    	else {
        	while (start->next != NULL && start->next->priority< p) {
            		start = start->next;
        	}
        temp->next = start->next;
        start->next = temp;
    }
	}
}
void push() {
	temp=(node *)malloc(sizeof(node));
	printf("\nEnter Priority of %d Process :",(i+1));
	scanf("%d",&temp->priority);
	printf("Enter Arrival Time :");
	scanf("%d",&temp->Atime);
	int p=temp->priority;
	printf("Enter Burst Time :");
	scanf("%d",&temp->time);
	temp->Btime=temp->time;
	sem_init(&temp->se,0,0);
	int t=temp->Atime;
	temp->flag=1;
	temp->p=1;
	node *start=front;
	if ((start->Atime > t) || (start->Atime==t && start->priority > temp->priority)){
        	temp->next = front;
        	front=temp;
    	}
    	else {
        	while (start->next != NULL && start->next->Atime <= t) {
            		if(start->next->Atime==t && temp->priority<start->next->priority) {
            			break;
					}
					else
					start = start->next;
            		
        	}
        temp->next = start->next;
        start->next = temp;
    }
}
void main() {
	int n,l=1;
	pthread_t p[10];
	printf("\nEnter No.of Processes :");
	scanf("%d",&n);
	while(i<n) {
		printf("*");
		if(front==NULL) {
			front=(node *)malloc(sizeof(node));
			printf("Enter Priority of %d Process :",(i+1));
			scanf("%d",&front->priority);
			printf("Enter Arrival Time :");
			scanf("%d",&front->Atime);
			printf("Enter Burst Time :");
			scanf("%d",&front->time);
			front->flag=1;
			front->p=1;
			front->Btime=front->time;
			sem_init(&front->se,0,0);
			front->next=NULL;
		}
		else {
			push();
		}
		i++;
	}
	start=clock();
	i=0;
	while(i<n) {
		temp=front;
		
		if((clock()-start)/CLOCKS_PER_SEC==temp->Atime) {
			if(l==1) {
				l=0;
				sem_post(&temp->se);
			}
			pthread_create(&p[i],NULL,processor,temp);
			front=front->next;
			rpush(temp);
			//printf("\nCreation : %d Priority of Rear : %d",temp->Atime,rear->priority);
			i++;
		}
	}
	for(i=0;i<n;i++) {
		pthread_join(p[i],NULL);
	}
	printf("Average Waiting Time :%f\nAverage Turn Around Time :%f",(float)WT/n,(float)TAT/n);
}

