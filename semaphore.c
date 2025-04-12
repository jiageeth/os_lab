#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
#include<pthread.h>
int buffer[5];
int i=0,j=0;
int item;
sem_t empty;
sem_t full;
sem_t locker;
int count1=0;
int count2=0;
void* producer()
{
	while(count1!=20)
	{
		sem_wait(&empty);
		sem_wait(&locker);
		buffer[i]=item;
		printf("producer produced %d at %d\n",item,i);
		i=(i+1)%5;
		sem_post(&locker);
		sem_post(&full);
		count1++;
	}
}
void* consumer()
{
	while(count2!=20)
	{
		sem_wait(&full);
		sem_wait(&locker);
		item=buffer[j];
		printf("CONSUMER CONSUMED %d FROM  %d\n",item,j);
		j=(j+1)%5;
		sem_post(&locker);
		sem_post(&empty);
		count2++;
	}

}
int main()
{
	pthread_t t1,t2;
	sem_init(&empty,0,5);
	sem_init(&full,0,0);
	sem_init(&locker,0,1);
	pthread_create(&t1,NULL,producer,NULL);
	pthread_create(&t2,NULL,consumer,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}