#ifndef _BAMTH_H
#define _BAMTH_H

#include "bmath.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

bool char_to_bool(char c){
	return (bool)(c - '0');
}

void str_to_bool(bin_int8_t src, bool * ar, int sz){
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

void bin_sum(bin_int8_t a, bin_int8_t b, bin_int8_t dest){
	int size = 8;
	bool bin_a[size]  ;
	bool bin_b[size] ;
	bool bin_total[size] ;

	str_to_bool(a, bin_a, size);
	str_to_bool(b, bin_b, size);
	
	int sum;
	int rmd = 0;
	for(int i = 0; i < size; i++){
		 sum = bin_a[i] + bin_b[i] + rmd;	

		 if(sum != 2){
			 bin_total[i] = sum;
			 rmd = 0;
		 }else{
			bin_total[i] = 0;
			rmd = 1;
		}
	}

	bin_print(bin_total, size);
}

#endif
