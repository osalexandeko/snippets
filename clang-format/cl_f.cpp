#include <iostream>
#include <stdint.h>
#include <limits.h>


#define ARR_SRC_SIZE 1024

void printAr(uint8_t *arr, int len) 
{
  printf("\n");
  for (int i = 0; i < len; i++) {
    printf("%u ", arr[i]);
  }
}

void cntSort(uint8_t const * const src,  uint8_t * const dst, int len ){
	uint8_t cntAr[_UI8_MAX] ={0};
	int i;
	uint8_t max =0;
	
	for(i = 0; i < len; i++){
		if(max < src[i]){
			max  =  src[i];
		}
		cntAr[src[i]]++;
	}
	
	for(i = 1; i <= max; i++){
		cntAr[i] += cntAr[i - 1];
	}
	
	for(i = 0; i < len; i++){
		cntAr[src[i]]--;
		dst[cntAr[src[i]]]=src[i];
	}
}



int main(int argc, char** argv) {
	uint8_t src[] = {4,3,6,3,77,255,13,2,4,5};
	uint8_t dst[ARR_SRC_SIZE] = {0};
	int src_size =  sizeof(src)/sizeof(src[0]) ;
	printAr(src, src_size);
	cntSort(src,dst, src_size );
	printAr(dst, src_size);
	return 0;
}