#ifndef _BINLIB_H
#define _BINLIB_H

#include "binlib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bin_print(bool *ar, int sz){
	for(int i = sz - 1; i >= 0; i--)
		printf("%d", ar[i]);
	printf("\n");
}

bool char_to_bool(char c){
	return (bool)(c - '0');
}

void str_to_bool(const char * src, bool * ar, int sz){
	int str_len = strlen(src);

	for(int i = str_len - 1, j = 0; i >= 0; i--, j++){
		ar[j] = char_to_bool(src[i]);
	}

}

bin_int8_t bin_assign(const char * src, int sz){
	bin_int8_t value = malloc(sizeof(struct rg_8bit));
	int bin_len;

	bin_len = sz;
	
	str_to_bool(src, value->bit, sz);

	return value;
}

void * bin_sum(void * c, void * d){
	bin_int8_t * a = &c;
	bin_int8_t * b = &d;

	int size = sizeof((*a)->bit);
	bin_int8_t total = malloc(sizeof(struct rg_8bit));

	int sum;
	int rmd = 0;
	for(int i = 0; i < size; i++){
		 sum = (*a)->bit[i] + (*b)->bit[i] + rmd;	

		 if(sum < 2){
			 total->bit[i] = sum;
			 rmd = 0;
		 }else{
			total->bit[i] = sum % 2;
			rmd = 1;
		}
	}

	bin_print(total->bit, size);
}

#endif
