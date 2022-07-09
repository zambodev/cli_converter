#include <math.h>

#include "util.h"


int8_t str_check(const char *number_str, uint8_t base)
{
	/* Skip the sign if present */
	const char *str_ptr = (*number_str == '-' || *number_str == '+') ? number_str+1 : number_str;

	while(*str_ptr != '\0')
	{
		if(alpha_to_dec(*str_ptr) >= base) return -1;
		++str_ptr;
	}
	
	return 0;
}

/* Get number length with delimiter*/
uint64_t strlen_d(const char *number_str, char delimiter)
{
	uint64_t length = 0;

	/* Skip the sign if present */
	const char *number_str_iter = (*number_str == '-' || *number_str == '+') ? number_str+1 : number_str;

	/* Get whole max idx */
	while(*number_str_iter != delimiter && *number_str_iter != '\0')
	{	
		++length;
		++number_str_iter;
	}

	return length;
}

/* Convert chars into respective decimal number */
int8_t alpha_to_dec(char c)
{
	if(c >= '0' && c <= '9')
		return c - '0';
	else if(c >= 'A' && c <= 'Z')
		return c - 55;
	else if(c >= 'a' && c <= 'z')
		return c - 87;
	else
		return -1;
}

/* Convert a string into uin8_t value */
int8_t str_to_uint8(const char *str, uint8_t *num)
{
	const char *iter = str;
	int8_t retval = 0;
	uint8_t exp = strlen_d(str, '\0');

	while(*iter != '\0')
	{
		if((retval = alpha_to_dec(*iter)) == -1) return -1;
		*num += retval * pow(10, --exp);
		++iter;	
	}

	return 0;
}


