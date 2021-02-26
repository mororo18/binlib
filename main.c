#include <stdio.h>
#include "binlib.h"

int main(){
	bin_int32_t a = bin_assign("10000000000000000000000000001011");
	bin_int8_t b = bin_assign("10000000");
	bin_int8_t c;

    printf("uint u %u\n", bin_to_uint(a));
    printf("uint d %d\n", bin_to_int(a));
	//bin_int_add_print(a, b);
	//c = bin_int_add(a, b);
    //bin_print(c);
	return 0;
}
