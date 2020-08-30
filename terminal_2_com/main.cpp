#include "main.hpp"

/* Open serial port*/
HANDLE serialHandle;

/*command pairs*/
command_pair_map_t command_pairs;

/*command info pairs*/
info_pair_map_t com_info_pairs;

/*array with the command*/



/*used to send commands*/
static uint8_t CMD_AR[CMD_ARR_SZ] = {0};					

/*global serial buffer*/					
static uint8_t gSerialBuffer[SERIAL_BUFFER_MAX_SIZE];



/*init commands*/
void initCommands(command_pair_map_t & command_pairs, info_pair_map_t & com_info_pairs){
	command_pairs.insert(command_pair_t( "help",HELP)); 
	com_info_pairs.insert(info_pair_t( HELP,"help command")); 
	
	command_pairs.insert(command_pair_t( "trcv",TRCV));
	com_info_pairs.insert(info_pair_t( TRCV,"trcv command syntax: trcv <file name>")); 
	
	command_pairs.insert(command_pair_t( "3",CMD_3));
	com_info_pairs.insert(info_pair_t( CMD_3,"3 command syntax: 3 power[Watt]")); 
	
	command_pairs.insert(command_pair_t( "42",CMD_42));
	com_info_pairs.insert(info_pair_t( CMD_42,"42 command syntax: 42 dim")); 
	
	command_pairs.insert(command_pair_t( "56",CMD_56));
	com_info_pairs.insert(info_pair_t( CMD_56,"get status: 56")); 
	
	
	command_pairs.insert(command_pair_t( "142",CMD_142));
	com_info_pairs.insert(info_pair_t( CMD_142,"142 command syntax: min dim max,")); 
	
	command_pairs.insert(command_pair_t( "145",CMD_145));
	com_info_pairs.insert(info_pair_t( CMD_145,"145 command is taken from cmd145.txt\n If 145 19 then open loop table")); 
	
	command_pairs.insert(command_pair_t( "146",CMD_146));
	com_info_pairs.insert(info_pair_t( CMD_146,"146 command is taken from cmd146.txt")); 
	
	
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
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
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
	
	WriteFile(serialHandle,        // Handle to the Serial port
       CMD_AR,     // Data to be written to the port
       dNoOFBytestoWrite,  //No of bytes to write
       &dNoOfBytesWritten, //Bytes written
       NULL);
}

/*read serial responce*/
void read_serial_resp(uint8_t * sRsp){
	//read   
    char TempChar; //Temporary character used for reading
	uint8_t SerialBuffer[SERIAL_BUFFER_MAX_SIZE];//Buffer for storing Rxed Data
	DWORD NoBytesRead;
	int i = 0;
	
	do
	 {
	   ReadFile( serialHandle,           //Handle of the Serial port
	             &TempChar,       //Temporary character
	             sizeof(TempChar),//Size of TempChar
	             &NoBytesRead,    //Number of bytes read
	             NULL);
	
	   SerialBuffer[i] = TempChar;// Store Tempchar into buffer
	   i++;
	  }
	
	while (NoBytesRead > 0);
      
    printf("RX Hex: ");
    for(int j =0;  j < i; j++){
		printf("%02X ", SerialBuffer[j]);
   	}
   	
   	printf("\nRX Dec: ");
    for(int j =0;  j < i; j++){
		printf("%d ", SerialBuffer[j]);
		sRsp[j] = SerialBuffer[j]; //clean buffer.
   	}
    
    printf("\n");
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

/*handle console commands*/
void cmd(void){
	size_t  sz = 0;
	string  userInput;
	string cmdArgs[CMD_ARGS_MAX_NUM];
	int argc;
	do{
		getline(std::cin, userInput);
		parseUserInput(userInput,cmdArgs,&argc);
		
		cout << "argc = " << argc<<endl;
		
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
				if (1 <= argc){
					CMD_AR[8]   = stoi(cmdArgs[1]);
				}
				printf("power : %d [Watt] \n",CMD_AR[8] );
				write_serial_cmd( CMD_AR, sz);  
				read_serial_resp(gSerialBuffer);
				break;
			}
			
			
			case CMD_42:{
				takeFromFile("./cmd42.txt", CMD_AR,sz);
				if (1 <= argc){
					CMD_AR[8]   = stoi(cmdArgs[1]);
				}
				write_serial_cmd( CMD_AR, sz);  
				read_serial_resp(gSerialBuffer);
				break;
			} 
			
			case CMD_56:{
				takeFromFile("./cmd56.txt", CMD_AR,sz);
				write_serial_cmd( CMD_AR, sz);  
				read_serial_resp(gSerialBuffer);
				
				printf("power : %d [Watt] \n",gSerialBuffer[8] );
				printf("Max power : %d [Watt] \n",gSerialBuffer[9] );
				
				break;
			}
			
			case CMD_142:{
				
				takeFromFile("./cmd142.txt", CMD_AR,sz);
				write_serial_cmd( CMD_AR, sz);  
	            read_serial_resp(gSerialBuffer);
				break;
			}
			
			case CMD_145:{
				
				printf("%d \n", CMD_AR[25]);
				
				takeFromFile("./cmd145.txt", CMD_AR,sz);
				if (1 <= argc){
					CMD_AR[24]   = stoi(cmdArgs[1]);
				}
				write_serial_cmd( CMD_AR, sz);  
				read_serial_resp(gSerialBuffer);
				break;	
			}
			
			case CMD_146:{
				
				takeFromFile("./cmd146.txt", CMD_AR,sz);
				write_serial_cmd( CMD_AR, sz);  
				read_serial_resp(gSerialBuffer);
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


/*the main function*/
int main(int argc, char** argv) {
	
 	if(MAIN_ARGS_MIN_NUMBER > argc ){
		cout << "enter com port, example : COM15 "<< endl;
		exit(EXIT_FAILURE);
	}
	cout << "connecting to port: "<< argv[MAIN_ARGS_COM_PORT_INDEX] << endl;
	initCommands(command_pairs,com_info_pairs);
	string comPort = string(argv[MAIN_ARGS_COM_PORT_INDEX]);
	init_serial(comPort);
	cmd();
	return 0;
}
