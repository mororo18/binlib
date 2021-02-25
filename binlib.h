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
struct rg_8bit {bool bit[8];};
struct rg_16bit {bool bit[16];};
struct rg_32bit {bool bit[32];};
struct rg_64bit {bool bit[64];};

typedef struct rg_8bit * bin_int8_t;
typedef struct rg_16bit * bin_int16_t;
typedef struct rg_32bit * bin_int32_t;
typedef struct rg_64bit * bin_int64_t;

extern bool char_to_bool(char);
extern void str_to_bool(const char * src, bool * ar, int sz); 
void bin_print(bool *ar, int sz);
extern bin_int8_t bin_assign(const char * src, int sz);
extern void * bin_sum(void * a, void * b);
