#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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

	/* Convert base into number */
	uint8_t tmp = strtol(argv[2], NULL, 10);
	if(errno == ERANGE)
	{
		perror("strtol");
		return EXIT_SUCCESS;
	}
	/* Initialize num_t */
	num_init(&num, argv[1], tmp);

	/* Convert new base into number */
	tmp = strtol(argv[3], NULL, 10);
	if(errno == ERANGE)
	{
		perror("strtol");
		return EXIT_SUCCESS;
	}
	/* Convert num_t to str with new base */
	num_to_str(&num, output, tmp);
	
	/* Print out new number */
	printf("%s\n", output);

	return EXIT_SUCCESS;
}
