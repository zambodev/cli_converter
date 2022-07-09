#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "util.h"
#include "num.h"


static const char alphabet[] = {'0', '1', '2', '3' ,'4' ,'5' ,'6' ,'7' ,'8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

/* Initialize number converting it to base 10 */
int8_t num_init(num_t *number, const char *in_str, const char *base_str)
{	
	uint8_t base = 0;

	/* Convert base_str into number */
	if(str_to_uint8(base_str, &base) == -1) return -1;
	/* Check base value */
	if(base < 2 || base > 36) return -1;
	
	/* Check String correctness */
	if(str_check(in_str, base) == -1) return -1;
	
	/* Sign value */
	number->base |= (*in_str == '-') ? 128 : 0;
	/* Set the point at the first number position */
	if(*in_str == '-' || *in_str == '+') ++in_str;

	/* Get whole length */
	uint64_t expval;
	if((expval = strlen_d(in_str, '.')) == 0) return -1;
	
	uint64_t retval;

	/* Whole number conversion */
	while(*in_str != '.' && *in_str != '\0')
	{	
		/* Convert chars into decimal numbers */
		retval = alpha_to_dec(*in_str);
		/* Check for conversion errors */
		if(retval == -1 || retval >= base) return -1;

		number->whole += retval * pow(base, --expval);
		++in_str;
	}

	/* Skip the middle dot */
	if(*in_str == '.') ++in_str;
	if(*in_str == '\0') return 0;

	/* Decimal number conversion */
	while(*in_str != '\0')
	{	
		/* Convert chars into decimal numbers */
		retval = alpha_to_dec(*in_str);
		/* Check for conversion errors */
		if(retval == -1 || retval >= base) return -1;
		
		number->decimal += retval / pow(base, ++expval);
		++in_str;
	}

	return 0;
}

/* Convert numbert into new base */
int8_t num_to_str(num_t *number, char *out_str, const char *new_base_str)
{	
	uint8_t new_base = 0;
	/* Convert base_str into number */
	if(str_to_uint8(new_base_str, &new_base) == -1) return -1;
	/* Check base value */
	if(new_base < 2 || new_base > 36) return -1;

	/* Allocate the maximum possible result size */
	char ret_str[STR_LEN];
	memset(out_str, 0, STR_LEN);

	/* Number indexes */
	uint8_t whole_stidx = 65, decimal_stidx = 66;

	/* Whole part conversion */
	uint64_t wholenum = number->whole;
	char *ret_str_iter = ret_str+65;

	/* Add the decimal dot if needed */
	if(number->decimal > 0.0000000000000000) *ret_str_iter = '.';

	while(wholenum > 0)
	{	
		/* Get chars from the alphabet array */
		*(--ret_str_iter) = alphabet[(wholenum % new_base)];

		wholenum /= new_base;
		--whole_stidx;
	}

	/* Decimal part conversion */
	double decnum = number->decimal;
	ret_str_iter = ret_str+65;

	do
	{
		decnum *= new_base;
		/* Get chars from the alphabet array */
		*(++ret_str_iter) = alphabet[(uint64_t)decnum];
		decnum -= (uint64_t)decnum;
		++decimal_stidx;
	}
	while(decnum != 0.0);
	
	char *out = out_str;
	uint64_t idx = 0;

	/* Insert sign */
	out[idx] = ((number->base & 128) != 0) ? '-' : '+';

	/* Copy string into output */
	for(int i=whole_stidx; i<decimal_stidx; ++i)
		out[++idx] = ret_str[i];
	out[++idx] = '\0';
	
	/* Clear pointer */
	out = NULL;

	return 0;
}

/* Print the number, just for debug */
void num_debug(num_t *number)
{
	char sign = ((number->base & 128) != 0) ? '-' : '+';
	char str[327];
	sprintf(str, "%.16f", number->decimal);

	if(number->decimal > 0.0000000000000000)
		printf("%c%lu.%s\n", sign, number->whole, str+2);
	else
		printf("%c%lu\n", sign, number->whole);
}
