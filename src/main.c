#include <stdio.h>
#include <stdlib.h>

#include "charset.h"
#include "number/num.h"


int main(int argc, char **argv)
{	
	if(argc < 4) 
	{
		puts("ERROR: Missing parameters <number> <base> <new_base>");
		return EXIT_FAILURE;	
	}

	num_t num = {0, 0, 0};
	char output[STR_LEN];


	num_init(&num, argv[1], strtol(argv[2], NULL, 10));

	num_to_str(&num, output, strtol(argv[3], NULL, 10));
	printf("%s\n", output);

	return EXIT_SUCCESS;
}
