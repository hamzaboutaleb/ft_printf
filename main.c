

#include "ft_printf.h"
#include <stdint.h>

int	main(void)
{
	int n = ft_printf("%#0-30p\n", (void *)SIZE_MAX);
	int m = printf("%#0-30p\n", (void *)SIZE_MAX);
	printf("bytes: %d -- %d\n", n, m);
}