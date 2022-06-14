#ifndef NUM_H
#define NUM_H

#define STR_LEN 120

#include <stdint.h>


typedef struct NUM_T
{
	uint64_t whole;		/* Stored in base 10 */
	double decimal;		/* Stored in base 10 */
	uint8_t base;		/* Higher bit used for sign, 127 is the max base */
} num_t;


int8_t num_init(num_t *number, const char *in_str, uint8_t base);
int8_t num_to_str(num_t *number, char *out_str, uint8_t new_base);
void num_debug(num_t *number);


#endif 
