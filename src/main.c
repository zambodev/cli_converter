#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "num.h"
#include "hist.h"

#define FILENAME "conv_history.bin"


int main(int argc, char **argv)
{	
	/* Used variables */
	num_t num = {0, 0, 0};
	hist_t hist;
	char output[STR_LEN];

	/* Check arguments count */
	if(argc == 1) 
	{
		puts("ERROR: Missing parameters, use -h for help");
		return EXIT_FAILURE;	
	}
	/* Args parser */
	else if(argv[1][1] == 'h' || argv[1][2] == 'h')
	{
		printf("%s%*s%s\n%s%*s%s\n%s%*s%s\n",
		"Default:", 32-8, " ", "<number> <base> <new_base>",
		"-h --help:", 32-10, " ", "Show this help page",
		"-l <n> --last <n>:", 32-18, " ", "Print last-n conversion"
		);

		return EXIT_SUCCESS;
	}
	else if(argv[1][1] == 'l' || argv[1][2] == 'l')
	{	
		int8_t retval;
		if(argc < 3)
			retval = hist_read(&hist, NULL);
		else
			retval = hist_read(&hist, argv[2]);
		
		if(retval == -1)
		{
			printf("ERROR: Log reading failed!\n");
			return EXIT_FAILURE;
		}

		hist_print(&hist);

		return EXIT_SUCCESS;
	}
	else if(argc < 4)
	{
		puts("ERROR: Missing parameters! <number> <base> <new_base>");
		return EXIT_FAILURE;
	}


	/* Initialize num_t */
	if(num_init(&num, argv[1], argv[2]) == -1)
	{
		puts("ERROR: Number initialization failed!");
		return EXIT_FAILURE;
	}

	/* Convert num_t to str with new base */
	if(num_to_str(&num, output, argv[3]) == -1)
	{
		puts("ERROR: Number conversion failed!");
		return EXIT_FAILURE;
	}

	/* Print out new number */
	printf("%s\n", output);
	
	/* Store conversion in hist_t */
	strcpy(hist.base, argv[2]);
	strcpy(hist.new_base, argv[3]);
	strcpy(hist.result, output);
	/* Convert num_t to str with original base */
	if(num_to_str(&num, output, argv[2]) == -1)
	{
		puts("ERROR: Conversion to base 10 failed!");
		return EXIT_FAILURE;
	}
	strcpy(hist.number, output);

	/* Store hist_t in file */
	if(hist_write(&hist) == -1)
	{
		puts("ERROR: Writing history file failed!");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
