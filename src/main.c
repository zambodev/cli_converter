#include <stdio.h>
#include <stdlib.h>

#include "charset.h"
#include "num.h"


int main(int argc, char **argv)
{	
	if(argc < 4) 
	{
		puts("ERROR: Missing parameters <number> <base> <new_base>");
		return EXIT_FAILURE;	
	}

	num_t num = {0, 0, 0};
	char output[STR_LEN];

	/* Initialize num_t */
	num_init(&num, argv[1], argv[2]);

	/* Convert num_t to str with new base */
	num_to_str(&num, output, argv[3]);
	
	/* Print out new number */
	printf("%s\n", output);

	return EXIT_SUCCESS;
}
