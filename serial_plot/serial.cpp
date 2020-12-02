#include "serial.h"



/* Open serial port*/
HANDLE serialHandle;



 /*init serial*/
void init_serial(string & comPort){
	comPort = string("\\\\.\\")+=comPort;
	serialHandle = CreateFile(comPort.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); 
  
	// Do some basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);
	GetCommState(serialHandle, &serialParams);
	serialParams.BaudRate = CBR_115200;
	serialParams.ByteSize = 8;
	serialParams.StopBits = ONESTOPBIT;
	serialParams.Parity = NOPARITY;
	SetCommState(serialHandle, &serialParams);
	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;
	SetCommTimeouts(serialHandle, &timeout);
}




/*read serial responce*/
//void read_serial_resp(uint8_t * sRsp){
//	//read   
//    char TempChar; //Temporary character used for reading
//	uint8_t SerialBuffer[SERIAL_BUFFER_MAX_SIZE];//Buffer for storing Rxed Data
//	DWORD NoBytesRead;
//	int i = 0;
//	do
//	 {
//	   ReadFile( serialHandle,           //Handle of the Serial port
//	             &TempChar,       //Temporary character
//	             sizeof(TempChar),//Size of TempChar
//	             &NoBytesRead,    //Number of bytes read
//	             NULL);
//	
//	   SerialBuffer[i] = TempChar;// Store Tempchar into buffer
//	   sRsp[i] = TempChar;
//	   i++;
//	   if(i >= RX_SER_BUF_MAX_SZ){
//			break;
//	   }
//	  }
//	
//	while (NoBytesRead > 0);
//	i=0;
//}



//
//void * serial_producer_task(void * p){
//	char TempChar; //Temporary character used for reading
//	DWORD NoBytesRead;
//	while(1){
//	  
//	}
//}




