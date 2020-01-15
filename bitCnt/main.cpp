#include <iostream>
#include <stdint.h>
#include <limits.h>

static uint8_t bitCntTbl[_UI8_MAX+1] = {0};

void initBitCntTbl(void){
	for(uint32_t i = 1; i <= _UI8_MAX; i++){
		bitCntTbl[i] = bitCntTbl[i/2] + (i&0x01);
	}
}

uint8_t cntBitsU8(uint8_t u8){
	return bitCntTbl[u8];
}


uint8_t cntBitsU32(uint32_t u32){
	uint32_t mask = 0x000000FF;
	uint8_t res = 0;
	int upLim = CHAR_BIT * sizeof(uint32_t);
	for(int s = 0 ; s < upLim; s+= CHAR_BIT){
		res += bitCntTbl[(u32 >> s) & mask];
	}
	return res;
}

int main(int argc, char** argv){
	initBitCntTbl();
	uint8_t u8  = 7;
	printf("u8 %u has %u bits set\n",u8 ,     cntBitsU8(u8));
		
	uint32_t u32  = 0x10070707;
	printf("u32 0x%X has %u bits set\n",u32 ,  cntBitsU32(u32));
	
	return 0;
}
