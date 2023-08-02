#include <stdio.h>


extern int strnorm(char *val);

int main()
{
	int ret;
	char list[] = "789aBcD";

	if((ret = strnorm(list)) == -1)
	{
		printf("ERROR!\n");
		return 1;
	}

	printf("rax: %d\n", ret);

	for(int i = 0; i < 7; ++i)
		printf("%d ", list[i]);

	return 0;
}
