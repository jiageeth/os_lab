#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int i = 0, j = 0;
int empty; //number of the empty palces
int full;  //number of them for filled
int locker;//don't crash
int item =1 ;


void wait(int *s) {
    while (*s <= 0);  //s,it is the number of process
    (*s)--;///when i done that we take it.i had to decrement it
}


void signalit(int *s) {
    (*s)++;//that process is done so that space is being empty
}

void* producer(void* arg) {
    while (1) {
        wait(&empty);  
        wait(&locker);  

        printf("Producer produced %d at %d\n", item, i);
        buffer[i] = item;
        i = (i + 1) % BUFFER_SIZE;

        signalit(&locker);
        signalit(&full);    

        sleep(10);
    }
}


void* consumer(void* arg) {
    while (1) {
        wait(&full);           
        wait(&locker);  

        printf("Consumer consumed %d from %d\n", buffer[j], j);
        j = (j + 1) % BUFFER_SIZE;

        signalit(&locker);  
        signalit(&empty);  

        sleep(1);
    }
}

int main() {
    pthread_t prod, cons;

    empty = BUFFER_SIZE;
    full = 0;
    locker = 1;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
