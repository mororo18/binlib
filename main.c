#include <stdio.h>
#include "binlib.h"

int main(){
	bin_int32_t a = bin_int_assign("00000000000000000000000000001010");
	bin_int16_t b = bin_int_assign("0000000000000101");
	bin_int32_t c;

	c = bin_int_add(a, b);      //return a pointer for a 32bit type ( 'a' is the bigger)

    printf(" (A) %dbit binary : \t", a->sz);      bin_print(a);
    printf(" (B) %dbit binary : \t\t\t", b->sz);  bin_print(b);
    printf(" (C) %dbit binary : \t", c->sz);      bin_print(c);

    bin_clear(&c);
    c = bin_from_int(127, 8);
    bin_print(c);
    //printf("uint u %u\n", bin_to_uint(a));
    //printf("uint d %d\n", bin_to_int(a));
	//bin_int_add_print(a, b);
	return 0;
}
