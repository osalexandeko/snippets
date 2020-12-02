#include <iostream>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

typedef union{
	void * p;
	uint64_t u;
} p2u_t;


void * aligned8Malloc(int nb){
	uint64_t adr0 ;
	p2u_t p2u;
	p2u.p = malloc(nb+16);
	adr0 = p2u.u;
	printf("original pointer: %X \n", (adr0));
	adr0 = (( adr0 + 8) & 0xFFFFFFFFFFFFFFF8);
	printf("alighen pointer: %X \n", (adr0));
	uint64_t * u64p = (uint64_t * )adr0;
	*u64p = p2u.u; 
	printf("saved: %X in %p\n", *u64p,u64p);
	printf("ret: %p \n", u64p + 1);
	return u64p + 1;
}


void * aligned8free(void * p){
	printf("rec: %p \n", p);
	p-=8;
	printf("rec -8: %p \n",p);
	uint64_t adr = *((uint64_t * )p);
	printf("freed pointer: %X \n", adr);
	p = (void *)(adr) ;
	printf("freed: %p \n", p );
	free(p);
}

template<typename T, size_t N>
void arrayDegradationTest(T (&arr)[N]){
	printf("%d", sizeof arr);
}


void segfaultTest(){
//	//case 1
//	//uint32_t * p = NULL;
//	
//	//case2:
//	uint32_t * p = NULL;
//	int a = *p;
}

int main(int argc, char** argv) {
	void * ptr_test = aligned8Malloc(8);
	aligned8free(ptr_test);
	uint8_t arr[10] = {0,1,2,3,4,5,6,7,8,9};
	arrayDegradationTest(arr);
	
	
	
	///
	segfaultTest();
	
	
	return 0;
}
