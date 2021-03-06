/**
    ================================
    filename: binlib.h
    date: feb-24-2021
    creator: Victor Mororo
    ================================
**/

#include <stdbool.h>

struct rg_8bit  { int sz; bool bit[8];};
struct rg_16bit { int sz; bool bit[16];};
struct rg_32bit { int sz; bool bit[32];};
struct rg_64bit { int sz; bool bit[64];};
struct rg_nbit  { int sz; bool bit[64];};

typedef struct rg_nbit  * bin_intn_t;
typedef struct rg_8bit  * bin_int8_t;
typedef struct rg_16bit * bin_int16_t;
typedef struct rg_32bit * bin_int32_t;
typedef struct rg_64bit * bin_int64_t;


void *  bin_int_assign(const char * bin_str); 
void *  bin_int_resize(void * bin_int_type, int size_new);
void    bin_clear(void **);

void    bin_print(void *);

void *  bin_int_add(void * a_bin_int_type, void * b_bin_int_type);
void    bin_int_add_print(void * a_bin_int_type, void * b_bin_int_type);

unsigned bin_to_uint(void * bin_int_type);
int     bin_to_int(void * bin_int_type);
void *  bin_from_uint(unsigned a_int, int rg_size);
void *  bin_from_int(int a_int, int rg_size);
void    bin_bit_move(void * a, int delta);
void *  bin_int_multiply(void * a, void * b);
