#ifndef NUM_H
#define NUM_H

#include <stdint.h>

#define STR_LEN 120


typedef struct NUM_T
{
	uint64_t whole;		/* Stored in base 10 */
	double decimal;		/* Stored in base 10 */
	uint8_t base;		/* Higher bit used for sign, 127 is the max base */
} num_t;


int8_t num_init(num_t *number, const char *in_str, const char *base_str);
int8_t num_to_str(num_t *number, char *out_str, const char *new_base_str);
void num_debug(num_t *number);


#endif 
