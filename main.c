#include <stdio.h>
#include "binlib.h"

int main(){
	bin_int16_t a = bin_assign("1000000000001011");
	bin_int8_t b = bin_assign("00010111");
	bin_int16_t c;

	c = bin_int_sum(a, b);
	bin_print(c);
	return 0;
}
