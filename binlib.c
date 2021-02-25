#ifndef _BINLIB_H
#define _BINLIB_H

#include "binlib.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

bool char_to_bool(char c){
	return (bool)(c - '0');
}

void str_to_bool(const char * src, bool * ar, int sz){
	int str_len = strlen(src);

	for(int i = str_len - 2, j = 0; i >= 0; i--, j++){
		ar[j] = char_to_bool(src[i]);
	}

}

void bin_print(bool *ar, int sz){
	for(int i = sz - 1; i >= 0; i--)
		printf("%d", ar[i]);
	printf("\n");
}

bin_int8_t bin_assign(const char * src, int sz){
	bin_int8_t value;
	int bin_len;

	bin_len = sz;
	
	str_to_bool(src, value.bit, sz);

	return value;
}

bin_int8_t bin_sum(bin_int8_t a, bin_int8_t b){
	int size = sizeof(a.bit);
	printf("sizeof %d\n", size);
	//bool bin_total[size] ;
	bin_int8_t total;

	//str_to_bool(a, bin_a, size);
	//str_to_bool(b, bin_b, size);
	
	int sum;
	int rmd = 0;
	for(int i = 0; i < size; i++){
		 sum = a.bit[i] + b.bit[i] + rmd;	
		 printf("%d", sum);

		 if(sum < 2){
			 total.bit[i] = sum;
			 rmd = 0;
		 }else{
			total.bit[i] = 0;
			rmd = 1;
		}
	}

	bin_print(total.bit, size);
}

#endif
