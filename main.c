#include <stdio.h>
#include "binlib.h"

int main(){
    bin_int16_t a = bin_int_assign("11010101");
    bin_int32_t b = bin_int_assign("1111111111111111");
    bin_int32_t c;

    //return a pointer (allocate memory) with the result of the addition 'a + b' with the size of the bigger type between 'a' and 'b' (32bit);
	c = bin_int_add(a, b);      

    // the current bin size is avaliable on the member 'sz' by dereferencing (a->sz);
    // the binary is printed with the number of bits indicated on the 'sz' member;
    printf("\nAddition of Binaries (signed integers):\n\n");
    printf(" (B) %dbit binary : \t", b->sz);  bin_print(b);
    printf(" (A) %dbit binary : \t\t", a->sz);      bin_print(a);
    printf("(A+B)%dbit binary : \t", c->sz);      bin_print(c);

    printf("\nResize B and do the Operation:\n\n");
	bin_int_add_print(a, b);

    printf("\nConvert binary to int:\n\n");
    printf(" (A) %dbit int : %d\n", a->sz, bin_int_to_dec(a));      
    printf(" (B) %dbit int : %d\n", b->sz, bin_int_to_dec(b)); 
    printf("(A+B)%dbit int : %d\n", c->sz, bin_int_to_dec(c));    

    printf("\nConvert binary to uint:\n\n");
    printf(" (A) %dbit int : %u\n", a->sz, bin_uint_to_dec(a));      
    printf(" (B) %dbit int : %u\n", b->sz, bin_uint_to_dec(b)); 
    printf("(A+B)%dbit int : %u\n", c->sz, bin_uint_to_dec(c));    
    // free the current memory allocated for this binary;
    bin_clear(&c);
    // return a pointer with binary with 8bit size for signed integers (-127);
    c = bin_int_from_dec(-1, 8);
    // print with its news size and value;
    bin_int8_t d = bin_int_assign("01010101");
    bin_int8_t e = bin_int_assign("00010101");
    bin_int16_t f = bin_int_multiply(d, e);

    printf("\nMultiplication of Binaries (unsigned integers):\n\n");
    printf(" (D) %dbit binary : \t\t", d->sz);  bin_print(d);
    printf(" (E) %dbit binary : \t\t", e->sz);      bin_print(e);
    printf("(D*E)%dbit binary : \t", f->sz);      bin_print(f);
    //printf("uint u %u\n", bin_to_uint(a));
    //printf("uint d %d\n", bin_to_int(a));
	//bin_int_add_print(a, b);
	return 0;
}
