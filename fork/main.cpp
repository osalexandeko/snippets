#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include "fork.hpp"

int main()
{
   int status;
   sem_t *semaphore =  sem_open("/sema", O_CREAT,  0777, 1);

   pid_t pid = fork();
   if(pid == 0) {
      printf("child\n");
      sem_post(semaphore);
      sem_close(semaphore);
   }
   else {
      sem_wait(semaphore);
      printf("parent\n");
      sem_close(semaphore);
      sem_unlink("/sema");
   }
   return 0;
}
