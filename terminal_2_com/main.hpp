#ifndef MAIN_HPP
#define MAIN_HPP
#include <iostream>
#include <fstream>
#include <iterator> 
#include <map> 
#include <stdlib.h>    
#include <windows.h>
#include <stdint.h>
#include <string>
using namespace std; 


#define CH1_MSK 0x0000
#define CH2_MSK 0x1000
#define CH3_MSK 0x2000
#define CH4_MSK 0x3000 

#define CHANNELS_BITS_OFFSET 6



#define POWER_CMD {0x02,0x00,0x18,0x02,0x00,0x00,0x4D,\
					/*opcode 7*/0x2A,/*% 8*/50,0x00,0x7B,\
					0x00,/*12*/0x00,/*13*/0x20,0x7C,0x32,\
					0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,\
					0x03,0x40,/*CS 26*/0,0x03}
#define POWER_MSB_IND 12
#define POWER_LSB_IND 13
#define POWER_CHANNEL_IND  16
#define CS_IND 26



#define CMD_ARGS_MAX_NUM 64
#define MAIN_ARGS_MIN_NUMBER 2
#define MAIN_ARGS_COM_PORT_INDEX 1
#define MAIN_ARGS_SN 2

#define  SERIAL_BUFFER_MAX_SIZE 28
#define  info_pair_map_t map<command_index_t,string>
#define  info_pair_t pair<command_index_t,string> 
#define  command_pair_map_t map<string,command_index_t>
#define  command_pair_t pair<string,command_index_t> 

#define CMD_ARR_SZ (255)
#define CMD_ARR_SN_INDEX (6)

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
	OPCOD_GPIO_TEST                 = 254,
	
}command_index_t;


int takeFromFile(string path, uint8_t * dst,size_t & sz);

#endif
