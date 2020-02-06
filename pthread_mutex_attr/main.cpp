//https://unix.stackexchange.com/questions/433365/custom-priority-value-is-a-pthread-high-sched-prio-positive-or-negative
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
pthread_mutex_t mymutex;
pthread_mutex_t mymutex1;
pthread_mutex_t mymutex2;



void*body(void*arg){
	int i,j;
	for(j=0; j<40; j++) {
	//	pthread_mutex_lock(&mymutex);
		for(i=0; i<1000000; i++);
			for(i=0; i<5; i++){
				fprintf(stderr,(char*)arg);
			}
	//	pthread_mutex_unlock(&mymutex);
	}
	return NULL;
}

int main(){
	
//	struct sched_param param;
//	
//	const int policy = sched_getscheduler(0),
//  	sched_high_prio = sched_get_priority_max(policy), // 19,
//  	sched_low_prio = sched_get_priority_min(policy), // -20,
//  	sched_range_prio = sched_high_prio - sched_low_prio;
//	
//	
	pthread_t t1,t2,t3;
//	pthread_attr_t myattr;
	int err;
//	
//	
//	pthread_mutexattr_t mymutexattr1;
//	pthread_mutexattr_init(&mymutexattr1);
//	pthread_mutexattr_setprotocol(&mymutexattr1, PTHREAD_PRIO_PROTECT);
//	pthread_mutexattr_setprioceiling(&mymutexattr1, 10);
//	pthread_mutex_init(&mymutex1, &mymutexattr1);
//	pthread_mutexattr_setprioceiling(&mymutexattr1, 15);
//	pthread_mutex_init(&mymutex2, &mymutexattr1);
//	pthread_mutexattr_destroy(&mymutexattr1);
//	
//	
//	
//	
//	
//	
//	
//	pthread_mutexattr_t mymutexattr;
//	pthread_mutexattr_init(&mymutexattr);
//	pthread_mutex_init(&mymutex, &mymutexattr);
//	pthread_mutexattr_destroy(&mymutexattr);
//	
//	
//	pthread_attr_init(&myattr);
//	int pic =  PTHREAD_INHERIT_SCHED;
//	pthread_attr_getinheritsched(&myattr, &pic);
//	pthread_attr_getschedparam (&myattr, &param);
//	param.sched_priority = -(((nTaskPriority
//                           - kLowPriority) * sched_range_prio
//                          / kHighPriority) + sched_low_prio
//                         - kDefaultTaskPriority);
//	


//test 2020.02.03
// https://www.oreilly.com/library/view/pthreads-programming/9781449364724/ch04.html




	//cpu_set_t cpu_set;


 

	pthread_attr_t custom_sched_attr1;
	pthread_attr_t custom_sched_attr2;
	pthread_attr_t custom_sched_attr3;
	int fifo_max_prio, fifo_min_prio, fifo_mid_prio;
	struct sched_param fifo_param1;
	struct sched_param fifo_param2;
	struct sched_param fifo_param3;

	pthread_attr_init(&custom_sched_attr1);
  	pthread_attr_setinheritsched(&custom_sched_attr1, PTHREAD_EXPLICIT_SCHED);
  	pthread_attr_setschedpolicy(&custom_sched_attr1, SCHED_FIFO);
  	
  	pthread_attr_init(&custom_sched_attr2);
  	pthread_attr_setinheritsched(&custom_sched_attr2, PTHREAD_EXPLICIT_SCHED);
  	pthread_attr_setschedpolicy(&custom_sched_attr2, SCHED_FIFO);
  	
  	pthread_attr_init(&custom_sched_attr3);
  	//pthread_attr_setscope(&custom_sched_attr3, PTHREAD_SCOPE_SYSTEM);
  	pthread_attr_setinheritsched(&custom_sched_attr3, PTHREAD_EXPLICIT_SCHED);
  	pthread_attr_setschedpolicy(&custom_sched_attr3, SCHED_FIFO);

// 	fifo_max_prio = sched_get_priority_max(SCHED_RR);
// 	fifo_min_prio = sched_get_priority_min(SCHED_RR);

//	fifo_max_prio = sched_get_priority_max(SCHED_FIFO);
// 	fifo_min_prio = sched_get_priority_min(SCHED_FIFO);

	fifo_max_prio = sched_get_priority_max(SCHED_FIFO);
  	fifo_min_prio = sched_get_priority_min(SCHED_FIFO);

    
 	fifo_mid_prio = (fifo_min_prio + fifo_max_prio)/2;
 	
 	printf("fifo_max_prio %d \n", fifo_max_prio);
 	printf("fifo_min_prio %d \n", fifo_min_prio);
 	printf("fifo_mid_prio %d \n", fifo_mid_prio);

  	fifo_param1.sched_priority = fifo_min_prio;
	pthread_attr_setschedparam(&custom_sched_attr1, &fifo_param1);
	err = pthread_create(&t1, &custom_sched_attr1, body, (void*)"1");
	printf("%d \n", fifo_param1.sched_priority);

	fifo_param2.sched_priority = fifo_mid_prio;
	pthread_attr_setschedparam(&custom_sched_attr2, &fifo_param2);
	err = pthread_create(&t2, &custom_sched_attr2, body, (void*)"2");
	printf("%d \n", fifo_param2.sched_priority);
	
	fifo_param3.sched_priority = fifo_max_prio;
	pthread_attr_setschedparam(&custom_sched_attr3, &fifo_param3);
	err = pthread_create(&t3, &custom_sched_attr3, body, (void*)"3");
	printf("%d \n", fifo_param3.sched_priority);

	
//
//	err = pthread_create(&t1, &myattr, body, (void*)"1");
//	err = pthread_create(&t2, &myattr, body, (void*)"2");
//	err = pthread_create(&t3, &myattr, body, (void*)"3");

	
//etest 2020.02.03


	//pthread_attr_destroy(&myattr);
	
	pthread_attr_destroy(&custom_sched_attr1);
	pthread_attr_destroy(&custom_sched_attr2);
	pthread_attr_destroy(&custom_sched_attr3);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	printf("\n");
	return 0;
}
