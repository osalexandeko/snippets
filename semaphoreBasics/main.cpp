// C program to demonstrate working of Semaphores 
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
  
sem_t mutex; 
  
void* thread(void* arg) 
{ 
    //wait 
    sem_wait(&mutex); 
    printf("\n%d Entered..\n", pthread_self()); 
  
    //critical section 
    sleep(1); 
      
    //signal 
    printf("\n%dJust Exiting...\n",pthread_self()); 
    sem_post(&mutex); 
} 

void * threadCntl(void *){
	printf("\n%d cntl Entered... RUN MAN!!!\n", pthread_self()); 
 	sleep(4); 
    sem_post(&mutex); 
}


void * threadRun(void *){
	//wait 
    sem_wait(&mutex); 
    printf("\n%d Entered..\n", pthread_self()); 
  
    //critical section 
    sleep(4); 
      
    //signal 
    printf("\n%dJust Exiting...\n",pthread_self()); 
    sem_post(&mutex); 
	
}
  
  
int main() 
{ 
    sem_init(&mutex, 0, 1); 
    pthread_t t1,t2,t3,t4; 
    pthread_create(&t1,NULL,thread,NULL); 
    sleep(2); 
    pthread_create(&t2,NULL,thread,NULL); 
    sleep(2); 
    pthread_create(&t3,NULL,threadRun,NULL); 
    sleep(2); 
    pthread_create(&t4,NULL,threadCntl,NULL); 
    
    
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    pthread_join(t3,NULL); 
    pthread_join(t4,NULL); 
    sem_destroy(&mutex); 
    return 0; 
} 

