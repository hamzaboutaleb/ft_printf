

#include "ft_printf.h"
#include <stdint.h>

int	main(void)
{
	int n;
	int m;
	m = 0;
	n = 0;

	char *format = "%#X\n";
	int l = -100;

	// n = ft_printf("%#0-30p\n", (void *)SIZE_MAX);
	n = ft_printf(format, l);
	m = printf(format, l);
	printf("bytes: %d -- %d\n", n, m);
}