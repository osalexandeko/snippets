#ifndef SERIAL_HPP
#define SERIAL_HPP
#include "main.hpp"

/* Open serial port*/
extern HANDLE serialHandle;

/*global serial buffer*/
#define  RX_SER_BUF_MAX_SZ 8 


void init_serial(string & comPort);
void read_serial_resp(uint8_t * sRsp);

#define NUM_OF_BUFFS 2
class SerialConsumerThread : public Thread{
  wqueue<uint8_t> & m_queue;
  uint8_t * RxCBfP[NUM_OF_BUFFS];
  int rx_ind = 0;
  int ready_ind = 1;
   
  
  public:
    SerialConsumerThread(wqueue<uint8_t>& queue, uint8_t *  bf1, uint8_t *  bf2  ) : 
			m_queue(queue) {
		rx_ind = 0;
		ready_ind = 1;
		RxCBfP[rx_ind] = bf1;
		RxCBfP[ready_ind] = bf2;
	}
    void* run() {
        for (int i = 0;; i++) {
            
            //printf("%d\n",RxCBfP[rx_ind][i]);
            if( RX_SER_BUF_MAX_SZ - 1 < i ){ /*the buffer is full, switch it*/
            	if(0 == rx_ind){
            		rx_ind = 1;
					ready_ind = 0;	
				}else{
					rx_ind = 0;
					ready_ind = 1;
				}
            	i = 0;
            	 
			}
			RxCBfP[rx_ind][i] = m_queue.remove();
			printf("%u %u\n",rx_ind , RxCBfP[ready_ind][i]);
		}
        return NULL;
    }
    
    /*get ready to read data array*/
    uint8_t * getRxData(){
    	return RxCBfP[ready_ind];
	}
	
	uint8_t getCurrBuffNum(){
		return rx_ind;
	}
};

class SerialProduserThread : public Thread{
	uint8_t item = 0; 
	DWORD NoBytesRead;
	wqueue<uint8_t> & m_queue;
	public:
	SerialProduserThread(wqueue<uint8_t>& queue  ) : 
		m_queue(queue) {
			NoBytesRead = 0;
		}
	void* run() {
		for (int i = 0;; i++) {
			/*read 1 byte from uart and put to queue*/
			do{
				ReadFile( serialHandle,&item,sizeof(uint8_t) ,&NoBytesRead,NULL);
				//printf("%u %u\n",NoBytesRead , item);
			}while (NoBytesRead == 0);
			NoBytesRead = 0;
		    //m_queue.add(item);0.25*sin(10*(x));/
		    //m_queue.add(64*(1 + sin(0.1*(i))));
		    m_queue.add(item);
		}
		return NULL;
	}
};



#endif
