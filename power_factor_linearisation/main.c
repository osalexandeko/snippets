#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/******************************************************************************
* y(x) = a*x + b 
* holds aproximation coefficients 
******************************************************************************/
typedef struct {
	int a_coef;
	int b_coef;
} lin_approx_coef_t;

/******************************************************************************
* y(x) = a*x + b 
* holds aproximation coefficients 
******************************************************************************/
static lin_approx_coef_t lin_approx_coef;

/******************************************************************************
* true iff lin_approx_coef is initiated
******************************************************************************/
static bool is_lin_approx_initiated = false;

/******************************************************************************
* @brief  - initiates linear approximation coefficients 
* @param - pwmV1 PWM value 1
* @param - pF1   PF 1
* @param - pwmV2 PWM value 2
* @param - pF2   PF 2
******************************************************************************/
void init_pf_lin_approx(const int pwmV1,const int pF1,const int pwmV2,
		const int pF2 ){
	lin_approx_coef.a_coef = (pF2 - pF1)/(pwmV2 - pwmV1);
	printf("lin_approx_coef.a_coef  %u\n", lin_approx_coef.a_coef);
	lin_approx_coef.b_coef = pF1 - (lin_approx_coef.a_coef)*pwmV1;
	printf("lin_approx_coef.b_coef  %u\n", lin_approx_coef.b_coef);
	is_lin_approx_initiated = true;
}

/******************************************************************************
* @brief  - fulfils linear approximation coefficients 
* @param - pwmV PWM value 
* @param - pfApprox_p   PF res. pointer
******************************************************************************/
bool get_pf_lin_approx(const uint32_t pwmV, uint32_t * const pfApprox_p  ){
	bool res = false;
	if(true == is_lin_approx_initiated){
		*pfApprox_p = pwmV * lin_approx_coef.a_coef + lin_approx_coef.b_coef;
		res = true;
	}
	return res;
}


//test
int main(int argc, char *argv[]) {
	
	int  pfApprox = 0;
	int pwmV1_to_approx = 1000;
	
//pf x 10^10	
	uint32_t pwmV1 = 1940;
	uint32_t pf1   = 692899436;
 
	
	uint32_t pwmV2 = 8112;
	uint32_t pf2   = 969720128;
	

////pf x 10^6	
//	uint32_t pwmV1 = 1940;
//	uint32_t pf1   = 692899;
//	
//	uint32_t pwmV2 = 8112;
//	uint32_t pf2   = 969720;

////pf x 10^5
//	uint32_t pwmV1 = 1940;
//	uint32_t pf1   = 69290;
//	
//	uint32_t pwmV2 = 8112;
//	uint32_t pf2   = 96972;


	
	init_pf_lin_approx(pwmV1,pf1,pwmV2,pf2);

	if(get_pf_lin_approx(pwmV1_to_approx,&pfApprox)){
		printf("get_pf_lin_approx(%d) = %d\n", pwmV1_to_approx, pfApprox);
	}else{
		printf("error\n");
	}
	
	//re init to test the difference
	init_pf_lin_approx(pwmV2,pf2,pwmV1,pf1);
	
 
	if(get_pf_lin_approx(pwmV1_to_approx,&pfApprox)){
		printf("get_pf_lin_approx(%d) = %d\n", pwmV1_to_approx, pfApprox);
	}else{
		printf("error\n");
	}
	return 0;
}
