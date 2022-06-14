#include <stdio.h>
#include <stdlib.h>

#include "charset.h"
#include "number/num.h"


int main(int argc, char **argv)
{	
	num_t num = {0, 0, 0};
	char output[STR_LEN];


	num_init(&num, "-123.123", 10);
	num_debug(&num);

	num_to_str(&num, output, 16);
	printf("%s\n", output);

	num_to_str(&num, output, 2);
	printf("%s\n", output);

	return EXIT_SUCCESS;
}
