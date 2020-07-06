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

int main1(int argc, char** argv){
	initBitCntTbl();
	uint8_t u8  = 7;
	printf("u8 %u has %u bits set\n",u8 ,     cntBitsU8(u8));
		
	uint32_t u32  = 0x10070707;
	printf("u32 0x%X has %u bits set\n",u32 ,  cntBitsU32(u32));
	
	return 0;
}


int local_un_init(){
		uint32_t a,b,c,d,e;
	printf("a %x, b %x, c %x ,  d %x, e %x\n", a, b ,c,d,e);
}
int local_un_init1(){
		uint32_t a,b,c,d,e;
	printf("a %x, b %x, c %x ,  d %x, e %x\n", a, b ,c,d,e);
}
int local_un_init2(){
		uint32_t a,b,c,d,e;
	printf("a %x, b %x, c %x ,  d %x, e %x\n", a, b ,c,d,e);
}

int main1(){
	for(int i =0 ; i < 200; i++){
		local_un_init1();
		local_un_init2();
		local_un_init();
	}
}


/*-------------------------------------------------------------------------------------------------------------------*/
/* TYPEDEFS (STRUCTURES, UNIONS, ENUMS, CLASSES)                                                                     */
/*-------------------------------------------------------------------------------------------------------------------*/
typedef struct
  {
		uint8_t	NotInUse                        :5;        // 1..65ms ; normal 50ms; defines how fast the Power Loop is converged to the target dim (see Power.c:
		uint8_t	ConfigByDimmerFlag              :1;        // if '0' opcode 142 payload is already contain all data as generated at the Host(=0)side rather than at the dimmer side (=1)
		uint8_t	u8SendAck_OnPublicAddress_Flag  :1;        // Flag: 1/0: if to respond with ack on a opcode142 public address command when Slot is 1
		uint8_t	u8SaveToFlash                   :1;        // bool flag 1/0
  } tsFlags_t;


typedef union  uMultiDimFlags
{
  uint8_t byteFlags;
  struct
  {
  		uint8_t	NotInUse5                        :1;
  		uint8_t	NotInUse4                        :1;
  		uint8_t	NotInUse3                        :1;
  		uint8_t	NotInUse2                        :1;
		uint8_t	NotInUse1                        :1;        
		//int : 0;
		uint8_t	ConfigByDimmerFlag              :1;        // if '0' opcode 142 payload is already contain all data as generated at the Host(=0)side rather than at the dimmer side (=1)
		//uint8_t : 0;
		uint8_t	u8SendAck_OnPublicAddress_Flag  :1;        // Flag: 1/0: if to respond with ack on a opcode142 public address command when Slot is 1
		//uint8_t : 0;
		uint8_t	u8SaveToFlash                   :1;        // bool flag 1/0
  }  tsFlags;
}
Union_MultiDimConfigFlags;



int main2(){
	Union_MultiDimConfigFlags	uFlags = (Union_MultiDimConfigFlags){0};
	uFlags.byteFlags = 0x80 ;//0b11110000;
	
//	printf("->%02X<- ", uFlags.tsFlags.NotInUse1|uFlags.tsFlags.ConfigByDimmerFlag| );
	
	
	printf("%02X  \n",uFlags.byteFlags);
	printf("NotInUse5 %u \n",uFlags.tsFlags.NotInUse5);
	printf("NotInUse4 %u \n",uFlags.tsFlags.NotInUse4);
	printf("NotInUse3 %u \n",uFlags.tsFlags.NotInUse3);
	printf("NotInUse2 %u \n",uFlags.tsFlags.NotInUse2);
	printf("NotInUse1 %u \n",uFlags.tsFlags.NotInUse1);
	printf("uFlags.tsFlags.ConfigByDimmerFlag %u \n",uFlags.tsFlags.ConfigByDimmerFlag);
	printf("uFlags.tsFlags.u8SendAck_OnPublicAddress_Flag %u \n",uFlags.tsFlags.u8SendAck_OnPublicAddress_Flag);
	printf("uFlags.tsFlags.u8SaveToFlash %u \n",uFlags.tsFlags.u8SaveToFlash);
	printf("sz %d \n", sizeof(Union_MultiDimConfigFlags));
	
//	tsFlags_t tsFlags = (tsFlags_t) {0};// 0b01110000;
//	
//	
//	printf("NotInUse %X \n",tsFlags.NotInUse);
//	printf("uFlags.tsFlags.ConfigByDimmerFlag %u \n",tsFlags.ConfigByDimmerFlag);
//	printf("uFlags.tsFlags.u8SendAck_OnPublicAddress_Flag %u \n",tsFlags.u8SendAck_OnPublicAddress_Flag);
//	printf("uFlags.tsFlags.u8SaveToFlash %u \n",tsFlags.u8SaveToFlash);
	
	
}



typedef union 
{
  uint8_t b;
  struct
  {
  		uint8_t	b0                       :1;
  		uint8_t	b1                       :1;
  		uint8_t	b2                       :1;
  		uint8_t	b3                       :1;
		uint8_t	b4                       :1;        
		uint8_t	b5               		 :1;       
		uint8_t	b6   					 :1;      
		uint8_t	b7                       :1;      
  }  u;
}
bub_t;


int main(){
	bub_t bub;
	bub.b = 0b00100100;
	//uint8_t r = bub.u.b7|bub.u.b6|bub.u.b5|bub.u.b4|bub.u.b3|bub.u.b2|bub.u.b1|bub.u.b0;
	printf("->%02X<- ", bub.u.b5);
}



