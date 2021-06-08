#ifndef TCP_CLIENT_HPP 
#define TCP_CLIENT_HPP
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map> 


using namespace std;

typedef enum {
	HELP,
	TRCV,
	EXIT,
	CMD_3,
	CMD_42,
	CMD_56,
	CMD_142,
	CMD_145,
	CMD_146,
	CMD_150,
	CMD_151,
	CMD_152,
	CMD_156,
	CMD_157,
	CMD_158,
	CMD_159,
	CMD_160,
	CMD_161,
	CMD_162,
	OPCOD_GPIO_TEST = 254,

}command_index_t;

#define CMD_ARR_SZ (255)
#define CMD_ARR_SN_INDEX (6)


#define  info_pair_map_t map<command_index_t,string>
#define  info_pair_t pair<command_index_t,string> 
#define  command_pair_map_t map<string,command_index_t>
#define  command_pair_t pair<string,command_index_t> 

// Need to link with Ws2_32.lib, Mswsoc  k.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "8888"
#define DEFAULT_IP "192.168.21.11"



#define CMD_ARGS_MAX_NUM 64
int get_from_server(SOCKET* ptrConnectSocket, char* server_input, int server_input_sz);
int parse_and_send(SOCKET* ptrConnectSocket, char* user_input, int user_input_sz);
void initCommands(command_pair_map_t& command_pairs, info_pair_map_t& com_info_pairs);

#endif
