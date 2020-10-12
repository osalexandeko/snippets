#ifndef  thread_h 
#define  thread_h 

#include <pthread.h>
#include <iostream>

class Thread
{
	public:
		Thread();
		virtual ~Thread();
		
		int start();
		int start_attr(pthread_attr_t const *  attr);
		int join();
		int detach();
		pthread_t self();
	
	virtual void* run() = 0;
	
	
	
	private:
		pthread_t  m_tid;
	int        m_running;
	int        m_detached;
};

#endif
