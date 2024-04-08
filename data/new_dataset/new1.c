#include <stdio.h>
#include "ap_int.h"

#define N 9

typedef ap_int<6> dinA_t;
typedef ap_int<12> dinB_t;
typedef ap_int<22> dinC_t;
typedef ap_int<33> dinD_t;

typedef ap_int<18> dout1_t;
typedef ap_uint<13> dout2_t;
typedef ap_int<22> dout3_t;
typedef ap_int<6> dout4_t;

void cpp_ap_int_arith(dinA_t inA,dinB_t inB,dinC_t inC,dinD_t inD,dout1_t *out1,dout2_t *out2,dout3_t *out3,dout4_t *out4);


void cpp_ap_int_arith(dinA_t  inA, dinB_t  inB, dinC_t  inC, dinD_t  inD,
  		       dout1_t *out1, dout2_t *out2, dout3_t *out3, dout4_t *out4
  ) {

	// Basic arithmetic operations
	*out1 = inA * inB;
	*out2 = inB + inA;
	*out3 = inC / inA;
	*out4 = inD % inA;

} 
