
#include <stdio.h>

int	main(void)
{
	int	n;

	n = printf("%0-50p", (void *)1006);
	printf("\nreturn: %d\n", n);
	return (n);
}

/*
-
0

*/