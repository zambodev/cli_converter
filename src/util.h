#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>


uint64_t strlen_d(const char *number_str, char delimiter);
int8_t alpha_to_dec(char c);
int8_t str_to_uint8(const char *str, uint8_t *num);


#endif
