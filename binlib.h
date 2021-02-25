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

typedef struct binary {bool bit[8];} bin_int8_t;

extern bool char_to_bool(char);
extern void str_to_bool(const char * src, bool * ar, int sz); 
void bin_print(bool *ar, int sz);
extern bin_int8_t bin_assign(const char * src, int sz);
extern bin_int8_t bin_sum(bin_int8_t a, bin_int8_t b);
