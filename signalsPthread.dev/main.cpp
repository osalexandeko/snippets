/* CELEBS26 */                                   
#define _OPEN_THREADS                                                           
                                                                                
#include <stdio.h>                                                              
#include <errno.h>                                                              
#include <signal.h>                                                             
#include <pthread.h>                                                            
#include <unistd.h>                                                             
                                                                                
void            *threadfunc(void *parm)                                         
{                                                                               
 int        threadnum;                                                          
 int        *tnum;                                                              
 sigset_t   set;                                                                
                                                                                
 tnum = parm;                                                                   
 threadnum = *tnum;                                                             
                                                                                
 printf("Thread %d executing\n", threadnum);                                    
 sigemptyset(&set);                                                             
 if(sigaddset(&set, SIGUSR1) == -1) {                                           
    perror("Sigaddset error");                                                  
    pthread_exit((void *)1);                                                    
 }                                                                              
                                                                                
 if(sigwait(&set) != SIGUSR1) {                                                 
    perror("Sigwait error");                                                    
    pthread_exit((void *)2);                                                    
 }                                                                              
                                                                                
 pthread_exit((void *)0);                                                       
}                                                                               
                                                                                
main() {                                                                        
 int          status;                                                           
 int          threadparm = 1;                                                   
 pthread_t    threadid;                                                         
 int          thread_stat;                                                      
                                                                                
                                                                                
 status = pthread_create( &threadid, NULL,                                      
                          threadfunc,                                           
                          (void *)&threadparm);                                 
 if ( status <  0) {                                                            
    perror("pthread_create failed");                                            
    exit(1);                                                                    
 }                                                                              
                                                                                
 sleep(5);                                                                      
                                                                                
 status = pthread_kill( threadid, SIGUSR1);                                     
 if ( status <  0)                                                              
    perror("pthread_kill failed");                                              
                                                                                
 status = pthread_join( threadid, (void *)&thread_stat);                        
 if ( status <  0)                                                              
    perror("pthread_join failed");                                              
                                                                                
 exit(0);                                                                       
}                      
