/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Match filter
	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include "fir.h"

void fir (
  data_t *y,
  data_t x
  )
{

	coef_t c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	
	// Write your code here
	static	
		data_t shift_reg[N];
		acc_t acc;
		int i;

  #pragma HLS ARRAY_PARTITION variable=shift_reg cyclic factor=32 dim=1
  #pragma HLS ARRAY_PARTITION variable=c cyclic factor=32 dim=1

  // We can try to seperate the loop to two loops: one for TDL (tapped delay line), one for MAC (multiply and accumulate)

TDL:
  for (i = N - 1; i > 0; i--){
    #pragma HLS unroll factor=32
    #pragma HLS pipeline II=1
    shift_reg[i] = shift_reg[i - 1];
  }
  shift_reg[0] = x;


	acc = 0;
MAC:
	for (i = N - 1; i >= 0; i--){
    #pragma HLS unroll factor=32
    #pragma HLS pipeline II=1
      acc += shift_reg[i] * c[i];
    }
  
	*y = acc;
}

