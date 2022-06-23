#ifndef hist_H
#define hist_H

#include <stdio.h>
#include <stdint.h>

#define STR_LEN 120


typedef struct HIST_T
{
	char number[STR_LEN];
	char base[STR_LEN];
	char result[STR_LEN];
	char new_base[STR_LEN];
} hist_t;


int8_t hist_read(hist_t *hist_out);
int8_t hist_write(hist_t *hist_in);
void hist_print(hist_t *hist);

#endif 
