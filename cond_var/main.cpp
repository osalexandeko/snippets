/*
   main.cpp

   Test application for the multithreaded work queue in C++.
  
   ------------------------------------------

   Copyright (c) 2013 Vic Hargrave

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "thread.h"
#include "wqueue.h"
#include <windows.h>
#include <iostream>
#include <exception>

#define MIN_REQ_SSIZE 81920
 
class WorkItem 
{
    string m_message;
    int    m_number;
 
  public:
    WorkItem(const char* message, int number) 
          : m_message(message), m_number(number) {}
    ~WorkItem() {}
 
    const char* getMessage() { return m_message.c_str(); }
    int getNumber() { return m_number; }
}; 

class ConsumerThread : public Thread
{
    wqueue<WorkItem*>& m_queue;
 
  public:
    ConsumerThread(wqueue<WorkItem*>& queue) : m_queue(queue) {}
 
    void* run() {
        // Remove 1 item at a time and process it. Blocks if no items are 
        // available to process.
        for (int i = 0;; i++) {
            printf("thread %lu, loop %d - waiting for item...\n", 
                  (long unsigned int)self(), i);
            WorkItem* item = m_queue.remove();
            printf("thread %lu, loop %d - got one item\n", 
                  (long unsigned int)self(), i);
            printf("thread %lu, loop %d - item: message - %s, number - %d\n", 
                  (long unsigned int)self(), i, item->getMessage(), 
                   item->getNumber());
            delete item;
        }
        return NULL;
    }
};

int main(int argc, char** argv)
{
	
	//test1 try catch testing
	int * tarr = NULL;
	try {
		tarr = new int[-1000];
	}
	catch (exception & e){
		cout << "Standard exception: " << e.what() << endl;
	}
	
	if(NULL != tarr){
		delete[] tarr;
		cout << "deleted "<< endl;
	}else{
		cout << "********* NULL ****** "<< endl;
	}
	//e test1
	
	
	//test1
	size_t default_stack_size;
	pthread_attr_t stack_size_custom_attr;
	pthread_attr_init(&stack_size_custom_attr);
	pthread_attr_getstacksize(&stack_size_custom_attr,
               &default_stack_size);
    // print the new stack size 
    printf("old stack size-> %d\n", default_stack_size);          
               
    if (default_stack_size < MIN_REQ_SSIZE) {
     
    	pthread_attr_setstacksize(&stack_size_custom_attr,
                  (size_t)MIN_REQ_SSIZE);
	}   
	
		pthread_attr_getstacksize(&stack_size_custom_attr,
               &default_stack_size);
    // print the new stack size 
    printf("New stack size-> %d\n", default_stack_size);          
               
	//etest1
	
	//cout << "arg:" << argc << endl;

    // Process command line arguments
    if ( argc != 2 ) {
        printf("usage: %s <iterations>\n", argv[0]);
        exit(-1);
    }
    int iterations = atoi(argv[1]);
 
    // Create the queue and consumer (worker) threads
    wqueue<WorkItem*>  queue;
    ConsumerThread* thread1 = new ConsumerThread(queue);
    ConsumerThread* thread2 = new ConsumerThread(queue);
//    ConsumerThread* thread3 = new ConsumerThread(queue);
//    ConsumerThread* thread4 = new ConsumerThread(queue);
//    ConsumerThread* thread5 = new ConsumerThread(queue);
//    ConsumerThread* thread6 = new ConsumerThread(queue);
//    ConsumerThread* thread7 = new ConsumerThread(queue);
//    ConsumerThread* thread8 = new ConsumerThread(queue);
    
    
    thread1->start_attr(&stack_size_custom_attr);
    thread2->start_attr(&stack_size_custom_attr);
//    thread3->start();
//    thread4->start();
//    thread5->start();
//    thread6->start();
//    thread7->start();
//    thread8->start();
 
    // Add items to the queue
    WorkItem* item;
    for (int i = 0; i < iterations; i++) {
        item = new WorkItem("abc", 123);
      queue.add(item);
        item = new WorkItem("def", 456);
        queue.add(item);
        item = new WorkItem("ghi", 789);
        queue.add(item);
       // pthread_cond_broadcast(queue.getCond());
        Sleep(1);
    }
 
    // Wait for the queue to be empty
    while (queue.size() > 0);
    pthread_attr_destroy(&stack_size_custom_attr);
    printf("done\n");
    exit(0);
}
