/**
    ================================
    filename: binlib.c
    date: feb-24-2021
    creator: Victor Mororo
    ================================
**/

#ifndef _BINLIB_H
#define _BINLIB_H

#include "binlib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static
int bin_int_size(void * a){
    bin_intn_t * a_adr = &a;
    int a_size = (*a_adr)->sz;

    return a_size;
}

void bin_print(void * a){
    bin_intn_t * a_adr = &a;
    bool * a_bit = (*a_adr)->bit;
    int sz = bin_int_size(a);

    for(int i = sz - 1; i >= 0; i--)
        printf("%d", a_bit[i]);
    printf("\n");
}

void bin_clear(void ** bin){
    if(*bin != NULL){
        free(*bin);
        *bin = NULL;
    }
}

static inline
bool char_to_bool(char c){
    return (bool)(c - '0');
}

static
void str_to_bool(const char * src, bool * ar, int sz){
    int str_len = strlen(src);

    for(int i = str_len - 1, j = 0; i >= 0; i--, j++){
        ar[j] = char_to_bool(src[i]);
    }

}

static
void bin_bit_clear(bool * bit, int sz){
    for(int i = 0; i < sz; i++)
        bit[i] = 0;
}

static
void * bin_int_malloc(int size){
    bin_intn_t total;

    switch(size){
        case 8:
            {
                total = malloc(sizeof(struct rg_8bit));
                break;
            }
        case 16:
            {
                total = malloc(sizeof(struct rg_16bit));
                break;
            }
        case 32:
            {
                total = malloc(sizeof(struct rg_32bit));
                break;
            }
        case 64:
            {
                total = malloc(sizeof(struct rg_64bit));
                break;
            }
    }

    total->sz = size;
    bin_bit_clear(total->bit, size);

    return total;
}

void * bin_int_assign(const char * bin_str){
    char * src = bin_str;
    int size = strlen(src);

    if(size % 8 || size > 64){
        fprintf(stderr, "[!!] error: in function \033[1m\'bin_int_assign\'\033[0m.\n"
                "     Invalid lenght={\033[1;31m%d\033[0m} of the passed string={\033[1;31m%s\033[0m}.\n", size, src);
        exit(1);
    }

    bin_intn_t value = bin_int_malloc(size);
    str_to_bool(src, value->bit, size);

    return value;
}

static
void bin_bit_print(bool * bit, int sz){
    for(int i = 0; i < sz; i++)
        printf("%d", bit[i]);
    printf("\n");
}

static
void bin_bit_add(bool * dest_bit, bool * a_bit, bool * b_bit, int size){
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

}

static 
void bin_bit_invert(bool * bit, int sz){
    for(int i = 0; i < sz; i++)
        bit[i] = !bit[i];
}

void * bin_int_resize(void * a, int size_new){
    bin_intn_t total;
    bin_intn_t * a_adr = &a;

    bool * a_bit = (*a_adr)->bit;
    int a_size = bin_int_size(a);
    bool a_sign = a_bit[a_size - 1];

    total = bin_int_malloc(size_new);
    //bin_bit_clear(total->bit, size_new);

    if(a_sign)
        bin_bit_invert(total->bit, size_new); 

    memcpy(total->bit, a_bit, a_size);

    return total;
}

static 
int bin_int_size_larger(void * a, void * b){
    int a_size = bin_int_size(a);
    int b_size = bin_int_size(b);
    int tbl[] = {a_size, b_size};

    return tbl[b_size > a_size];
}

void * bin_int_add(void * a, void * b){

    int size_max = bin_int_size_larger(a, b);

    bin_intn_t total = bin_int_malloc(size_max);
    bin_intn_t c = bin_int_resize(a, size_max);
    bin_intn_t d = bin_int_resize(b, size_max);

    bin_bit_add(total->bit, c->bit, d->bit, total->sz);

    bin_clear(&c);
    bin_clear(&d);

    return total;
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
        smaller = bin_int_resize(b, a_size);
        bigger_size = a_size;

    }else{
        dif = b_size - a_size;
        dif /= 8;

        bigger = b;
        smaller = bin_int_resize(a, b_size);
        bigger_size = b_size;
    }

    printf("\t");                                   bin_print(bigger);
    printf("      + ");                             bin_print(smaller);
    printf("\t");       while(bigger_size--) printf("="); printf("\n");
    printf("\t");                                   bin_print(result);
    printf("\n");

    bin_clear(&smaller);
    bin_clear(&result);

}

unsigned bin_uint_to_dec(void * a){
    unsigned a_int = 0;
    int a_size = bin_int_size(a);
    bin_intn_t * a_adr = &a;

    for(int i = 0; i < a_size; i++)
        a_int += (*a_adr)->bit[i] << i;

    return a_int;
}

int bin_two_complement(void * a){

    int a_size = bin_int_size(a);
    bin_intn_t a_copy = bin_int_resize(a, a_size);
    bool * bit = a_copy->bit;

    bool sign = bit[a_size-1];


    if(sign){
        bool bit_complement[a_size];
        bin_bit_clear(bit_complement, a_size);
        bit_complement[0] = 1;

        bit[a_size-1] = 0;
        bin_bit_invert(bit, a_size-1);
        bin_bit_add(bit, bit, bit_complement, a_size);

        int int_signed = (-1) * bin_uint_to_dec(a_copy);
        bin_clear(&a_copy);

        return int_signed;
        
    }else{

    }
}

int bin_int_to_dec(void * a){
    int a_int;
    int a_size = bin_int_size(a);
    bin_intn_t * a_adr = &a;

    bool sign = (*a_adr)->bit[a_size-1];

    if(sign)
        a_int = bin_two_complement(a);
    else
        a_int = bin_uint_to_dec(a);

    return a_int;
}

void * bin_uint_from_dec(unsigned a_int, int rg_size){
    char buff[rg_size+1];
    int quoc = a_int;
    int i = rg_size;
    bool rmd;

    for(;;){
        rmd = quoc % 2;
        quoc /= 2;
        buff[--i] = rmd + '0';

        if(!i)
            break;
    }

    buff[rg_size] = '\0';

    return bin_int_assign(buff);
}

void * bin_int_from_dec(int a_int, int rg_size){
    bin_intn_t temp;
    if(a_int < 0){
        temp = bin_uint_from_dec((-1)* a_int, rg_size);
        bin_bit_invert(temp->bit, temp->sz);

        bool comp[rg_size];
        bin_bit_clear(comp, rg_size);
        comp[0] = 1;

        bin_bit_add(temp->bit, temp->bit, comp, rg_size);

    }else{

        temp = bin_uint_from_dec(a_int, rg_size);

    }

    return temp;
}

void bin_bit_shift(void * a, int delta){
    int a_size = bin_int_size(a);
    bin_intn_t * a_adr = &a;
    bool * a_bit = (*a_adr)->bit;

    if(delta < 0){
        int a_size_sub = a_size + delta;
        memmove(a_bit, a_bit - delta, a_size_sub * sizeof(bool));

        for(int i = a_size_sub; i < a_size; i++)
            a_bit[i] = 0;
    }else if(delta > 0){
        int a_size_sub = a_size - delta;
        memmove(a_bit + delta, a_bit, a_size_sub * sizeof(bool));

        for(int i = 0; i < delta; i++)
            a_bit[i] = 0;
    }
}

int bin_bit_set_count(void * a){
    bin_intn_t * a_adr = &a;
    int a_size = bin_int_size(a);
    bool * a_bit = (*a_adr)->bit;
    int count = 0;

    for(int i = 0; i < a_size; i++)
        if(a_bit[i])
            count++;

    return count;
}

int bin_size_fit(int size){
    if(size <= 8)
        return 8;
    else if(size <= 16)
        return 16;
    else if(size <= 32)
        return 32;
    else if(size <= 64)
        return 64;
    else
        fprintf(stderr, "[!!] error: in function \033[1m\'bin_size_fit\'\033[0m.\n"
                "     Invalid size={\033[1;31m%dbits\033[0m}. Max size support is 64bits.\n",size);
        
}

void * bin_int_multiply(void * a, void * b){
    bin_intn_t result;
    bin_intn_t buffer;
    bin_intn_t bigger;
    bin_intn_t smaller;
    int a_size = bin_int_size(a);
    int b_size = bin_int_size(b);
    int result_size;
    int increasement;

    if(a_size < b_size){
        increasement = a_size - 1;
        result_size = b_size + increasement;
        bigger = b;
        smaller = a;
    }else{
        increasement = b_size - 1;
        result_size = a_size + increasement;
        bigger = a;
        smaller = b;
    }

    if(result_size > 64)    {
        fprintf(stderr, "[!!] error: in function \033[1m\'bin_int_multiply\'\033[0m.\n"
                "     Invalid size={\033[1;31m%dbits\033[0m}. Can't support the result of the multiplication between \'%dbits\' and \'%dbits\'.\n",
                result_size, a_size, b_size);
        exit(1);
    }

    result = bin_int_malloc(bin_size_fit(result_size)); 
    buffer = bin_int_resize(bigger, bin_size_fit(result_size)); 

    int itert = bin_int_size(smaller);
    bool * bit = smaller->bit;

    for(int i = 0; i < itert; i++){
        bin_bit_shift(buffer, (bool)i);
        if(!bit[i])
            continue;
        
        bin_bit_add(result->bit, result->bit, buffer->bit, result->sz);
    }

    bin_clear(&buffer);

    return result;

}

#endif
