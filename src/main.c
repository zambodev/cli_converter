#include <stdio.h>
#include <stdlib.h>

#include "charset.h"
#include "num.h"


int main(int argc, char **argv)
{	
	if(argc == 1) 
	{
		puts("ERROR: Missing parameters, use -h for help");
		return EXIT_FAILURE;	
	}

	/* Args parser */
	if(argv[1][1] == 'h' || argv[1][2] == 'h')
	{
		printf("%s%*s%s\n%s%*s%s\n",
		"Default:", 32-8, " ", "<number> <base> <new_base>",
		"-h --help:", 32-10, " ", "Show this help page"
		);

		return EXIT_SUCCESS;
	}
	else
	{
		puts("ERROR: Wrong parameters, use -h for help");
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
