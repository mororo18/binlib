#ifndef _BINLIB_H
#define _BINLIB_H

#include "binlib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bin_print(void * ar){
    bin_intn_t * ar_adr = &ar;
    int sz = (*ar_adr)->sz;

    for(int i = sz - 1; i >= 0; i--)
        printf("%d", (*ar_adr)->bit[i]);
    printf("\n");
}

void bin_clear(void ** bin){
    if(*bin != NULL){
        free(*bin);
        *bin = NULL;
    }
}

static bool char_to_bool(char c){
    return (bool)(c - '0');
}

static void str_to_bool(const char * src, bool * ar, int sz){
    int str_len = strlen(src);

    for(int i = str_len - 1, j = 0; i >= 0; i--, j++){
        ar[j] = char_to_bool(src[i]);
    }

}

void * bin_assign(const char * src){
    int size = strlen(src);

    if(size % 8){
        fprintf(stderr, "[!!] error: in function \033[1m\'bin_assign\'\033[0m.\n"
                "     Invalid lenght={\033[1;31m%d\033[0m} of the passed string={\033[1;31m%s\033[0m}.\n", size, src);
        exit(1);
    }

    switch(size){
        case 8:
            {
                bin_int8_t value = malloc(sizeof(struct rg_8bit));
                str_to_bool(src, value->bit, size);
                value->sz = size;
                return value;
            }
        case 16:
            {
                bin_int16_t	value = malloc(sizeof(struct rg_16bit));
                str_to_bool(src, value->bit, size);
                value->sz = size;
                return value;
            }
        case 32:
            {
                bin_int32_t value = malloc(sizeof(struct rg_32bit));
                str_to_bool(src, value->bit, size);
                value->sz = size;
                return value;
            }
        case 64:
            {
                bin_int64_t value = malloc(sizeof(struct rg_64bit));
                str_to_bool(src, value->bit, size);
                value->sz = size;
                return value;
            }
    }
}

static int max(int a, int b){
    int tbl[] = {a, b};

    return tbl[b > a];
}

static void bin_bit_sum(bool * dest_bit, bool * a_bit, bool * b_bit, int size){
    int sum;
    int rmd = 0;
    for(int i = 0; i < size; i++){
        sum = a_bit[i] + b_bit[i] + rmd;	

        if(sum < 2){
            dest_bit[i] = sum;
            rmd = 0;
        }else{
            dest_bit[i] = sum % 2;
            rmd = 1;
        }
    }
}

void * bin_int_resize(void * a, int size_new){
    bin_intn_t * a_adr = &a;

    switch(size_new){
        case 8:
            {
                bin_int8_t total = malloc(sizeof(struct rg_8bit));
                memcpy(total->bit, (*a_adr)->bit, (*a_adr)->sz);
                total->sz = 8;
                return total;
            }
        case 16:
            {
                bin_int16_t	total = malloc(sizeof(struct rg_16bit));
                memcpy(total->bit, (*a_adr)->bit, (*a_adr)->sz);
                total->sz = 16;
                return total;
            }
        case 32:
            {
                bin_int32_t total = malloc(sizeof(struct rg_32bit));
                memcpy(total->bit, (*a_adr)->bit, (*a_adr)->sz);
                total->sz = 32;
                return total;
            }
        case 64:
            {
                bin_int64_t total = malloc(sizeof(struct rg_64bit));
                memcpy(total->bit, (*a_adr)->bit, (*a_adr)->sz);
                total->sz = 64;
                return total;
            }
    }
}

void * bin_int_sum(void * a, void * b){
    bin_intn_t * a_adr = &a;
    bin_intn_t * b_adr = &b;

    int a_size = (*a_adr)->sz;
    int b_size = (*b_adr)->sz;
    int size_max = max(a_size, b_size); 
    //printf("size max %d\n", b_size);
    //printf("size max %d\n", a_size);

    switch(size_max){
        case 8:
            {
                bin_int8_t c = bin_int_resize(a, 8);
                bin_int8_t d = bin_int_resize(b, 8);
                bin_int8_t total = malloc(sizeof(struct rg_8bit));
                total->sz = 8;
                bin_bit_sum(total->bit, c->bit, d->bit, total->sz);
                bin_clear(&c);
                bin_clear(&d);
                return total;
            }
        case 16:
            {
                bin_int16_t c = bin_int_resize(a, 16);
                bin_int16_t d = bin_int_resize(b, 16);
                bin_int16_t total = malloc(sizeof(struct rg_16bit));
                total->sz = 16;
                bin_bit_sum(total->bit, c->bit, d->bit, total->sz);
                bin_clear(&c);
                bin_clear(&d);
                return total;
            }
        case 32:
            {
                bin_int32_t c = bin_int_resize(a, 32);
                bin_int32_t d = bin_int_resize(b, 32);
                bin_int32_t total = malloc(sizeof(struct rg_32bit));
                total->sz = 32;
                bin_bit_sum(total->bit, c->bit, d->bit, total->sz);
                bin_clear(&c);
                bin_clear(&d);
                return total;
            }
        case 64:
            {
                bin_int64_t c = bin_int_resize(a, 64);
                bin_int64_t d = bin_int_resize(b, 64);
                bin_int64_t total = malloc(sizeof(struct rg_64bit));
                total->sz = 64;
                bin_bit_sum(total->bit, c->bit, d->bit, total->sz);
                bin_clear(&c);
                bin_clear(&d);
                return total;
            }
    }
}

#endif
