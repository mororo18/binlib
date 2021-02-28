#include <stdio.h>
#include "binlib.h"

int main(){
    bin_int32_t a = bin_int_assign("11111111");
    bin_int16_t b = bin_int_assign("0000000000000101");
    bin_int32_t c;

    //return a pointer (allocate memory) with the result of the addition 'a + b' with the size of the bigger type between 'a' and 'b' (32bit);
	c = bin_int_add(a, b);      

    // the current bin size is avaliable on the member 'sz' by dereferencing (a->sz);
    // the binary is printed with the number of bits indicated on the 'sz' member;
    printf("\nAddition of Binaries:\n\n");
    printf(" (A) %dbit binary : \t", a->sz);      bin_print(a);
    printf(" (B) %dbit binary : \t", b->sz);  bin_print(b);
    printf("(A+B)%dbit binary : \t", c->sz);      bin_print(c);
    printf("\n\tPrint The Operation:\n\n");
	bin_int_add_print(a, b);

    printf("\nConvert binary to int:\n\n");
    printf(" (A) %dbit int : %d\n", a->sz, bin_to_int(a));      
    printf(" (B) %dbit int : %d\n", b->sz, bin_to_int(b)); 
    printf("(A+B)%dbit int : %d\n", c->sz, bin_to_int(c));    

    bin_print(c);

    printf("\nConvert binary to uint:\n\n");
    printf(" (A) %dbit int : %d\n", a->sz, bin_to_int(a));      
    printf(" (B) %dbit int : %d\n", b->sz, bin_to_int(b)); 
    printf("(A+B)%dbit int : %d\n", c->sz, bin_to_int(c));    
    // free the current memory allocated for this binary;
    bin_clear(&c);
    // return a pointer with binary with 8bit size for signed integers (-127);
    c = bin_from_int(-127, 8);
    // print with its news size and value;
    bin_print(c);

    //printf("uint u %u\n", bin_to_uint(a));
    //printf("uint d %d\n", bin_to_int(a));
	//bin_int_add_print(a, b);
	return 0;
}
