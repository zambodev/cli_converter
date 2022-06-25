#include "hist.h"
#include "util.h"

#define FILENAME "/tmp/conv_history.bin"


int8_t hist_read(hist_t *hist_out, char *val_str)
{
	uint8_t val = 0;
	FILE *log;

	if((log = fopen(FILENAME, "rb")) == NULL) return -1;
	if(val_str != NULL && str_to_uint8(val_str, &val) == -1)
		return -1;
	else
		++val;
	
	if(fseek(log, -sizeof(hist_t) * val, SEEK_END) != 0) return -1;
	fread(hist_out, sizeof(hist_t), 1, log);
	
	if(ferror(log) != 0)
	{
		clearerr(log);
		return -1;
	}

	fclose(log);
	return 0;
}

int8_t hist_write(hist_t *hist_in)
{
	FILE *log;
	if((log = fopen(FILENAME, "ab")) == NULL) return -1;

	fwrite(hist_in, sizeof(hist_t), 1, log);
	if(ferror(log) != 0)
	{
		clearerr(log);
		return -1;
	}

	fclose(log);
	return 0;
}

void hist_print(hist_t *hist)
{
	printf("%s (%s) -> %s (%s)\n", hist->number, hist->base, hist->result, hist->new_base);
}
