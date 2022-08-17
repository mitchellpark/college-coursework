#include <stdint.h>
#include "library.h"
#include "graphics.h"
#include<stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

uint32_t Bits2Unsigned(int8_t bits[8]){
  uint32_t n = 0;
  for(int i = 7; i >= 0; i--){
    n = (2*n + bits[i]);
  }

  return n;
}


int32_t Bits2Signed(int8_t bits[8]){
	int32_t result = 0;
	result -= (pow(2, 7) * bits[7]);
	for(int i=0; i<7; i++) {
		result += (pow(2, i) * bits[i]);
	}
	return result;
}


void Increment(int8_t bits[8]){
  for(int i = 0; i < 8; i++){

    if (bits[i] == 0){
      bits[i] = 1;
      return;
    }else{
      bits[i] = 0;
    }
  }
  return;
}


void Unsigned2Bits(uint32_t n, int8_t bits[8]){
  for(int i = 0; i < 8; i++){

      if(n % 2 == 1){
        bits[i] = 1;
      }
      else{
        bits[i] = 0;
      }
      n /= 2;
  }
  return;
}
