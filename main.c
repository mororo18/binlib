#include <stdio.h>
#include "bmath.h"

int main(){
	bin_int8_t a = "01010";
	bin_int8_t b = "10101";
	bin_int8_t c;

	bin_sum(a, b, c);
	return 0;
}
