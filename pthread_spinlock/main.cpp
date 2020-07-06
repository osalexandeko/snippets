#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
//#include <sys/syscall.h>
#include <errno.h>
#include <sys/time.h>

#include <list>

#define LOOPS 10000000


//!!!!!!!!!!
//#define USE_SPINLOCK (1)


using namespace std;

list<int> the_list;

#ifdef USE_SPINLOCK
pthread_spinlock_t spinlock;
#else
pthread_mutex_t mutex;
#endif

pid_t gettid() { return pthread_self();/*syscall( __NR_gettid ); */}

void *consumer(void *ptr)
{
    int i;

    printf("Consumer TID %lu\n", (unsigned long)gettid());

    while (1)
    {
#ifdef USE_SPINLOCK

		if(EBUSY == pthread_spin_trylock(&spinlock)){
			perror("EBUSY MAN  %d" ); 	
			printf("TID %lu\n", (unsigned long)gettid());
           	pthread_spin_lock(&spinlock);
		}
	 
       
        
        
        
        
        
        
#else
		if(EBUSY ==	pthread_mutex_trylock(&mutex)){
			perror("EBUSY MAN  %d" ); 	
			printf("TID %lu\n", (unsigned long)gettid());
			pthread_mutex_lock(&mutex);
		}
        
#endif

        if (the_list.empty())
        {
#ifdef USE_SPINLOCK
            pthread_spin_unlock(&spinlock);
#else
            pthread_mutex_unlock(&mutex);
#endif
            break;
        }

        i = the_list.front();
        the_list.pop_front();

#ifdef USE_SPINLOCK
        pthread_spin_unlock(&spinlock);
#else
        pthread_mutex_unlock(&mutex);
#endif
    }

    return NULL;
}

int main()
{
    int i;
    pthread_t thr1, thr2;
    struct timeval tv1, tv2;

#ifdef USE_SPINLOCK
    pthread_spin_init(&spinlock, 0);
#else
    pthread_mutex_init(&mutex, NULL);
#endif

    // Creating the list content...
    for (i = 0; i < LOOPS; i++)
        the_list.push_back(i);

    // Measuring time before starting the threads...
    gettimeofday(&tv1, NULL);

    pthread_create(&thr1, NULL, consumer, NULL);
    pthread_create(&thr2, NULL, consumer, NULL);

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);

    // Measuring time after threads finished...
    gettimeofday(&tv2, NULL);

    if (tv1.tv_usec > tv2.tv_usec)
    {
        tv2.tv_sec--;
        tv2.tv_usec += 1000000;
    }

    printf("Result - %ld.%ld\n", tv2.tv_sec - tv1.tv_sec,
        tv2.tv_usec - tv1.tv_usec);

#ifdef USE_SPINLOCK
    pthread_spin_destroy(&spinlock);
#else
    pthread_mutex_destroy(&mutex);
#endif


	// make two process which run same 
    // program after this instruction 
    //fork(); 
    return 0;
}
