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


typedef char * bin_int8_t;

extern bool char_to_bool(char);
extern void str_to_bool(bin_int8_t src, bool * ar, int sz); 
extern void bin_print(bool *ar, int sz);
extern void bin_sum(bin_int8_t a, bin_int8_t b, bin_int8_t dest);
