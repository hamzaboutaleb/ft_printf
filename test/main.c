
#include <stdio.h>

int	main(void)
{
	int	n;

	fclose(stdout);
	n = printf("%-+--d\n", 50);
	return (n);
}

/*
-
0

*/