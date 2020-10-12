#include "main.hpp"


/* Open serial port*/
HANDLE serialHandle;

/*command pairs*/
command_pair_map_t command_pairs;

/*command info pairs*/
info_pair_map_t com_info_pairs;

/*serial sync*/
pthread_mutex_t serial_mutex;
pthread_mutex_t serial_buffer_mutex;

 



/*used to send commands*/
static uint8_t CMD_AR[CMD_ARR_SZ] = {0};					

/*global serial buffer*/					
static uint8_t gSerialBuffer[SERIAL_BUFFER_MAX_SIZE];

/*serial number*/
uint8_t sn = 0;
uint32_t sn_wait_cnt =0;
#define MAX_SN_WAIT  (5)



/*init commands*/
void initCommands(command_pair_map_t & command_pairs, info_pair_map_t & com_info_pairs){
	command_pairs.insert(command_pair_t( "help",HELP)); 
	com_info_pairs.insert(info_pair_t( HELP,"help command")); 
	
	command_pairs.insert(command_pair_t( "trcv",TRCV));
	com_info_pairs.insert(info_pair_t( TRCV,"trcv command syntax: trcv <file name>")); 
	
	command_pairs.insert(command_pair_t( "3",CMD_3));
	com_info_pairs.insert(info_pair_t( CMD_3,"3 command syntax: 3 power[Watt]")); 
	
	command_pairs.insert(command_pair_t( "42",CMD_42));
	com_info_pairs.insert(info_pair_t( CMD_42,"dimming, 42 command syntax: 42 dim")); 
	
	command_pairs.insert(command_pair_t( "56",CMD_56));
	com_info_pairs.insert(info_pair_t( CMD_56,"get status: 56")); 
	
	
	command_pairs.insert(command_pair_t( "142",CMD_142));
	com_info_pairs.insert(info_pair_t( CMD_142,"142 +(color ratio config) + enter")); 
	
	command_pairs.insert(command_pair_t( "145",CMD_145));
	com_info_pairs.insert(info_pair_t( CMD_145,"145 command is taken from cmd145.txt\n If 145 19 then open loop table")); 
	
	command_pairs.insert(command_pair_t( "146",CMD_146));
	com_info_pairs.insert(info_pair_t( CMD_146,"146 command is taken from cmd146.txt")); 

	command_pairs.insert(command_pair_t( "150",CMD_150));
	com_info_pairs.insert(info_pair_t( CMD_150,"150 : UVX_Lamp_SetConfig_Request ")); 	 
	 
	command_pairs.insert(command_pair_t( "151",CMD_151));
	com_info_pairs.insert(info_pair_t( CMD_151,"151 : Get UVX Lamp parameters ")); 
	
	command_pairs.insert(command_pair_t( "152",CMD_152));
	com_info_pairs.insert(info_pair_t( CMD_152,"152 : Set/Clear UVX Lamp into/From UVC Mode "));
	 
	command_pairs.insert(command_pair_t( "156",CMD_156));
	com_info_pairs.insert(info_pair_t( CMD_156,"156 : UVX Lamp / Light gonfig set dim"));

	command_pairs.insert(command_pair_t( "157",CMD_157));
	com_info_pairs.insert(info_pair_t( CMD_157,"157 : UVX Lamp / Light gonfig get dim"));
	
	command_pairs.insert(command_pair_t( "158",CMD_158));
	com_info_pairs.insert(info_pair_t( CMD_158,"158 : UVX Lamp / Light gonfig set min dim"));
	
	command_pairs.insert(command_pair_t( "159",CMD_159));
	com_info_pairs.insert(info_pair_t( CMD_159,"159 : UVX Lamp / Light gonfig get min dim"));
	
	
	
	
	command_pairs.insert(command_pair_t( "254",OPCOD_GPIO_TEST));
	com_info_pairs.insert(info_pair_t( OPCOD_GPIO_TEST,"254, GPIO_TEST , use: 254 1 [enter]")); 
	
	
	command_pairs.insert(command_pair_t( "exit",EXIT));
	com_info_pairs.insert(info_pair_t( EXIT,"exit command")); 
}

/*init serial*/
void init_serial(string & comPort){
	comPort = string("\\\\.\\")+=comPort;
 	serialHandle = CreateFile(comPort.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	// Do some basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);
	GetCommState(serialHandle, &serialParams);
	serialParams.BaudRate = CBR_38400;
	serialParams.ByteSize = 8;
	serialParams.StopBits = ONESTOPBIT;
	serialParams.Parity = NOPARITY;
	SetCommState(serialHandle, &serialParams);
	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 5000;
	timeout.ReadTotalTimeoutConstant = 5000;
	timeout.ReadTotalTimeoutMultiplier = 5000;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;
	SetCommTimeouts(serialHandle, &timeout);
}

/* Calculate checksum */
uint8_t CalcChecksum(uint8_t* pBuff, uint8_t ucSize)
{
	uint8_t i, ucCs = 0;
    for (i = 0; i < ucSize; i++){
        ucCs -= pBuff[i];
    }
    return ucCs;
}




/*write serial request*/
void write_serial_cmd(uint8_t lpBuffer[], size_t sz ){
	uint8_t cs = CalcChecksum(CMD_AR, sz);
	CMD_AR[sz -2] = cs;
  	printf("\n CS: %02X\n", cs);
 
	printf("TX: ");
	for(int j =0;  j < sz; j++){
		printf("%02X ", CMD_AR[j]);
   	}
	printf("\n");
	 
	
	DWORD dNoOFBytestoWrite;         // No of bytes to write into the port
	DWORD dNoOfBytesWritten = 0;     // No of bytes written to the port
	dNoOFBytestoWrite = sz;
	
	pthread_mutex_lock(&serial_mutex);
	WriteFile(serialHandle,        // Handle to the Serial port
       CMD_AR,     // Data to be written to the port
       dNoOFBytestoWrite,  //No of bytes to write
       &dNoOfBytesWritten, //Bytes written
       NULL);
    pthread_mutex_unlock(&serial_mutex);
}

/*read serial responce*/
void read_serial_resp(uint8_t * sRsp){
	//read   
    char TempChar;                               //Temporary character used for reading
	uint8_t SerialBuffer[SERIAL_BUFFER_MAX_SIZE] = {0};//Buffer for storing Rxed Data
	DWORD NoBytesRead = 0;
	int i = 0;
	
	
	do
	 {
	 	
	   pthread_mutex_lock(&serial_mutex);
	   ReadFile( serialHandle,    //Handle of the Serial port
	             &TempChar,       //Temporary character
	             sizeof(TempChar),//Size of TempChar
	             &NoBytesRead,    //Number of bytes read
	             NULL);
	   pthread_mutex_unlock(&serial_mutex);
	   //printf("%d. ", TempChar);
	
	   pthread_mutex_lock(&serial_buffer_mutex);	
	   SerialBuffer[i] = TempChar;// Store Tempchar into buffer
	   pthread_mutex_unlock(&serial_buffer_mutex);
	   i++;
	   if(SERIAL_BUFFER_MAX_SIZE <= i){
			break;
	   }
	  }
	
	while (NoBytesRead > 0);
 
//    printf("RX Hex: ");
//    for(int j =0;  j < i; j++){
//		printf("%02X ", SerialBuffer[j]);
//   	}


   	if(sn == SerialBuffer[CMD_ARR_SN_INDEX]){
	   	printf("\nRX Dec: ");
	    for(int j =0;  j < i; j++){
			printf("%d ", SerialBuffer[j]);
			sRsp[j] = SerialBuffer[j]; //clean buffer.
	   	}
	   	printf("\n");
	   	
		if(OPCOD_GPIO_TEST == gSerialBuffer[CMD_ARR_SN_INDEX+1] ){
			cout << "###########################################"<<endl;
			printf("Analog measurment UVC1 %d[V] \n",gSerialBuffer[8] );
			printf("Analog measurment UVC2 %d[V] \n",gSerialBuffer[9] );
			printf("Analog measurment UVC3 %d[V] \n",gSerialBuffer[10] );
			printf("Analog measurment UVC4 %d[V] \n",gSerialBuffer[11] );
			printf("MODE_SELECT %d  \n",gSerialBuffer[12] );
			printf("PIR_IN %d  \n",gSerialBuffer[13] );
			cout << "###########################################"<<endl;
			
		}
	}
}

/*parse user input*/
void parseUserInput(string &  userInput, string  (&cmdArgs)[CMD_ARGS_MAX_NUM] , int * argc ){
	int i = 0;
	string delimiter = " ";
	size_t pos = 0;
	while ((pos = userInput.find(delimiter)) != string::npos) {
	    cmdArgs[i++] = userInput.substr(0, pos);
	    userInput.erase(0, pos + delimiter.length());
	}
	cmdArgs[i] = userInput;
	* argc = i;
}

/*true iff input string is a number*/
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

/*handle console commands*/
void cmd(void){
	size_t  sz = 0;
	string  userInput;
	string cmdArgs[CMD_ARGS_MAX_NUM];
	int argc;
	
	do{
		getline(std::cin, userInput);
		parseUserInput(userInput,cmdArgs,&argc);
		
		//cout << "argc = " << argc<<endl;
	    /*for(int i = userInput.size(); 0 <= i; i--){
			printf("->%c<-\n", userInput[i]);
		}*/
		
		if(command_pairs.find(cmdArgs[0])== command_pairs.end()){
			cout << "Error try again, print \"help\"" << endl;
			continue;
		}
		command_index_t ind = command_pairs.at(cmdArgs[0]);
		switch(ind){
			case HELP:{
				
				command_pair_map_t::iterator itr; 
				for (itr = command_pairs.begin(); itr != command_pairs.end(); ++itr) { 
			    	cout << '\t' <<  itr->first  << " - " << com_info_pairs.at(itr->second) << '\n'; 
			    	
				} 
				break;
			}
			
			case TRCV:{	
				printf("dummy trcv \n");
				break;
			}
			
			case CMD_3:{
				takeFromFile("./cmd3.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				if (1 <= argc){
					if(is_number(cmdArgs[1])){
						CMD_AR[8]   = stoi(cmdArgs[1]);
					}else{
						cout << "Error try again,  ener a number" << endl;
						continue;
					}
				}
				printf("power : %d [Watt] \n",CMD_AR[8] );
				write_serial_cmd( CMD_AR, sz);  
				 
				break;
			}
			
			
			case CMD_42:{
				takeFromFile("./cmd42.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				if (1 <= argc){
					
					if(is_number(cmdArgs[1])){
					
				 		CMD_AR[8]   = stoi(cmdArgs[1]);
					}else{
						cout << "Error try again,  ener a number" << endl;
						continue;
					}
				}
				printf("please wait for response ...\n");
				write_serial_cmd( CMD_AR, sz);  
			 
				break;
			} 
			
			case CMD_56:{
				takeFromFile("./cmd56.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				write_serial_cmd( CMD_AR, sz);  
				
				 
				
				printf("power : %d [Watt] \n",gSerialBuffer[8] );
				printf("Max power : %d [Watt] \n",gSerialBuffer[9] );
				
				break;
			}
			
			case CMD_142:{
				
				takeFromFile("./cmd142.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				printf("please wait for response ...\n");
				write_serial_cmd( CMD_AR, sz);  
	             
				break;
			}
			
			case CMD_145:{
				
				printf("%d \n", CMD_AR[25]);
				
				takeFromFile("./cmd145.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				if (1 <= argc){
					if(is_number(cmdArgs[1])){
						CMD_AR[24]   = stoi(cmdArgs[1]);
					}else{
						cout << "Error try again,  ener a number" << endl;
						continue;
					}
				}
				write_serial_cmd( CMD_AR, sz);  
				 
				break;	
			}
			
			case CMD_146:{
				takeFromFile("./cmd146.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				write_serial_cmd( CMD_AR, sz);  
				read_serial_resp(gSerialBuffer);
				break;	
			}
			
			case CMD_150:{
				
				takeFromFile("./cmd150.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				printf("please wait for response ...\n");
				write_serial_cmd( CMD_AR, sz);  
	             
				break;
			}
			case CMD_151:{
				
				takeFromFile("./cmd151.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				printf("please wait for response ...\n");
				write_serial_cmd( CMD_AR, sz);  
	             
				break;
			}
			case CMD_152:{
				
				takeFromFile("./cmd152.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				printf("please wait for response ...\n");
				write_serial_cmd( CMD_AR, sz);  
	             
				break;
			}
			
			case CMD_156:{
				
				takeFromFile("./cmd156.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				printf("cmd156, please wait for response ...\n");
				write_serial_cmd( CMD_AR, sz);  
	             
				break;
			}
			
			case CMD_157:{
				takeFromFile("./cmd157.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				printf("cmd157, please wait for response ...\n");
				write_serial_cmd( CMD_AR, sz);  
	           	break;
			}
			
			case CMD_158:{
				takeFromFile("./cmd158.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				printf("cmd159, please wait for response ...\n");
				write_serial_cmd( CMD_AR, sz);  
	           	break;
			}
			
			case CMD_159:{
				takeFromFile("./cmd159.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				printf("cmd159, please wait for response ...\n");
				write_serial_cmd( CMD_AR, sz);  
	           	break;
			}
			
			case OPCOD_GPIO_TEST:{
				/*
				PD0	A2D	CS_UVC1	Analog measurment UVC1
				PD1		CS_UVC2	Analog measurment UVC2
				PD2		CS_UVC3	Analog measurment UVC3
				PD3		CS_UVC4	Analog measurment UVC4
				PA8	Control FANs	MODE_SELECT	1'- FANs ON and UVC dimming EN. '0' FANs off and UVC dimming disabled.
				PD13	PIR INPUT	PIR_IN	Input From Relay. Normally close- "0". Will change to "1" when detects movement
				*/
				takeFromFile("./cmd254.txt", CMD_AR,sz);
				CMD_AR[CMD_ARR_SN_INDEX] = sn;
				if(1 <= argc){
					if(is_number(cmdArgs[1])){
						CMD_AR[8] =	stoi(cmdArgs[1]);
					}else{
						cout << "Error try again,  ener a number" << endl;
						continue;
					}
				}
				printf("please wait for response ...\n");
				sn_wait_cnt = 0;
				pthread_mutex_lock(&serial_buffer_mutex);
				write_serial_cmd( CMD_AR, sz);
				pthread_mutex_unlock(&serial_buffer_mutex);
				break;
			}
			case EXIT:{
				CloseHandle(serialHandle);
			 	exit(EXIT_SUCCESS);
				break;
			}
	    	default:
				break;
		}
	}
	while(true);
	cout << userInput << endl;
}

/*********************************************************************************
* Takes data from file to dst.
* @param  path, path to file.
* @param  dst, destination.
* @param  sz, size of data taken from file to dst, in bytes.
*********************************************************************************/
int takeFromFile(string path, uint8_t * dst,size_t & sz){
	int x = 0;
	int i = 0;
	ifstream inFile;
	inFile.open(path);
	if (!inFile) {
	    cout << "Unable to open file";
	    exit(1);  
	}
	cout << "trying to read: "<< path << endl;
	
	while (inFile >> x ) {
	   dst[i++] = x;
	}
	
	sz = i;
	cout <<  endl;
	inFile.close();
	return 0;
}

void* serial_listener(void*arg){
	while(true){
	//	memset(gSerialBuffer,0,SERIAL_BUFFER_MAX_SIZE);
		read_serial_resp(gSerialBuffer);
		 
	}
	return NULL;
}


/*the main function*/
int main(int argc, char** argv) { 
	
 	if(MAIN_ARGS_MIN_NUMBER > argc ){
		cout << "enter com port and serial number, example : COM15 77"<< endl;
		exit(EXIT_FAILURE);
	}
	cout << "connecting to port: "<< argv[MAIN_ARGS_COM_PORT_INDEX] << endl;
	initCommands(command_pairs,com_info_pairs);
	string comPort = string(argv[MAIN_ARGS_COM_PORT_INDEX]);
	init_serial(comPort);
	
	sn = atoi(argv[MAIN_ARGS_SN] );
	printf("sn: %d\n", sn);
	
	pthread_t ser_listen;
	pthread_mutex_init(&serial_mutex, NULL);
	pthread_create(&ser_listen, NULL, serial_listener, NULL);
	
	pthread_mutex_init(&serial_buffer_mutex,NULL);
	cmd();
	return 0;
}
