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
	if(argv[1][1] == 'h' || argv[1][2] == 'h')
	{
		printf("%s%*s%s\n%s%*s%s\n%s%*s%s\n",
		"Default:", 32-8, " ", "<number> <base> <new_base>",
		"-h --help:", 32-10, " ", "Show this help page",
		"-l <n> --last <n>:", 32-18, " ", "Print last-n conversion"
		);

		return EXIT_SUCCESS;
	}
	if(argv[1][1] == 'l' || argv[1][2] == 'l')
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


	/* Initialize num_t */
	num_init(&num, argv[1], argv[2]);

	/* Convert num_t to str with new base */
	num_to_str(&num, output, argv[3]);
	
	/* Print out new number */
	printf("%s\n", output);
	
	/* Store conversion in hist_t */
	strcpy(hist.base, argv[2]);
	strcpy(hist.new_base, argv[3]);
	strcpy(hist.result, output);
	/* Convert num_t to str with original base */
	num_to_str(&num, output, argv[2]);
	strcpy(hist.number, output);

	/* Store hist_t in file */
	hist_write(&hist);

	return EXIT_SUCCESS;
}
