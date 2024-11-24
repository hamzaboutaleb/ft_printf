

#include "ft_printf.h"

int	main(void)
{
	int n = ft_printf("%+-10c\n", 'h');
	int m = printf("%+-10c\n", 'h');
	printf("bytes: %d -- %d\n", n, m);
}