#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*******************************************************************************
 * structure contains IIR filter coefficients:
 * Y[z]/X[z] = (b0*z + b1* z^-1 + b2*z^-2)/(z + a0*z^-1 + a1*z^-2)
 * y[n] + a0*y[n-1]+a1*y[n-2] = b0*x[n] + b1*x[n - 1] + b2*x[n - 2]
 ******************************************************************************/
typedef struct
{
  int32_t b0;
  int32_t b1;
  int32_t b2;
  int32_t a0;
  int32_t a1;
} IIR_coef_t;

/*******************************************************************************
 * In order to avoid floating point ops. abuse we will:
 * 1. multiply obj. by  coeff_devider
 * 2. make calculations using int.
 * 3. then divide the result to get integer approx. of floating points result
 ******************************************************************************/
#define IIR_COEF_DIV (10000ULL)

//IIR 50 Hz coefficients:
//b0 = 0.133831, b1 = 0.000000, b2 = -0.133831, a0 = -1.647552, a1 = 0.732339
static IIR_coef_t coefs50_Hz =
  { .b0 = 0.133831 * IIR_COEF_DIV, .b1 = 0.000000 * IIR_COEF_DIV, .b2 =
      -0.133831 * IIR_COEF_DIV, .a0 = -1.647552 * IIR_COEF_DIV, .a1 = 0.732339
      * IIR_COEF_DIV };

int main(int argc, char *argv[]) {
	
	int32_t * ptr = &coefs50_Hz;
	for(int i = 0; i < sizeof(IIR_coef_t)/sizeof(coefs50_Hz.a0); i++){
		printf("\n");
		printf("%d",  *(ptr + i) );
	}
	
	return 0;
}
