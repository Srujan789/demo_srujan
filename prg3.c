#include<stdio.h>
#include<stdlib.h>
int *q;
int max,rear=-1,front=0,count=0;
void enqueue()
{
	int ele;
	if(count==max)
	{
		printf("Queue is overflow");
	}
	else
	{
		printf("Enter elements to be inserted:");
		scanf("%d",&ele);
		rear=(rear+1)%max;
		q[rear]=ele;
		count++;
	}
}
void dequeue()
{
	if(count==0)
	{
		printf("Queue is underflow");
	}
	else
	{
		printf("Deleted elements is %d",q[front]);
		front=(front+1)%max;
		count--;
	}
}
void display()
{
	int i,k;
	if(count==0)
	{
		printf("Queue is empty:");
	}
	else
	{
		k=front;
		for(i=0;i<count;i++)
		{
			printf("%d",q[k]);
			k=(k+1)%max;
		}
	}
}
int main()
{
	int max,ele,choice;
	printf("Enter the size of queue:");
	scanf("%d",&max);
	q=(int*)malloc(max*sizeof(int));
	while(1)
	{
		printf("1: Enqueue\n2: Dequeue\n3: Display\n4: Exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				enqueue();
				break;
			case 2:
				dequeue();
				break;
			case 3:
				display();
				break;
			case 4:
				free(q);
				exit(0);
				break;
			default:
				printf("Invalid");
		}
	}
}
