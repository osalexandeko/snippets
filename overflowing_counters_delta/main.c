#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 

int main(int argc, char *argv[]) {
	uint8_t cnt1 = 0;
	int8_t cnt2 = 127;
	
	int i;
	//uint16_t delta = 0; //next time why 65408...
	uint8_t delta = 0;
	for(i = 0; i <= 129;i++){
		delta = cnt2 - cnt1;
		printf("delta %u\n",delta);
		cnt2++;
	}
    
	return 0;
}
