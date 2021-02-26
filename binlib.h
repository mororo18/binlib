/**
*
*
*
*
* HEADER
*
*
*
*
**/

#include <stdbool.h>

struct rg_8bit { int sz; bool bit[8];};
struct rg_16bit { int sz; bool bit[16];};
struct rg_32bit { int sz; bool bit[32];};
struct rg_64bit { int sz; bool bit[64];};
struct rg_nbit { int sz; bool bit[64];};

typedef struct rg_nbit * bin_intn_t;
typedef struct rg_8bit * bin_int8_t;
typedef struct rg_16bit * bin_int16_t;
typedef struct rg_32bit * bin_int32_t;
typedef struct rg_64bit * bin_int64_t;

//typedef unsigned uint;

void bin_print(void *ar);
void * bin_assign(const char * src);
void * bin_int_add(void * a, void * b);
void  bin_int_add_print(void * a, void * b);
unsigned bin_to_uint(void *);
int bin_to_int(void *);
