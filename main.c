#include <stdio.h>
#include "bmath.h"

int main(){
	bin_int8_t a = bin_assign("00001011", 8);
	bin_int8_t b = bin_assign("00010111", 8);
	bin_int8_t c;

	bin_sum(a, b);
	return 0;
}
