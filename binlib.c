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

void bin_bit_print(bool * bit, int sz){
    for(int i = 0; i < sz; i++)
        printf("%d", bit[i]);
    printf("\n");
}

static void bin_bit_add(bool * dest_bit, bool * a_bit, bool * b_bit, int size){
    int total;
    int rmd = 0;
    for(int i = 0; i < size; i++){
        total = a_bit[i] + b_bit[i] + rmd;	

        if(total < 2){
            dest_bit[i] = total;
            rmd = 0;
        }else{
            dest_bit[i] = total % 2;
            rmd = 1;
        }
    }

    //bin_bit_print(a_bit, size);
    //bin_bit_print(b_bit, size);
}

static void bin_bit_clear(bool * bit, int sz){
    for(int i = 0; i < sz; i++)
        bit[i] = 0;
}

void * bin_int_resize(void * a, int size_new){
    bin_intn_t * a_adr = &a;

    switch(size_new){
        case 8:
            {
                bin_int8_t total = malloc(sizeof(struct rg_8bit));
                bin_bit_clear(total->bit, 8);
                memcpy(total->bit, (*a_adr)->bit, (*a_adr)->sz);
                total->sz = 8;
                return total;
            }
        case 16:
            {
                bin_int16_t	total = malloc(sizeof(struct rg_16bit));
                bin_bit_clear(total->bit, 16);
                memcpy(total->bit, (*a_adr)->bit, (*a_adr)->sz);
                total->sz = 16;
                return total;
            }
        case 32:
            {
                bin_int32_t total = malloc(sizeof(struct rg_32bit));
                bin_bit_clear(total->bit, 32);
                memcpy(total->bit, (*a_adr)->bit, (*a_adr)->sz*sizeof(bool));
                //bin_bit_print((*a_adr)->bit, (*a_adr)->sz);
                total->sz = 32;
                return total;
            }
        case 64:
            {
                bin_int64_t total = malloc(sizeof(struct rg_64bit));
                bin_bit_clear(total->bit, 64);
                memcpy(total->bit, (*a_adr)->bit, (*a_adr)->sz);
                total->sz = 64;
                return total;
            }
    }
}

static int bin_int_size(void * a){
    bin_intn_t * a_adr = &a;
    int a_size = (*a_adr)->sz;

    return a_size;
}

static int bin_int_size_larger(void * a, void * b){
    bin_intn_t * a_adr = &a;
    bin_intn_t * b_adr = &b;

    int a_size = bin_int_size(a);
    int b_size = bin_int_size(b);
    int tbl[] = {a_size, b_size};

    return tbl[b_size > a_size];
}

void * bin_int_add(void * a, void * b){

    int size_max = bin_int_size_larger(a, b);

    switch(size_max){
        case 8:
            {
                bin_int8_t c = bin_int_resize(a, 8);
                bin_int8_t d = bin_int_resize(b, 8);
                bin_int8_t total = malloc(sizeof(struct rg_8bit));
                total->sz = 8;
                bin_bit_add(total->bit, c->bit, d->bit, total->sz);
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
                bin_bit_add(total->bit, c->bit, d->bit, total->sz);
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
                bin_bit_add(total->bit, c->bit, d->bit, total->sz);
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
                bin_bit_add(total->bit, c->bit, d->bit, total->sz);
                bin_clear(&c);
                bin_clear(&d);
                return total;
            }
    }
}

void bin_int_add_print(void * a, void * b){
    void * bigger;
    void * smaller;

    int bigger_size;
    int a_size = bin_int_size(a);
    int b_size = bin_int_size(b);
    int dif;

    bin_int64_t result = bin_int_add(a, b);

    if(a_size > b_size){
        dif = a_size - b_size;
        dif /= 8;

        bigger = a;
        smaller = b;
        bigger_size = a_size;

    }else{

        dif = b_size - a_size;
        dif /= 8;
        bigger = b;
        smaller = a;
        bigger_size = b_size;
    }

    printf("\t");                                   bin_print(bigger);
    printf("      + "); while(dif--) printf("\t");  bin_print(smaller);
    printf("\t");       while(bigger_size--) printf("="); printf("\n");
    printf("\t");                                   bin_print(result);
    printf("\n");

    bin_clear(&result);

}

unsigned bin_to_uint(void * a){
    unsigned a_int = 0;
    int a_size = bin_int_size(a);
    bin_intn_t * a_adr = &a;

    for(int i = 0; i < a_size; i++)
        a_int += (*a_adr)->bit[i] << i;

    return a_int;
}

void bin_bit_invert(bool * bit, int sz){
    for(int i = 0; i < sz; i++)
        bit[i] = !bit[i];
}

int bin_two_complement(void * a){
    int a_size = bin_int_size(a);
    bin_intn_t * a_adr = &a;

    bool * bit = (*a_adr)->bit;
    bool sign = bit[a_size-1];

    if(sign){
        bool bit_complement[a_size];
        bin_bit_clear(bit_complement, a_size);
        bit_complement[0] = 1;

        bit[a_size-1] = 0;
        bin_bit_invert(bit, a_size-1);
        bin_bit_add(bit, bit, bit_complement, a_size);

        int int_signed = (-1) * bin_to_uint(a);

        return int_signed;
        
    }else{

    }
}

int bin_to_int(void * a){
    int a_int = 0;
    int a_size = bin_int_size(a);
    bin_intn_t * a_adr = &a;

    bool sign = (*a_adr)->bit[a_size-1];

    if(sign)
        return bin_two_complement(a);
    else
        return bin_to_uint(a);
}

#endif
